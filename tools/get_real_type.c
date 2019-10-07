#define _POSIX_C_SOURCE
#define _GNU_SOURCE

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <signal.h>
#include <stdlib.h>
#include <linux/capability.h>
#include <time.h>
#include <sys/stat.h>
#include <linux/module.h>
#include <unistd.h>
#include <poll.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <sched.h>
#include <linux/aio_abi.h>
#include <mqueue.h>
#include <keyutils.h>

#define GET_ARG_TYPE(expr) \
	(_Generic((expr), \
		char: "T_CHAR", unsigned char: "T_UCHAR", \
		short: "T_SHORT", unsigned short: "T_USHORT", \
		int: "T_INT", unsigned int: "T_UINT", \
		long: "T_LINT", unsigned long: "T_ULINT", \
		long long: "T_LLINT", unsigned long long: "T_ULLINT", \
		float: "T_FLOAT", \
		double: "T_DOUBLE", \
		long double: "T_LDOUBLE", \
		default: "T_UNKNOWN"))


int		main(int ac, char **av) {
	if (ac < 2) {
		printf("UNKNOWN");
	}
	else if (strcmp(av[1], "pid_t") == 0)
		printf("%s", GET_ARG_TYPE((pid_t)42));
	else if (strcmp(av[1], "mode_t") == 0)
		printf("%s", GET_ARG_TYPE((mode_t)42));
	else if (strcmp(av[1], "time_t") == 0)
		printf("%s", GET_ARG_TYPE((time_t)42));
	else if (strcmp(av[1], "timer_t") == 0)
		printf("%s", GET_ARG_TYPE((timer_t)42));
	else if (strcmp(av[1], "ssize_t") == 0)
		printf("%s", GET_ARG_TYPE((ssize_t)42));
	else if (strcmp(av[1], "uid_t") == 0)
		printf("%s", GET_ARG_TYPE((uid_t)42));
	else if (strcmp(av[1], "off_t") == 0)
		printf("%s", GET_ARG_TYPE((off_t)42));
	else if (strcmp(av[1], "clock_t") == 0)
		printf("%s", GET_ARG_TYPE((clock_t)42));
	else if (strcmp(av[1], "gid_t") == 0)
		printf("%s", GET_ARG_TYPE((gid_t)42));
	else if (strcmp(av[1], "dev_t") == 0)
		printf("%s", GET_ARG_TYPE((dev_t)42));
	else if (strcmp(av[1], "size_t") == 0)
		printf("%s", GET_ARG_TYPE((size_t)42));
	else if (strcmp(av[1], "id_t") == 0)
		printf("%s", GET_ARG_TYPE((id_t)42));
	else if (strcmp(av[1], "loff_t") == 0)
		printf("%s", GET_ARG_TYPE((loff_t)42));
	else if (strcmp(av[1], "nfds_t") == 0)
		printf("%s", GET_ARG_TYPE((nfds_t)42));
	else if (strcmp(av[1], "cap_user_header_t") == 0)
		printf("%s", GET_ARG_TYPE((cap_user_header_t)42));
	else if (strcmp(av[1], "cap_user_data_t") == 0)
		printf("%s", GET_ARG_TYPE((cap_user_data_t)42));
	else if (strcmp(av[1], "off64_t") == 0)
		printf("%s", GET_ARG_TYPE((off64_t)42));
	else if (strcmp(av[1], "aio_context_t") == 0)
		printf("%s", GET_ARG_TYPE((aio_context_t)42));
	else if (strcmp(av[1], "u64") == 0)
		printf("%s", GET_ARG_TYPE((__u64)42));
	else if (strcmp(av[1], "clockid_t") == 0)
		printf("%s", GET_ARG_TYPE((clockid_t)42));
	else if (strcmp(av[1], "mqd_t") == 0)
		printf("%s", GET_ARG_TYPE((mqd_t)42));
	else if (strcmp(av[1], "idtype_t") == 0)
		printf("%s", GET_ARG_TYPE((idtype_t)42));
	else if (strcmp(av[1], "key_serial_t") == 0)
		printf("%s", GET_ARG_TYPE((key_serial_t)42));
	else if (strcmp(av[1], "uint32_t") == 0)
		printf("%s", GET_ARG_TYPE((uint32_t)42));
	else if (strcmp(av[1], "uint64_t") == 0)
		printf("%s", GET_ARG_TYPE((uint64_t)42));
	else if (strcmp(av[1], "socklen_t") == 0)
		printf("%s", GET_ARG_TYPE((socklen_t)42));

	// Unknown type
	else if (strcmp(av[1], "stack_t") == 0)
		printf("%s", "T_STACK_T");
	else if (strcmp(av[1], "old_kernel_sigset_t") == 0)
		printf("%s", "T_OLD_KERNEL_SIGSET_T");
	else if (strcmp(av[1], "kernel_sigset_t") == 0)
		printf("%s", "T_KERNEL_SIGSET_T");
	else if (strcmp(av[1], "sigset_t") == 0)
		printf("%s", "T_SIGSET_T");
	else if (strcmp(av[1], "siginfo_t") == 0)
		printf("%s", "T_SIGINFO_T");
	else if (strcmp(av[1], "sighandler_t") == 0)
		printf("%s", "T_SIGHANDLER_T");
	else if (strcmp(av[1], "caddr_t") == 0)
		printf("%s", "T_CADDR_T");
	else if (strcmp(av[1], "cpu_set_t") == 0)
		printf("%s", "T_CPU_SET_T");
	else
		printf("UNKNOWN");
	return (0);
}
