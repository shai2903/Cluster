FLAGS = -ansi -Wall -Wextra -Werror -pedantic-errors
LIBS = -lm

all:cluster 
clean:
	rm -rf *.o cluster cluster_linked_list spmat Helper ModMatrix LinkedList LinkedListCol

cluster : Helper.o ModMatrix.o spmat_linked_list.o main.o LinkedList.o LinkedListCol.o MainAlgorithem.o
	gcc spmat_linked_list.o Helper.o ModMatrix.o main.o LinkedList.o LinkedListCol.o MainAlgorithem.o -o cluster $(LIBS)

Helper.o: Helper.c Helper.h
	gcc $(FLAGS) -c Helper.c

spmat_linked_list.o: spmat_linked_list.c spmat.h Helper.h LinkedListCol.h
	gcc $(FLAGS) -c spmat_linked_list.c

ModMatrix.o: ModMatrix.c ModMatrix.h spmat.h Helper.h
	gcc $(FLAGS) -c ModMatrix.c


main.o: main.c ModMatrix.h Helper.h MainAlgorithem.h
	gcc $(FLAGS) -c main.c

LinkedList.o : LinkedList.c main.h
	gcc $(FLAGS) -c LinkedList.c 

LinkedListCol.o: LinkedListCol.c 
	gcc $(FLAGS) -c LinkedListCol.c 


MainAlgorithem.o: MainAlgorithem.c MainAlgorithem.h Helper.h
	gcc $(FLAGS) -c MainAlgorithem.c