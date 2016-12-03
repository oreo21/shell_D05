compile: shell.c
	gcc shellApp.c shellUtils.c -o shell

clean:
	rm *~ *# shell

run: shell
	./shell
