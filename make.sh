#!/bin/bash

PROG_NAME=$0

CC="gcc"
CFLAGS="-D_GNU_SOURCE -std=c99 -pedantic -O3"
DBG_FLAGS="-Wall -g3 -fsanitize=address -Og"

function printhelp() {
    echo "${PROG_NAME} <QUIZ_NUMBER>"
    exit 1
}

[ $# -lt 1 ] && printhelp

if [ $1 == "clean" ]; then
    rm -vr out
    exit 0
fi

mkdir -p out

while [[ $# -gt 0 ]]
do
    echo ${CC} ${CFLAGS} -o out/$1 "$1.c"
    ${CC} ${C_FLAGS} -o out/$1 "$1.c"
    shift
done
