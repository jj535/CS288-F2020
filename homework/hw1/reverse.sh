#!/bin/bash

function reverse() {
    while [ "$#" -gt "0" ]; do
	local tmp=$1
	shift
	rtn+=( $tmp )
    done
    ind=${#rtn[@]}
    (( ind-- ))


    for (( i=ind;i>=0;i-- )); do
        local tmpind=$[$ind-$i]
	final[$tmpind]=${rtn[i]}
    done

}

function main() {
    lst=( `ls $@` )
    reverse ${lst[@]}
    echo ${final[@]}
}

rtn=()
final=()
main $@
