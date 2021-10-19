GENERATES = range
TRASH = *.o
CFLAGS = -O0 -g

all: range

range: main.o range.o

range.o: range.h

test: all
	gdb -x tests/test_1.py | grep @@@ | cut -c 5- > tests/test_1
	cmp tests/test_1 tests/test_1_true

	gdb -x tests/test_2.py | grep @@@ | cut -c 5- > tests/test_2
	cmp tests/test_2 tests/test_2_true

	rm tests/test_1 tests/test_2

clean:
	rm -f $(TRASH)

distclean: clean
	rm -rf $(GENERATES)