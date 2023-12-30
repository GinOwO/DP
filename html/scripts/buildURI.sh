#!/usr/bin/env bash

echo "Getting Metadata from Leetcode"
node html/scripts/buildMetadata.js
echo "Received Metadata"
echo ""

echo "Building URIs"
mapfile -d $'\0' cppfiles < <(find . -name "*.cpp" -print0)
python3 html/scripts/mergeData.py "${cppfiles[@]}"
echo "Done"
echo ""

echo "Cleanup"
mv html/scripts/URIs.json ./URIs.json
rm html/scripts/metadata.json