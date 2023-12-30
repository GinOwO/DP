#!/usr/bin/env python3

import json
import sys
import os
import re

P = re.compile(r"/(NLC)?\.?(\d+)\.(\w+)\.cpp")

_DEBUG = False

def main():
    args = sys.argv
    if len(args) == 1 and not _DEBUG: return

    with open(f'html/scripts/metadata.json', 'r') as f:
        metadata = json.load(f)
    
    output = {"NLC":[]}

    for cnt, arg in enumerate(args[1:], start=1):
        nlc, Id, name = P.findall(arg)[0]
        if not Id: continue
        if not nlc:
            obj = metadata[Id]
            if not obj: continue
            obj['URI'] = arg
            output[Id] = obj
        else: 
            output['NLC'].append({
                "Title": name,
                "URI": arg,
                "Tags": [],
                "Difficulty": "NA"
            })
        print(f"Processing: {cnt}/{len(args)-1}\t ",end='\r')
    print()
    with open('html/scripts/URIs.json', 'w') as f:
        f.write(json.dumps(output, indent=4, sort_keys=True))
    print("Dumped to html/scripts/URIs.json")

if __name__ == '__main__':
    main()