#!/bin/bash
CURR_DIR=$(pwd)
mkdir test
cd test
mkdir graph_1
mkdir graph_2
cd graph_1
for (( c=1,i=1; c<7; c++,i++ ))
do
	echo 14 $c >>inp$i.txt
done
cd ..
cd graph_2
for (( c=13,i=1; c<19; c++,i++ ))
do
	echo $c 4 >>inp$i.txt
done
cd $CURR_DIR
 
echo


