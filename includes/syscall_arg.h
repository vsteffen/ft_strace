#ifndef SYSCALL_ARG_H
# define SYSCALL_ARG_H

# define LINE_MIN_SIZE 40
# define PRINT_STR_MAX_SIZE 68
# define STR_UNESCAPE_MAX_SIZE 32
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
	bool is_exited;
};

enum e_type_syscall_arg {
	CHAR,
	SHORT,
	INT,
	LINT,
	LLINT,
	INTMAX,
	UCHAR,
	USHORT,
	UINT,
	ULINT,
	ULLINT,
	UINTMAX,
	SIZE_T,
	FLOAT,
	DOUBLE,
	LDOUBLE,
	ADDR,
	BUFF,
	STR,
	STRUCT,
	NONE
};


struct s_syscall_data {
	const char *name;
	const enum e_type_syscall_arg args[7];
	bool (* const handler)(union x86_64_regs *, const struct s_syscall_data *, pid_t, enum e_syscall_arch, int *);
};


#endif