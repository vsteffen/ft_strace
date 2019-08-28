#ifndef SYSCALL_ARG_H
# define SYSCALL_ARG_H

# define LINE_MIN_SIZE 40
# define PRINT_STR_MAX_SIZE 68
# define STR_UNESCAPE_MAX_SIZE 32


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
	PTR,
	STR,
	STRUCT,
	NONE
};

struct s_syscall32_data {
	const char *name;
	const enum e_type_syscall_arg args[7];
	size_t (* const handler)(struct i386_user_regs_struct *, const struct s_syscall32_data *, pid_t child);
};

struct s_syscall64_data {
	const char *name;
	const enum e_type_syscall_arg args[7];
	size_t (* const handler)(struct user_regs_struct *, const struct s_syscall64_data *, pid_t child);
};


#endif