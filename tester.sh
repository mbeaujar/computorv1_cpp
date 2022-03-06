#!/bin/bash

# calculator quadratic equation
# https://www.calculatorsoup.com/calculators/algebra/quadratic-formula-calculator.php

# Tuto script bash
# https://askubuntu.com/questions/674333/how-to-pass-an-array-as-function-argument

### COLORS ###

GREEN='\033[1;32m'
YELLOW='\033[1;33m'
RED='\033[1;31m'
NC='\033[0m'

### FILES ###

if [ ! -f ./computor ]; then
	printf "${RED}Executable ./computor does not exist${NC}\n"
	exit 1
fi

i=0
function test_with_inputs() {
	inputs=("$@")
	for input in "${inputs[@]}";
	do
		i=$(($i + 1))
		printf "\n"
		printf "${YELLOW}$i${NC} -- $input\n\n"
		./computor "$input"
	done
}

subjects=(
	"5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0" 
	"5 * X^0 + 4 * X^1 = 4 * X^0"
	"8 * X^0 - 6 * X^1 + 0 * x^2 - 5.6 * X^3 = 3 * X^0"
	"3 * X^0 + 1 * X^1 = 0 * X^0 - 1 * X^1 - 3 * X^2" # Example in the video
)


first=(
	"5 * X^1 - 4 * X^0 = 0 * X^0"
	"8 * X^1 + 20 * X^0 = 0 * X^0"
	"1 * X^1 = 10 * X^0"
	"1 * X^1 - 10 * X^0 = 100 * X^1 + 100 * X^0" 
)

second_positive=(
	"1 * X^2 - 11 * X^1 + 30 * X^0 = 0 * X^0"
	"4 * X^2 + 11 * X^1 - 3 * X^0 = 0 * X^0"
	"2 * X^2 + 8 * X^1 - 16 * X^0 = 0 * X^0"
	"1 * X^2 - 4 * X^1 - 21 * X^0 = 0 * X^0"
)

second_neutral=(
	"1 * X^2 - 6 * X^1 + 9 * X^0 = 0 * X^0"
	"1 * X^2 - 2 * X^1 + 1 * X^0 = 0 * X^0"
	"4 * X^2 + 32 * X^1 + 64 * X^0 = 0 * X^0"
)

second_negative=(
	"1 * X^2 - 3 * X^1 + 4 * X^0 = 0 * X^0"
	"3 * X^2 + 4 * X^1 + 2 * X^0 = 0 * X^0"
	"1 * X^2 - 4 * X^1 + 9 * X^0 = 0 * X^0"
	"3 * X^2 + 2 * X^1 + 4 * X^0 = 0 * X^0"
	"1 * X^2 - 1 * X^1 + 30 * X^0 = 0 * X^0"
)

function all_test() {
	all_tests=("$@")
	for test in "${all_tests[@]}";
	do
		# echo "$test"
		test_with_inputs "$test"
	done
}

# all_test "${subjects[@]}" "${second_negative[@]}" "${second_positive[@]}" "${second_neutral[@]}"

# test_with_inputs "${subjects[@]}"
test_with_inputs "${first[@]}"
# test_with_inputs "${second_negative[@]}"
