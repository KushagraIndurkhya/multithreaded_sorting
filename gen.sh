#!/bin/bash
START=1
END=5
CURR_DIR=$(pwd)
mkdir test
cd test
mkdir graph_1
mkdir graph_2
cd graph_1
for (( c=$START; c<=$END; c++ ))
do
	let x=$c+1
	echo 12 $x >>inp$c.txt
done
cd ..
cd graph_2
for (( c=$START; c<=$END; c++ ))
do
	let x=$c+10
	echo $x 5 >>inp$c.txt
done
cd $CURR_DIR
 
echo


