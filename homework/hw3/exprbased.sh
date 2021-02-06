#!/bin/bash

cat $1 | grep -o "aria-label=\"\(.*\) views\" title=\"" | grep -v "&" | while read x; do echo `expr "$x" : "aria-label=\"\(.*\)\" title=\""`;done | grep 'ago' | grep 'by' | grep 'views' > clips.txt
cat clips.txt | while read x; do s=`expr "$x" : "\(.*\) by.*"`; echo ${s//,}; done > titles.txt
cat clips.txt | while read x; do echo `expr "$x" : ".* by \(.*\) [0-9].*ago.*"`; done > users.txt
cat clips.txt | while read x; do echo `expr "$x" : ".* by .* \([0-9].*\) ago.*"`; done > upload.txt
cat clips.txt | while read x; do s=`expr "$x" : ".*ago \(.*\) [,0-9].* views"`; echo ${s//,}; done > duration.txt
cat clips.txt | while read x; do s=`expr "$x" : ".* \([,0-9].*\)views"`; echo ${s//,}; done > views.txt


paste titles.txt users.txt duration.txt upload.txt views.txt > youtube.csv
