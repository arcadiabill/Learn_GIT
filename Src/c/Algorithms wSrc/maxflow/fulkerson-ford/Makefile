all:
	cl /W4 /ZI /GZ *.c
	./maxflow.exe < graph.inp
	cat maxflow.gv
	C:/view/graphviz/bin/gvedit.exe maxflow.gv &
