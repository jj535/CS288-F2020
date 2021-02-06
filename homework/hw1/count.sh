#!/bin/bash
chararr=(a b c d e f g h i j k l m n o p q r s t u v w x y z)
lst=`ls /bin`
charcnt=(0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0)
for x in $lst; do
	case $x in
		a*)
			((charcnt[0]++))
			;;
		b*)
			((charcnt[1]++));;
		c*)
			((charcnt[2]++));;
		d*)
			((charcnt[3]++));;
		e*)
			((charcnt[4]++));;
		f*)
			((charcnt[5]++));;
		g*)
			((charcnt[6]++));;
		h*)
			((charcnt[7]++));;
		i*)
			((charcnt[8]++));;
		j*)
			((charcnt[9]++));;
		k*)
			((charcnt[10]++));;
		l*)
			((charcnt[11]++));;
		m*)
			((charcnt[12]++));;
		n*)
			((charcnt[13]++));;
		o*)
			((charcnt[14]++));;
		p*)
			((charcnt[15]++));;
		q*)
			((charcnt[16]++));;
		r*)
			((charcnt[17]++));;
		s*)
			((charcnt[18]++));;
		t*)
			((charcnt[19]++));;
		u*)
			((charcnt[20]++));;
		v*)
			((charcnt[21]++));;
		w*)
			((charcnt[22]++));;
		x*)
			((charcnt[23]++));;
		y*)
			((charcnt[24]++));;
		z*)
			((charcnt[25]++));;
		*);;
	esac
done
for ((k=0;k<26;k++)); do
	echo ${chararr[$k]} ${charcnt[$k]}
done
