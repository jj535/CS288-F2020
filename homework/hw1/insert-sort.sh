#!/bin/bash

lst=()
for x in $@; do
    lst+=( $x )
done

#echo ${lst[@]}

for (( x=1; x<${#lst[@]}; x++)); do
    key=${lst[x]}
    j=$[x-1]
#    echo $j
    while [[ "$j" -ge "0" && ${lst[j]} -gt $key ]]
	do
	k=$[j+1]
	tmp=${lst[j]}
	lst[k]=$tmp
	((j--))
    done
    ((j++))
    lst[j]=$key
done

echo ${lst[@]}
