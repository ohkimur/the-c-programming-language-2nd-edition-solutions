#!/bin/bash

# check if file is present and executable
if [ ! -f expr ]; then
    echo "File 'expr' found!"
    exit 1
fi

if [ ! -x expr ]; then
    echo "File 'expr' not executable!"
    exit 1
fi

echo "=== Testing expr calculator ==="

# Test 1: Simple addition
T=1
result=$(./expr 2 3 +)
expected="result: 5.000"
if [[ "$result" == "$expected" ]]; then
    echo "Test $T PASS: 2 + 3 = 5"
else
    echo "Test $T FAIL: Expected '$expected', got '$result'"
fi

# Test 2: Commutativity of addition
T=2
result=$(./expr 3 2 +)
expected="result: 5.000"
if [[ "$result" == "$expected" ]]; then
    echo "Test $T PASS: 3 + 2 = 5"
else
    echo "Test $T FAIL: Expected '$expected', got '$result'"
fi

# Test 3: Subtraction
T=3
result=$(./expr 10 3 -)
expected="result: 7.000"
if [[ "$result" == "$expected" ]]; then
    echo "Test $T PASS: 10 - 3 = 7"
else
    echo "Test $T FAIL: Expected '$expected', got '$result'"
fi

# Test 4: Complex expression
T=4
# ------------------------------------
# Expected:
# 5 --> [5]
# 1 --> [5, 1]
# 2 --> [5, 1, 2]
# + --> (1 + 2 = 3) --> [5, 3]
# 4 --> [5, 3, 4]
# * --> (3 * 4 = 12) --> [5, 12]
# + --> (5 + 12 = 17) --> [17]
# 3 --> [17, 3]
# - --> (17 - 3 = 14) --> [14]
# ------------------------------------
result=$(./expr 5 1 2 + 4 \* + 3 -)
expected="result: 14.000"
if [[ "$result" == "$expected" ]]; then
    echo "Test $T PASS: Complex RPN expression"
else
    echo "Test $T FAIL: Expected '$expected', got '$result'"
fi

# Test 5: Division by zero
T=5
result=$(./expr 5 0 / 2>&1)
if [[ "$result" == *"division by zero"* ]]; then
    echo "Test $T PASS: Division by zero detected"
else
    echo "Test $T FAIL: Should detect division by zero"
fi

# Test 6: Missing operator
T=6
result=$(./expr 5 1)
expected="Error: Operator is missing!"
if [[ "$result" == "$expected" ]]; then
    echo "Test $T PASS: Missing operator"
else
    echo "Test $T FAIL: Expected '$expected', got '$result'"
fi

echo "=== Tests Complete ==="