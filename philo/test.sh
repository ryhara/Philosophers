#!/bin/bash

# test case
# no one shoud die
# 5 800 200 200
# 5 600 150 150
# 4 410 200 200
# 100 800 200 200
# 105 800 200 200
# 200 800 200 200

# die
# 1 800 200 200
# 4 310 200 100
# 4 200 205 200

# stop
# 5 800 200 200 7
# 4 410 200 200 10

# error
# -5 600 200 200
# 4 -5 200 200
# 4 600 -5 200
# 4 600 200 -5
# 4 600 200 200 -5

# パラメータを表示する関数を定義
print_params() {
    param_value=$1
    param_name=$2
    echo "$param_name: $param_value"
}

# チェック関数を定義
check_philo() {
    if [ ! -x "./philo" ]; then
        make re
    fi
}

# 引数が４つの場合の処理関数を定義
process_with_4_args() {
    num1=$1
    num2=$2
    num3=$3
    num4=$4

    check_philo
    echo "---------------------------"
    print_params $num1 "number_of_philosophers"
    print_params $num2 "time_to_die"
    print_params $num3 "time_to_eat"
    print_params $num4 "time_to_sleep"
    echo "---------------------------"
    ./philo $num1 $num2 $num3 $num4 > result
    grep died result > result2
    grep -o "[0-9]* [0-9]*" result2 > result3
    id=$(cat result3 | awk '{print $2}')
    cat result | grep " $id "

    rm result result2 result3
}

# 引数が５つの場合の処理関数を定義
process_with_5_args() {
    num1=$1
    num2=$2
    num3=$3
    num4=$4
    num5=$5

    check_philo
    echo "---------------------------"
    print_params $num1 "number_of_philosophers"
    print_params $num2 "time_to_die"
    print_params $num3 "time_to_eat"
    print_params $num4 "time_to_sleep"
    print_params $num5 "number_of_times_each_philosopher_must_eat"
    echo "---------------------------"
    ./philo $num1 $num2 $num3 $num4 $num5 > result

    eating_count=$(cat result | grep 'is eating' | wc -l)
    expected_count=$((num1 * num5))

    if [ $eating_count -ge $num5 ]; then
        echo -e "\033[0;32mEating count is greater than or equal to expected: $eating_count (Expected: $expected_count)\033[0m"
    else
        echo -e "\033[0;31mEating count is less than expected: $eating_count (Expected: $expected_count)\033[0m"
    fi


    rm result
}

if [ $# -eq 4 ]; then
    process_with_4_args $@
elif [ $# -eq 5 ]; then
    process_with_5_args $@
else
    echo "Usage: $0 number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]"
    exit 1
fi
