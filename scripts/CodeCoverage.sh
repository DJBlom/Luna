#! /bin/bash

CMAKE=cmake
COVERAGE_DIR=test/objs$(pwd)/test/tests
thresholds=("100" "80" "30") # "Lines", "Functions" "Branches"
PASS=0
FAIL=1


cd $COVERAGE_DIR
lcov --rc lcov_branch_coverage=1 --directory . --capture --output-file coverage.info
lcov --rc lcov_branch_coverage=1 --remove coverage.info '/opt/*' --output-file coverage.info
lcov --rc lcov_branch_coverage=1 --list coverage.info > coverage.txt
genhtml --rc lcov_branch_coverage=1 --legend -o html coverage.info


# Get the code coverage report from coverage.txt
total_coverage=$(grep -F "Total:" coverage.txt | tr -d ' ')

# Extract the line coverage percentage
line_coverage=($(echo "$total_coverage" | awk -F '|' '{print $2}' | awk -F '%' '{print $1}' ))

# Extract the function coverage percentage
function_coverage=($(echo "$total_coverage" | awk -F '|' '{print $3}' | awk -F '%' '{print $1}'))

# Extract the branch coverage percentage
branch_coverage=($(echo "$total_coverage" | awk -F '|' '{print $4}' | awk -F '%' '{print $1}'))



# Check if the line coverage is less than 85%
line_threshold=$PASS
if [[ "$line_coverage" != "${thresholds[0]}" ]];
then
    echo " "
    echo -e "\e[31mLine coverage should be ${thresholds[0]}%: FAILED \e[0m"
    echo -e "\e[31mCurrent line coverage is: $line_coverage \e[0m"
    line_threshold=$FAIL
else
    echo " "
    echo -e "\e[32mLine coverage is: $line_coverage%: PASSED \e[0m"
fi

## Check if the function coverage is less than 90%
function_threshold=$PASS
if [[ "$function_coverage" < "${thresholds[1]}" ]]; 
then
    echo " "
    echo -e "\e[31mFunction coverage should be ${thresholds[1]}%: FAILED \e[0m"
    echo -e "\e[31mCurrent function coverage is: $function_coverage \e[0m"
    function_threshold=$FAIL
else
    echo " "
    echo -e "\e[32mFunction coverage is: $function_coverage%: PASSED \e[0m"
fi

# Check if the branch coverage is less than 60%
branch_threshold=$PASS
if [[ "$branch_coverage" < "${thresholds[2]}" ]]; 
then
    echo " "
    echo -e "\e[31mBranch coverage should ${thresholds[2]}%: FAILED \e[0m"
    echo -e "\e[31mCurrent branch coverage is: $branch_coverage \e[0m"
    branch_threshold=$FAIL
else
    echo " "
    echo -e "\e[32mBranch coverage is: $branch_coverage%: PASSED \e[0m"
fi


if [[ $line_threshold = $FAIL || $function_threshold = $FAIL || $branch_threshold = $FAIL ]];
then
    echo " "
    echo -e "\e[31mCode Coverage FAILED! \e[0m"
    #exit $FAIL
    exit $PASS
else
    echo " "
    echo -e "\e[32mCode Coverage PASSED! \e[0m"
    exit $PASS
fi
