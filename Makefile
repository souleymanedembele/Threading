
all: single_thread multi_thread

clean:
	rm -f single_thread multi_thread
single_thread: p1.c
	gcc -o single_thread single_thread.c -Wall

multi_thread: multi_thread.c
	gcc -o multi_thread multi_thread.c -Wall -pthread
