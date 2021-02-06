#!/bin/bash

cat $1 | grep -o "aria-label=\"\(.*\) views\" title=\"" | grep -v "&" | while read x; do echo `expr "$x" : "aria-label=\"\(.*\)\" title=\""`;done | grep 'ago' | grep 'by' | grep 'views' > clips.txt
echo > titles.txt > duration.txt > users.txt > views.txt > upload.txt

grep -v "&" clips.txt | sed 's/\(.*\) by \(.*\) \([0-9]* .*\) ago \(.*\) \([0-9,]* views\)/\1IIII\2IIII\3IIII\4IIII\5/g' | sed 's/,//g' | sed 's/IIII/,/g' | paste > youtube.csv
