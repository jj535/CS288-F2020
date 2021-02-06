#!/bin/bash

#average computes average and set it to global variable avg
function average() {
    value=0
    cnt=0
    shift
    shift
    while [[ "$#" -gt "0" ]]; do
#	echo $value
	value=$(($value + $1))
	((cnt++))
	shift
	shift
    done

    #if there's 0 parament is passed, then I will just say average is 0
    if [ "$cnt" -ne "0" ]; then
	avg=$((value/cnt))
#	echo $avg
    else
	avg=0
    fi
}

#this function filters any file/directory which has size less than avg(global variable)
function filter() {
    shift
    shift
    while [[ "$#" -gt "0" ]]; do
	size=$1
	shift
	[[ "$size" -gt "$avg" ]] && filtered_list+=($1)
	shift
    done
}


#main calls average to get avg and filters file/directory, then prints filtered list
function main() {
    filtered_list=()
    average `ls -s $@`
    filter `ls -s $@`
    echo ${filtered_list[@]}
}

main $@
