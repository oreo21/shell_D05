compile: shell.c
	gcc shell.c -o shell

clean:
	rm *~ *# shell

run: shell
	./shell
