#!/usr/bin/env bash

mapfile -d $'\0' cppfiles < <(find . -name "*.cpp" -print0)
python3 html/scripts/mergeData.py "${cppfiles[@]}"



