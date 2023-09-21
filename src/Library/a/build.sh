#!/usr/bin/env bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
CC=clang
CXX=clang++
AR=ar

$CC -c -o $SCRIPT_DIR/a.o $SCRIPT_DIR/a.c
$AR rcs $SCRIPT_DIR/liba.a $SCRIPT_DIR/a.o
