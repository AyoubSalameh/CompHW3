#!/bin/bash

# Define color codes
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

make all
test_folder_name="newtests"
command="./hw3" #change this to your name of file, keep the ''./''

for ((i=1; i<=58; i++))
do
    filename="$test_folder_name/t${i}.in"
    filename_our_out="$test_folder_name/t${i}.our.out"
    filename_out="$test_folder_name/t${i}.out"
    if [ -f "$filename" ]; then
	    "$command" < "$filename" >"$filename_our_out"
        if diff -q "$filename_our_out" "$filename_out" >/dev/null; then
            echo -e "${GREEN}$filename: PASSED${NC}"
        else
            echo -e "${RED}$filename: FAILED${NC}"
            # echo "diffing test no.${i}"
            # diff "$filename_out" "$filename_our_out"
        fi
    
    else
        echo "File not found: $filename"
    fi

done

