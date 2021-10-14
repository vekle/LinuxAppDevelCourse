#!/bin/bash

delay=${1}

if [[ ! $delay =~ ^[+-]?[0-9]+\.?[0-9]*$ ]]; then
    echo "Usage: ./randomize.sh <<delay>>"
    exit 1
fi

lines=""
line_num=0
file_size=0

char_x=()
char_y=()

IFS=$'\n' 
while read line; do
    lines+=$line
    line_size=${#line}
    echo ${line_size}

    for (( i=0; i<${line_size}; i++ )); do
        char_x+=(${i})
        char_y+=(${line_num})
    done

    file_size=$((${file_size}+${line_size}))
    line_num=$((${line_num}+1))
done

tput init
tput clear

for i in $(seq 0 $((${file_size} - 1)) | shuf); do
    x=${char_x[i]}
    y=${char_y[i]}

    tput cup ${y} ${x}
    echo -n ${lines:${i}:1}

    sleep ${delay}
done

