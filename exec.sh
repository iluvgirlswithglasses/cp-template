#!/bin/bash
set -euo pipefail

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
CYAN='\033[0;36m'
BOLD='\033[1m'
NC='\033[0m'

DEBUG=0
FAST=0

usage() {
    echo -e "${BOLD}Usage:${NC} $0 [-d|--debug] [-f|--fast] <file.cpp> [args...]"
    echo "  -d, --debug   Run with gdb on crash (auto-backtrace)"
    echo "  -f, --fast    Skip sanitizers for speed"
    exit 1
}

while [[ $# -gt 0 ]]; do
    case "$1" in
        -d|--debug) DEBUG=1; shift ;;
        -f|--fast)  FAST=1; shift ;;
        -h|--help)  usage ;;
        -*)         echo -e "${RED}Unknown option:${NC} $1"; usage ;;
        *)          break ;;
    esac
done

if [[ $# -lt 1 ]]; then usage; fi

SRC="$1"
shift

if [[ ! -f "$SRC" ]]; then
    echo -e "${RED}Error:${NC} File not found: $SRC"
    exit 1
fi

if [[ ! "$SRC" =~ \.cpp$ ]]; then
    echo -e "${YELLOW}Warning:${NC} File does not have .cpp extension"
fi

BIN="/tmp/cp_$(basename "$SRC" .cpp)_$$"

CXXFLAGS=(
    -std=c++20
    -g
    -Wall -Wextra -Wshadow
    -fno-omit-frame-pointer
)

if [[ $FAST -eq 0 ]]; then
    CXXFLAGS+=(-O2 -fsanitize=address,undefined -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC)
else
    CXXFLAGS+=(-O2)
    echo -e "${YELLOW}Fast mode:${NC} sanitizers disabled"
fi

echo -e "${CYAN}Compiling${NC} $SRC..."

if ! g++ "${CXXFLAGS[@]}" -o "$BIN" "$SRC" 2>&1; then
    echo -e "\n${RED}Compilation failed.${NC}"
    echo -e "${YELLOW}Hints:${NC}"
    echo "  - Check for missing semicolons or braces"
    echo "  - Verify all includes are present"
    echo "  - Look for typos in variable/function names"
    exit 1
fi

echo -e "${GREEN}Running${NC} $(basename "$SRC")...\n"

cleanup() { rm -f "$BIN"; }
trap cleanup EXIT

run_with_gdb() {
    echo -e "\n${CYAN}Running with gdb...${NC}\n"
    gdb -q -batch \
        -ex "set confirm off" \
        -ex "set pagination off" \
        -ex "run" \
        -ex "echo \n${YELLOW}=== BACKTRACE ===${NC}\n" \
        -ex "bt full" \
        -ex "echo \n${YELLOW}=== LOCAL VARIABLES ===${NC}\n" \
        -ex "info locals" \
        -ex "quit" \
        --args "$BIN" "$@" 2>&1 | grep -v "^\[" | head -100
}

set +e
"$BIN" "$@"
EXIT_CODE=$?
set -e

if [[ $EXIT_CODE -ne 0 ]]; then
    echo -e "\n${RED}━━━ Runtime error (exit code $EXIT_CODE) ━━━${NC}"

    case $EXIT_CODE in
        139|11)
            echo -e "${YELLOW}Segmentation fault.${NC} Common causes:"
            echo "  • Null/dangling pointer dereference"
            echo "  • Array index out of bounds"
            echo "  • Stack overflow (deep recursion)"
            ;;
        134|6)
            echo -e "${YELLOW}Abort signal.${NC} Triggered by:"
            echo "  • Sanitizer (ASan/UBSan) - see details above"
            echo "  • assert() failure"
            echo "  • STL bounds check (_GLIBCXX_DEBUG)"
            ;;
        136|8)
            echo -e "${YELLOW}Floating point exception.${NC} Check:"
            echo "  • Division by zero"
            echo "  • Invalid FP operation"
            ;;
        *)
            echo -e "${YELLOW}Unknown error.${NC}"
            ;;
    esac

    if [[ $DEBUG -eq 1 ]]; then
        run_with_gdb "$@"
    else
        echo -e "\n${CYAN}Tip:${NC} Run with ${BOLD}-d${NC} for gdb backtrace: ./exec.sh -d $SRC"
    fi
    exit $EXIT_CODE
fi
