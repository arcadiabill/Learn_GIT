all:
	gcc *.c
	./maxflow.exe < graph.inp
	cat maxflow.gv
	C:/view/graphviz/bin/gvedit.exe maxflow.gv &

clean:
	del *.exe
