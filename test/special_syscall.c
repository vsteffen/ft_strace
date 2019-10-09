#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>


int main(int argc, char *argv[])
{
	#ifndef __LP64__
		syscall(17); // unimplemented
		syscall(222); // unused
		syscall(18); // oldstat
		syscall(28); // oldfstat
		syscall(54); // ioctl
		syscall(55); // fcntl
		syscall(221); // fcntl64
		syscall(59); // oldolduname
		syscall(109); // olduname
		syscall(120); // clone
		syscall(142); // _newselect
		syscall(163); // mremap
		// syscall(173); // rt_sigreturn
		syscall(174); // rt_sigaction
		syscall(176); // rt_sigpending
		syscall(177); // rt_sigtimedwait
		syscall(184); // capget
		syscall(185); // capset
		syscall(191); // ugetrlimit173
		syscall(250); // fadvise
		syscall(262); // timer_getoverrun
		syscall(263); // timer_delete
		syscall(272); // fadvise64_64
		syscall(288); // keyctl
		syscall(308); // pselect6
		syscall(327); // signalfd4
		syscall(328); // eventfd2
		syscall(343); // clock_adjtime
		syscall(386); // rseq
	#else // 32 bits
		syscall(66); // mremap
		syscall(72); // fcntl
		syscall(221); // fadvise64
		syscall(214); // epoll_ctl_old
		syscall(215); // epoll_wait_old
	#endif
}