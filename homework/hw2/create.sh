#!/bin/bash
function depth() {
    local d=`expr $1 - 1`
    echo $3
    if [[ $1 -gt "0" ]]; then
        local i=0
	for (( i=0;i<$2;i++ )); do
	    depth $d $2 $3/$i
	done
    fi
}
depth=$1
breath=$2
seed="$3-$4"
#assume user will enter correct input as described in website
[[ $4 == "depth" ]] && df=1 || bf=1
#breath-frist
if [[ bf -eq "1" ]]; then
    open=($seed)
    for (( i=0;i<$depth;i++ )); do
        tmpopen=()
        for x in $open; do
	    for (( j=0;j<$breath;j++ )); do
	        tmp=$x/$j
		echo $tmp
	        tmpopen+=($tmp)
	    done
        done
	open=${tmpopen[@]}
    done
#depth-first
else
    depth $1 $2 $seed
fi
