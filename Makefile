heap: asst6.c
	gcc -o heap asst6.c heap.c

run: 
	./heap

clean: 
	rm heap

debug: 
	gcc -g -o heap asst6.c heap.c
	gdb heap

