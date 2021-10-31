GENERATES = move protect.so
TRASH = *.o
CFLAGS = -O2 -fPIC

all: move protect.so

protect.so: protect.o
	cc -shared $^ -o $@

move: main.o
	cc $^ -o $@

test: all
	./strace_tests.sh
	./preload_test.sh

clean:
	rm -f $(TRASH)

distclean: clean
	rm -rf $(GENERATES)