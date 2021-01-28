.SILENT: run
compile:
	gcc sol1.c -pthread -o first.out
	gcc sol2.c -pthread -o second.out
graph1:
	echo --------------------
	./first.out < ./test/graph_1/inp1.txt
	./second.out < ./test/graph_1/inp1.txt
	echo --------------------
	./first.out < ./test/graph_1/inp2.txt
	./second.out < ./test/graph_1/inp2.txt
	echo --------------------
	./first.out < ./test/graph_1/inp3.txt
	./second.out < ./test/graph_1/inp3.txt
	echo --------------------
	./first.out < ./test/graph_1/inp4.txt
	./second.out < ./test/graph_1/inp4.txt
	echo ---------------------
	./first.out < ./test/graph_1/inp5.txt
	./second.out < ./test/graph_1/inp5.txt
graph2:
	echo ---------------------
	./first.out < ./test/graph_2/inp1.txt
	./second.out < ./test/graph_2/inp1.txt
	echo ---------------------
	./first.out < ./test/graph_2/inp2.txt
	./second.out < ./test/graph_2/inp2.txt
	echo ---------------------
	./first.out < ./test/graph_2/inp3.txt
	./second.out < ./test/graph_2/inp3.txt
	echo ---------------------
	./first.out < ./test/graph_2/inp4.txt
	./second.out < ./test/graph_2/inp4.txt
	echo ---------------------
	./first.out < ./test/graph_2/inp5.txt
	./second.out < ./test/graph_2/inp5.txt

clean:
	rm *.out
