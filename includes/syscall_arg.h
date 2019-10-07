#ifndef SYSCALL_ARG_H
# define SYSCALL_ARG_H

# define LINE_MIN_SIZE 40
# define PRINT_STR_MAX_SIZE 68
# define BUFF_UNESCAPE_MAX_SIZE 32
# define STR_UNESCAPE_MAX_SIZE 4096
# define MAX_ARG 6

enum e_syscall_arch {
	SYSCALL_64,
	SYSCALL_32
};

enum e_syscall_time_status {
	SYSCALL_BEGIN,
	SYSCALL_END
};

struct s_syscall_state {
	enum e_syscall_time_status time_status;
	enum e_syscall_arch arch;
	bool is_exited;
};

enum e_type_syscall_arg {
	T_CHAR,
	T_SHORT,
	T_INT,
	T_LINT,
	T_LLINT,
	T_UCHAR,
	T_USHORT,
	T_UINT,
	T_ULINT,
	T_ULLINT,
	T_FLOAT,
	T_DOUBLE,
	T_LDOUBLE,
	T_ADDR,
	T_HEX,
	T_BUFF,
	T_STR,
	T_UNKNOWN,

	T_CADDR_T,
	T_SIGHANDLER_T,
	T_E_PTRACE_REQUEST,

	T_NONE
};


struct s_syscall_data {
	const char *name;
	const enum e_type_syscall_arg args[7];
	bool (* const handler)(union x86_64_regs *, const struct s_syscall_data *, pid_t, enum e_syscall_arch, int *);
};


#endif