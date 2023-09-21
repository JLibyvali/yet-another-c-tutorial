#!/usr/bin/env bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
CC=clang
CXX=clang++
AR=ar

$CXX -c -o $SCRIPT_DIR/b.o $SCRIPT_DIR/b.cpp
$CXX -c -o $SCRIPT_DIR/b_interface.o $SCRIPT_DIR/b_interface.cpp
$AR rcs $SCRIPT_DIR/libb.a $SCRIPT_DIR/b.o $SCRIPT_DIR/b_interface.o
