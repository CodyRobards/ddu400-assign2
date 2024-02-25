all: compC compJava runC runJava 

compC: prog.c prog.h
	gcc -o prog prog.c -pthread 

runC: prog
	./prog 10 
	./prog 1000 
	./prog 5000 
	./prog 10000      

compJava: prog_j.java SorterThread.java MergerThread.java
	javac prog_j.java SorterThread.java MergerThread.java

runJava: prog_j.class SorterThread.class MergerThread.class 
	java prog_j 10 
	java prog_j 1000 
	java prog_j 5000
	java prog_j 10000 

clean:
	rm *.o *.class prog

