#!/bin/bash

for ((i=0;i<60;i++)); do
	cdate=`date +"%Y_%m_%d_%H_%M_%S"`
	hfn=yahoo_${cdate}.html
	wget -O $hfn https://finance.yahoo.com/most-active
	xhfn=yahoo_${cdate}.xhtml
	java -jar tagsoup-1.2.1.jar --files $hfn
	python3 db.py $xhfn
	sleep 60
done
