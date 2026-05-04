#!/bin/bash
# Usage: ./test.sh

CALC='./calc-cli'
PASS=0
FAIL=0

run_test() {
    local description="$1"
    local input="$2"
    local expected="$3"

    local actual
    actual=$($CALC "$input" 2>&1)

    if [ "$actual" = "$expected" ]; then
        echo "  PASS  $description"
        ((PASS++))
    else
        echo "  FAIL  $description"
        echo "        input:    $input"
        echo "        expected: $expected"
        echo "        got:      $actual"
        ((FAIL++))
    fi
}

echo "=== Basic operations ==="
run_test "basic sum"            "1+2"   "3"
run_test "basic subtraction"    "10-3"  "7"
run_test "multiplication"       "4*5"   "20"
run_test "exact division"       "10/2"  "5"
run_test "division"             "1/3"   "0.3333333333"
run_test "module"               "10%3"  "1"
run_test "exponentiation"       "2^10"  "1024"

echo ""
echo "=== Precedence and parentheses ==="
run_test "precedence */+"           "2+3*4"         "14"
run_test "parentheses force sum"    "(2+3)*4"       "20"
run_test "multiple parentheses"     "((2+3)*4)+1"   "21"
run_test "brackets"                 "{2+3}*[4+1]"   "25"

echo ""
echo "=== Unary minus ==="
run_test "simple negative"          "-5+3"      "-2"
run_test "negative in parentheses"  "(-5)*2"    "-10"
run_test "double negation"          "--5"       "5"
run_test "negative in power"        "-2^2"      "-4"

echo ""
echo "=== Constants ==="
run_test "pi*0"         "pi*0"      "0"
run_test "pi"           "pi"        "3.141592654"
run_test "e^1"          "e^1"       "2.718281828"
run_test "e^0"          "e^0"       "1"

echo "=== Right-associativity of ^ ==="
run_test "2^3^2 = 2^(3^2) = 512"     "2^3^2"           "512"
run_test "2^2^3 = 2^(2^3) = 256"     "2^2^3"           "256"
run_test "4^3^2 = 4^(3^2) = 262144"  "4^3^2"           "262144"
 
echo ""
echo "=== Unary minus interactions ==="
run_test "---5 = -5"                "---5"          "-5"
run_test "----5 = 5"                "----5"         "5"
run_test "-2^2 = -(2^2) = -4"       "-2^2"          "-4"
run_test "-(2^2) = -4"              "-(2^2)"        "-4"
run_test "(-2)^2 = 4"               "(-2)^2"        "4"
run_test "(-2)^3 = -8"              "(-2)^3"        "-8"
run_test "-sqrt(4) = -2"            "-sqrt(4)"      "-2"
run_test "sqrt(-1*-1) = 1"          "sqrt(-1*-1)"   "1"
 
echo ""
echo "=== Operator precedence ==="
run_test "2+3*4-1 = 13"         "2+3*4-1"       "13"
run_test "10-2*3+1 = 5"         "10-2*3+1"      "5"
run_test "2*3+4*5 = 26"         "2*3+4*5"       "26"
run_test "100/10/2 = 5"         "100/10/2"      "5"
run_test "2^3*4 = 32"           "2^3*4"         "32"
run_test "4*2^3 = 32"           "4*2^3"         "32"

echo ""
echo "=== Functions ==="
run_test "sqrt(4)"              "sqrt(4)"       "2"
run_test "sqrt(2)"              "sqrt(2)"       "1.414213562"
run_test "log(100)"             "log(100)"      "2"
run_test "log(1)"               "log(1)"        "0"
run_test "ln(e)"                "ln(e)"         "1"
run_test "sin(0)"               "sin(0)"        "0"
run_test "cos(0)"               "cos(0)"        "1"
run_test "sin(pi)"              "sin(pi)"       "0"
 
echo ""
echo "=== Nested functions ==="
run_test "sqrt(sqrt(16)) = 2"       "sqrt(sqrt(16))"    "2"
run_test "log(10^3) = 3"            "log(10^3)"         "3"
run_test "ln(e^5) = 5"              "ln(e^5)"           "5"
run_test "sqrt(2^2+2^2) = 2"        "sqrt(2^2+2^2)"     "2.828427125"
run_test "log(sqrt(100)) = 1"       "log(sqrt(100))"    "1"
 
echo ""
echo "=== Trig identities ==="
run_test "sin(pi/6)*2 = 1"          "sin(pi/6)*2"               "1"
run_test "cos(pi/3)*2 = 1"          "cos(pi/3)*2"               "1"
run_test "tan(pi/4) = 1"            "tan(pi/4)"                 "1"
run_test "sin(pi/4)^2+cos(pi/4)^2"  "sin(pi/4)^2+cos(pi/4)^2"   "1"
 
echo ""
echo "=== Constants in expressions ==="
run_test "e^ln(7) = 7"              "e^ln(7)"       "7"
run_test "log(10^pi) ~= pi"         "log(10^pi)"    "3.141592654"
run_test "2*pi > 6"                 "2*pi"          "6.283185307"
run_test "e^1 = e"                  "e^1-e"         "0"
 
echo ""
echo "=== Expressions ==="
run_test "10^10 - 2^31"             "10^10-2^31"                "7852516352"
run_test "2^32 = 4294967296"        "2^32"                      "4294967296"
run_test "sqrt(1000000) = 1000"     "sqrt(1000000)"             "1000"
run_test "1/1000000"                "1/1000000"                 "1e-06"
run_test "e^3 + log(57)"            "e^3+log(57)"               "21.84141178"
run_test "sqrt(2)^2"                "sqrt(2)^2"                 "2"
run_test "sin^2 + cos^2 = 1"        "sin(pi/4)^2+cos(pi/4)^2"   "1"

echo ""
echo "=== Expected errors ==="
error_test() {
    local description="$1"
    local input="$2"
    local actual
    actual=$($CALC "$input" 2>&1)
    if echo "$actual" | grep -qE "^[0-9]"; then
        echo "  FAIL  $description (should error, returned '$actual')"
        ((FAIL++))
    else
        echo "  PASS  $description (expected: '$actual')"
        ((PASS++))
    fi
}

error_test "unbalanced parentheses" "(2+3"
error_test "invalid character"      "2#3"
error_test "module with float"      "2.5%1.5"

echo ""
echo "=============================="
echo "  $PASS passed, $FAIL failed"
echo "=============================="