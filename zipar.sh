#!/bin/bash

NAME="ed2-trab3-AthusCavalini-KelvinSantos"

FILE="$NAME.zip"

if [ -f "$FILE" ]; then
    rm "$FILE"
fi

# mkdir -p "$NAME/"

ln -s -r -T "codigo/" "$NAME"
# ln -s -r -T "doc/" "$NAME/doc"

zip "$FILE" -r  "$NAME/"

rm -r "$NAME"
