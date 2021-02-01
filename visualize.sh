#!/bin/bash
red=`tput setaf 1`
green=`tput setaf 2`
reset=`tput sgr0`
START=1
END=6
cd .scripts
gcc ./../solutions/sol1.c -pthread -o 1.out
gcc ./../solutions/sol2.c -pthread -o 2.out
gcc ./../solutions/sol3.c -pthread -o 3.out
/usr/bin/printf "${green}\xE2\x9C\x94 Compiled${reset}"
./gen.sh
/usr/bin/printf "${green}\xE2\x9C\x94 Inputs Generated\n${reset}"
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
	for (( i=1; i<=3; i++ ))
	do
		LINE=0
		./$i.out < ./test/$1/inp$c.txt|
			while read j
			do
				let LINE=LINE+1
				if [ $LINE == 2 ]
				then
					if [ $j = "SORTED" ]
					then
						echo "SORTED" > res$i.txt
					elif [ $j = "NOT SORTED" ]
					then
						echo "NOT SORTED" > res$i.txt
					fi
				elif [ $LINE == 1 ]
				then
					echo $j > time$i.txt
				fi
			done
		done
	for (( i=1; i<=3; i++ ))
	do
	echo $(cat time$i.txt | grep -o '[0-9]*'|head -1) >> $1.$i.txt
	done	
	echo "($(cat ./test/$1/inp$c.txt))	$(cat time1.txt | grep -o '[0-9]*'|head -1)	$(colorize $(cat res1.txt))	$(cat time2.txt|grep -m 1 -o '[0-9]*'|head -1)	$(colorize $(cat res2.txt))	$(cat time3.txt|grep -m 1 -o '[0-9]*'|head -1)	$(colorize $(cat res3.txt))"
done
}
echo "				Graph-1		"
echo "(n p)	SOl-1			SOL-2			SOL-3"
graph_val "graph_1"
echo "				Graph-2		"
echo "(n p)	SOl-1			SOL-2			SOL-3"
graph_val "graph_2"
/usr/bin/printf "${green}\xE2\x9C\x94 Graphs Plotted\n${reset}"

( for (( i=1; i<=2; i++ ))
	do
		for (( j=1; j<=3; j++ ))
			do
				echo  "graph_$i.$j.txt"
			done
	done )|python.exe ./visualize.py
rm *.out
rm res*.txt
rm time*.txt
rm graph_*.txt
rm -r test
cd ..
/usr/bin/printf "${green}\xE2\x9C\x94 Cleanup \n${reset}"
echo "${red}Script Exited${reset}"


