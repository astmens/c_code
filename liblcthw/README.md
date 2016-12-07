http://www.gnu.org/software/gsl/manual/html_node/Shared-Libraries.html

To run a program linked with the shared version of the library the operating system must be able to locate the corresponding .so file at runtime. If the library cannot be found, the following error will occur:

$ ./a.out
./a.out: error while loading shared libraries:
libgsl.so.0: cannot open shared object file: No such
file or directory
To avoid this error, either modify the system dynamic linker configuration5 or define the shell variable LD_LIBRARY_PATH to include the directory where the library is installed.

For example, in the Bourne shell (/bin/sh or /bin/bash), the library search path can be set with the following commands:

$ LD_LIBRARY_PATH=/usr/local/lib
$ LD_LIBRARY_PATH=/media/C/Users/Atom/Documents/c_code/liblcthw/build/

$ export LD_LIBRARY_PATH
$ ./example


(5)
/etc/ld.so.conf on GNU/Linux systems.

sudo nano /etc/ld.so.conf.d/libc.conf

Add:
/media/C/Users/Atom/Documents/c_code/liblcthw/build/
Run:
sudo ldconfig
