#!/bin/bash
red=`tput setaf 1`
green=`tput setaf 2`
reset=`tput sgr0`
START=1
END=5
gcc sol1.c -pthread -o first.out
gcc sol2.c -pthread -o second.out
./gen.sh
function colorize()
{
	if [ $1 = "SORTED" ]
	then
		echo "${green} $1 ${reset}"
	else [ $1 = "NOT SORTED" ]
		echo "${red} NOT SORTED ${reset}"
	fi
}
function graph_val()
{
for (( c=$START; c<=$END; c++ ))
do
	LINE=0
	./first.out < ./test/$1/inp$c.txt|
		while read i
		do
		let LINE=LINE+1
		if [ $LINE == 2 ]
		then
			if [ $i = "SORTED" ]
			then
				echo "SORTED" > res1.txt
			elif [ $i = "NOT SORTED" ]
			then
				echo "NOT SORTED" > res1.txt
			fi
		elif [ $LINE == 1 ]
		then
			echo $i > time1.txt
		fi
		done
	LINE=0
	./second.out < ./test/$1/inp$c.txt |
	while read i
	do
	let LINE=LINE+1
	if [ $LINE == 2 ]
		then
			if [[ $i = "SORTED" ]]
			then
				echo "SORTED" > res2.txt
			elif [[ $i = "NOT SORTED" ]]
			then
				echo "NOT SORTED" > res2.txt
			fi
		elif [ $LINE == 1 ]
		then
			echo $i > time2.txt
	fi
	done
	
	echo "$(cat time1.txt | grep -o '[0-9]*'|head -1)	$(colorize $(cat res1.txt))	$(cat time2.txt|grep -m 1 -o '[0-9]*'|head -1)	$(colorize $(cat res2.txt))"
	# echo "$(cat time1.txt | grep -o '[0-9]*'|head -1)	$(cat res1.txt)	$(cat time2.txt|grep -m 1 -o '[0-9]*'|head -1)	$(cat res2.txt)"
	
done
}
for (( i=1; i<=2; i++))
do
echo "		Graph-$i		"
echo "	SOl-1		SOL-2"
graph_val "graph_$i"
done

rm *.out
rm res*.txt
rm time*.txt
rm -r test

echo


