#!/bin/bash

PROG_NAME=$0

CC="gcc"
CFLAGS="-D_GNU_SOURCE -std=c99 -pedantic -Wall -O3"
DBG_FLAGS="-D_GNU_SOURCE -std=c99 -pedantic -Wall -g3 -fsanitize=address -Og"

function printhelp() {
    echo "${PROG_NAME} [-d] <QUIZ_NUMBER> ..."
    exit 1
}

[ $# -lt 1 ] && printhelp

FLAGS=""
if [ "$1" == "-d" ]; then
    shift
    FLAGS=${DBG_FLAGS}
else
    FLAGS=${CFLAGS}
fi

[ $# -lt 1 ] && printhelp

if [ $1 == "clean" ]; then
    rm -vr out
    exit 0
fi

mkdir -p out

while [[ $# -gt 0 ]]
do
    CMD="${CC} ${FLAGS} -o out/$1 $1.c"
    echo ${CMD} && eval ${CMD}
    shift
done
