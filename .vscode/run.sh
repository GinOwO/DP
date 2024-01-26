#!/bin/bash

if [ $# -eq 0 ]; then
  echo "Usage: $0 <file> <out>"
  exit 1
fi

g++ -g "$1" -o "$2" -std=c++20 -fsanitize=address -fsanitize=undefined
