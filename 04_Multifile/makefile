GENERATES = prog prog-a prog-so liboutput_static.a liboutput.so README
TRASH = *.o *~ o.*
CFLAGS = -fPIC

all: README prog prog-a prog-so liboutput_static.a liboutput.so

prog: const.o fun.o prog.o

prog-so: liboutput.so prog.o
	cc -L. prog.o -loutput -o prog-so

prog-a: liboutput_static.a prog.o
	cc -L. prog.o -loutput_static -o prog-a

README: prog
	./$< 2> $@

fun.o: outlib.h

liboutput_static.a: fun.o const.o
	ar -rcs $@ $^

liboutput.so: fun.o const.o
	cc -shared $^ -o $@

test: all
	rm -f file*

	./prog 2> file
	./prog-a 2> file-a
	LD_LIBRARY_PATH=`pwd` ./prog-so 2> file-so

	sed -i -e 's/prog-a/prog/g' ./file-a
	sed -i -e 's/prog-so/prog/g' ./file-so

	cmp file file-a;
	cmp file file-so;

	rm -f file*

	./prog 42 >> file
	./prog-a 42 >> file-a
	LD_LIBRARY_PATH=`pwd` ./prog-so 42 >> file-so

	cmp file file-a;
	cmp file file-so;

	rm -f file*

	./prog baba keke lulu >> file
	./prog-a baba keke lulu >> file-a
	LD_LIBRARY_PATH=`pwd` ./prog-so baba keke lulu >> file-so

	cmp file file-a;
	cmp file file-so;

	rm -f file*

clean:
	rm -f $(TRASH)

distclean: clean
	rm -rf $(GENERATES)