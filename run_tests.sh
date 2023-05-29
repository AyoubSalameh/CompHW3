#!/bin/bash

# Define color codes
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Define the path to your executable
EXECUTABLE="./hw3"

# Define the directory paths for test files, expected output files, and actual output files
TEST_DIR="./tests/in"
EXPECTED_DIR="./tests/expected"
ACTUAL_DIR="./tests/actual"

# Create the actual output directory if it doesn't exist
mkdir -p "$ACTUAL_DIR"

# Iterate over the test files in the directory
for test_file in "$TEST_DIR"/*.in; do
    # Extract the test file name without the extension
    test_filename=$(basename "$test_file" .in)
    # Construct the corresponding expected output file path
    expected_file="$EXPECTED_DIR/$test_filename.in.out"
    # Construct the actual output file path
    actual_file="$ACTUAL_DIR/$test_filename.actual"

    # Run the test file and redirect the output to the actual output file
    "$EXECUTABLE" < "$test_file" > "$actual_file"

    # Compare the actual output file with the expected output file
    if diff -q "$actual_file" "$expected_file" >/dev/null; then
        echo -e "${GREEN}$test_filename: PASSED${NC}"
    else
        echo -e "${RED}$test_filename: FAILED${NC}"
    fi
done
