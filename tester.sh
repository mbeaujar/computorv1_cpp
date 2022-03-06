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
		printf "${YELLOW}$i${NC} -- $input\n\n"
		./computor "$input"
		printf "\n"
	done
}

subjects=(
	"5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0" 
	"5 * X^0 + 4 * X^1 = 4 * X^0"
	"8 * X^0 - 6 * X^1 + 0 * x^2 - 5.6 * X^3 = 3 * X^0"
	"3 * X^0 + 1 * X^1 = 0 * X^0 - 1 * X^1 - 3 * X^2" # Example in the video
)

second_negative=(
	"1 * X^2 - 3 * X^1 + 4 * X^0"
	"3 * X^2 + 4 * X^1 + 2 * X^0"
	"1 * X^2 - 4 * X^1 + 9 * X^0"
)

all_tests=("${subjects[@]}" "${second_negative[@]}")

for test in "${all_tests[@]}";
do
	test_with_inputs "$test"
done

# test_with_inputs "${second_negative[@]}"
# test_with_inputs "${subjects[@]}"
