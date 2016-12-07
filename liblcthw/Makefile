# Made some adjustments for building with MS Visual Studio on Windows OS
# @project properties (Alt + F7):
# General->Configuration Type->Makefile;
# Debugging->Command->tests\list_algos_wiki_tests.exe
# NMake->General->Build Command line->make
# NMake->General->Clean Command line->make clean
# VC++ Directories->Include Directories->C:\Users\Atom\Source\Repos\C_code\liblcthw\tests;C:\Users\Atom\Source\Repos\C_code\liblcthw\src;$(IncludePath)
# Source Directories->C:\Users\Atom\Source\Repos\C_code\liblcthw\src\lcthw;$(SourcePath)

#CFLAGS=-g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
#CFLAGS=-g -Wall -Wextra -Isrc -Itests -Lbuild -Wl,--export-dynamic -export-dynamic $(OPTFLAGS)
CFLAGS=-g -Wall -Wextra -Isrc -Itests -Ibuild -Lbuild $(OPTFLAGS)
LIBS=-ldl $(OPTLIBS)
PREFIX?=/usr/local

#LIBPATH=-L./build/

SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

TEST_SRC=$(wildcard tests/*_tests.c)
#TESTS=$(patsubst %.c,%,$(TEST_SRC))

TARGET=build/liblcthw.a

MYLIBF = lcthw
ifeq ($(OS), Windows_NT)
	MYLIB = lcthwwin
	TESTS=$(patsubst %.c,%.exe,$(TEST_SRC))
else
	MYLIB = lcthw
	TESTS=$(patsubst %.c,%,$(TEST_SRC))
endif
MYLIBNAME = build/lib$(MYLIB:=.a)

SO_TARGET=$(patsubst %.a,%.so,$(MYLIBNAME))

# The trick here is to put the library AFTER the module you are compiling. The problem is a reference thing. The linker resolves references in order, so when the library is BEFORE the module being compiled, the linker gets confused and does not think that any of the functions in the library are needed. By putting the library AFTER the module, the references to the library in the module are resolved by the linker.

#The MYLIBNAME Build
all: $(MYLIBNAME) $(SO_TARGET) $(TESTS)

#dev: CFLAGS=-g Wall Isrc -Wall -Wextra $(OPTFLAGS)
dev: CFLAGS=-g -Wall -Wextra -Isrc -Itests -Ibuild -Lbuild $(OPTFLAGS)
dev: all

# need to compile our library source code into position-independent code (PIC)
$(MYLIBNAME): CFLAGS += -fPIC -Wl,--export-all-symbols
# build our static library:
$(MYLIBNAME): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

# build our shared library:
$(SO_TARGET): $(MYLIBNAME) $(OBJECTS)
	$(CC) $(OBJECTS) -shared -o $@

# my add: to solve linking error by wrong order; TODO: improve upon make rule!
$(TESTS): $(TEST_SRC) $(MYLIBNAME) Makefile
ifeq ($(OS), Windows_NT)
	$(CC) -o $@ $(patsubst %.exe,%.c,$@) $(CFLAGS) -Lbuild -l$(MYLIB)
else
	$(CC) -o $@ $(patsubst %,%.c,$@) $(CFLAGS) -Lbuild -l$(MYLIB)
endif
	#$(CC) -o $@ $(patsubst %,%.c,$@) $(CFLAGS)

build:
	@mkdir -p build
	@mkdir -p bin

# The Unit Tests
.Phony: tests
tests: CFLAGS += $(MYLIBNAME)
tests: $(TESTS)
	sh ./tests/runtests.sh

valgrind:
	VALGRIND="valgrind --log-file=/tmp/valgrind-%p.log" $(MAKE)

# The Cleaner
clean:
	rm -rf build $(OBJECTS) $(TESTS)
	rm -f tests/test.log
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`

# The Install
install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(MYLIBNAME) $(DESTDIR)/$(PREFIX)/lib/

# The Checker
BADFUNCS='[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)'
check:
	@echo Files with potentially dangerous functions.
	@egrep $(BADFUNCS) $(SOURCES) || true
