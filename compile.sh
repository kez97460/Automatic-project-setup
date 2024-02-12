#!/bin/bash

pyinstaller -n aps -F main.py
mv ./dist/aps ./aps
rm -r ./dist 
rm -r ./build