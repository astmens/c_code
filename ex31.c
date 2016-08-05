#include <unistd.h>

int main(int argc, char *argv[]) {
	int i = 0;
	
	while(i < 100) {
		usleep(3000);
	}
	
	return 0;
}

/*
gdb ./ex31
---
./ex31

$ ps ax | grep ex31
10026 s000  S+     0:00.11 ./ex31
10036 s001  R+     0:00.00 grep ex31

$ gdb ./ex31 10026

(gdb) bt
#0  0x00007ffff7ad5de0 in __nanosleep_nocancel ()
    at ../sysdeps/unix/syscall-template.S:81
#1  0x00007ffff7b07354 in usleep (useconds=<optimized out>)
    at ../sysdeps/unix/sysv/linux/usleep.c:32
#2  0x0000000000400554 in main (argc=1, argv=0x7fffffffde48) at ex31.c:7
(gdb) select-frame 2
(gdb) p i
$1 = 0


*/
