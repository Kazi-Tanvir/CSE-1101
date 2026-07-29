#!/bin/bash

# ============================================================
# C Programming Lab Grader
# Usage:
#   ./grader.sh student_folder
#
# Student folder should contain:
#   q1.c
#   q2.c
#   q3.c
#
# Tests should be stored as:
#   tests/q1/in001.txt
#   tests/q1/out001.txt
#   ...
# ============================================================

STUDENT_DIR=${1:-.}
TEST_DIR="tests"

TOTAL=0

GREEN="\033[0;32m"
RED="\033[0;31m"
YELLOW="\033[1;33m"
BLUE="\033[0;34m"
NC="\033[0m"

grade_question() {

    Q=$1
    SRC="$STUDENT_DIR/q${Q}.c"
    EXE="q${Q}.out"

    echo
    echo -e "${BLUE}========== Question $Q ==========${NC}"

    if [ ! -f "$SRC" ]; then
        echo -e "${RED}Source file q${Q}.c not found.${NC}"
        return
    fi

    echo "Compiling..."

    gcc -std=c11 -Wall -Wextra "$SRC" -o "$EXE"

    if [ $? -ne 0 ]; then
        echo -e "${RED}Compilation Failed${NC}"
        return
    fi

    PASS_COUNT=0
    TOTAL_TESTS=0

    for INPUT in "$TEST_DIR"/q"$Q"/in*.txt
    do
        TOTAL_TESTS=$((TOTAL_TESTS + 1))

        NUM=$(basename "$INPUT" | sed 's/in//; s/.txt//')
        EXPECTED="$TEST_DIR/q$Q/out$NUM.txt"

        ./"$EXE" < "$INPUT" > output.txt

        STATUS=$?

        if [ $STATUS -ne 0 ]; then
            echo "Test $NUM : RUNTIME ERROR"
            continue
        fi

        if diff -w -B output.txt "$EXPECTED" >/dev/null
        then
            echo -e "Test $NUM : ${GREEN}PASS${NC}"
            PASS_COUNT=$((PASS_COUNT + 1))
        else
            echo -e "Test $NUM : ${RED}FAIL${NC}"
        fi
    done

    MARKS=$(awk "BEGIN {printf \"%.2f\", ($PASS_COUNT/$TOTAL_TESTS)*10}")

    echo
    echo "Passed : $PASS_COUNT / $TOTAL_TESTS"


    TOTAL=$(awk "BEGIN {printf \"%.2f\", $TOTAL + $MARKS}")

    rm -f "$EXE" output.txt
}

echo "==========================================="
echo "        C Programming Lab Grader"
echo "==========================================="

grade_question 1
grade_question 2
grade_question 3

echo
echo "==========================================="
printf "TOTAL MARKS : %.2f / 30\n" "$TOTAL"
echo "==========================================="
