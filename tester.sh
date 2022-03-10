#!/bin/bash

# calculator quadratic equation
# https://www.calculatorsoup.com/calculators/algebra/quadratic-formula-calculator.php

# calculator first degree equation
# https://www.123calculus.com/en/first-degree-equation-page-1-25-100.html

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
		printf "${YELLOW}$i${NC} --> $input\n\n"
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

three=(
	"3 * X^3 + 2 * X^2 = 1 * X^1 + 2 * X^0"
)

infinite_solution=(
	"2 * X^1 + 3 * X^0 = 2 * X^1 + 3 * X^0"
	"42 * X^0 = 42 * X^0"
	"0 * 0 = 0"
)

no_solution=(
	"42 * X^0 = 43 * X^0"
	"20 * X^1 + 42 * X^0 = 20 * X^1  + 10 * X^0"
	"1 * 1 = 0"
)

multiplication=(
	"1x * 2x^2 = 1000000"
	"2 * 2 * 2 + 6x = 8"
	"80 = 14x * 4 * 5"
	"1x * 2x = 80"
	"1x * 2x = 40 * 2"
)

fraction=(
	"1/2x - 1/3 = 80"
	"1/2x * 1/2x + 80 = -60"
	"6/0x = 6"
	"6/0 = 6"
	"0/6 = 0"
)

parsing=(
	"2 / 6 = 0"
	"1+1+1+1+1+ = 5"
	"+ 5 = 5"
	"0 - - 5 = 5"
	"1x^ + 5 = 0"
)

function all_test() {
	all_tests=("$@")
	for test in "${all_tests[@]}";
	do
		# echo "$test"
		test_with_inputs "$test"
	done
}

# all_test "${subjects[@]}" "${second_negative[@]}" "${second_positive[@]}" "${second_neutral[@]}" "${first[@]}" "${three[@]}"

# test_with_inputs "${no_solution[@]}"
# test_with_inputs "${subjects[@]}"
# test_with_inputs "${multiplication[@]}"
# test_with_inputs "${fraction[@]}"
# test_with_inputs "${parsing[@]}"
# test_with_inputs "${first[@]}"
# test_with_inputs "${second_negative[@]}"
# test_with_inputs "${second_positive[@]}"
