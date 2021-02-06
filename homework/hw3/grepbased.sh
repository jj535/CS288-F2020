#!/bin/bash

cat $1 | grep -o "aria-label=\"\(.*\) views\" title=\"" | grep -v "&" | while read x; do echo `expr "$x" : "aria-label=\"\(.*\)\" title=\""`;done | grep 'ago' | grep 'by' | grep 'views' > clips.txt
grep -v "&" clips.txt | grep -oP ".*(?= by )" > titles.txt
grep -v "&" clips.txt | grep -oP '(?<= by ).* (?=[0-9][0-9]* .* ago)' > users.txt
grep -v "&" clips.txt | grep -o 'by \(.*\) ago' | grep -o "[0-9]\+ .* ago" > upload.txt
grep -v "&" clips.txt | grep -oP "(?>ago )\K.* (?=[0-9,]* views)" | while read x; do s=${x//,}; echo $s; done > duration.txt
grep -v "&" clips.txt | grep -oP "(?=ago \K).*(?=s \K).*(?= views)" | while read x; do echo ${x//,}; done > views.txt

paste titles.txt users.txt duration.txt upload.txt views.txt > youtube.csv

