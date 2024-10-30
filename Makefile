build:
	gcc -std=gnu11 -g -o quadtree main.c coada.c implementare.c
run:
	./quadtree
clean:
	rm quadtree
