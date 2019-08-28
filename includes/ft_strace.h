#ifndef FT_STRACE_H
# define FT_STRACE_H

# define _XOPEN_SOURCE
# define _XOPEN_SOURCE_EXTENDED

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <ctype.h>
# include <stddef.h>
# include <string.h>
# include <sys/ptrace.h>
# include <sys/user.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>

# include <signal.h>

# include <elf.h>
# include <sys/uio.h>

# include <stdbool.h>
# include <errno.h>


# define COUNT_OF(ptr) (sizeof(ptr) / sizeof((ptr)[0]))


struct s_si_code_regular {
	const int	si_code;
	const char	*to_str;
};

struct s_si_code {
	const int	si_signo;
	const int	si_code;
	const char	*to_str;
};

struct i386_user_regs_struct {
	uint32_t ebx;
	uint32_t ecx;
	uint32_t edx;
	uint32_t esi;
	uint32_t edi;
	uint32_t ebp;
	uint32_t eax;
	uint32_t xds;
	uint32_t xes;
	uint32_t xfs;
	uint32_t xgs;
	uint32_t orig_eax;
	uint32_t eip;
	uint32_t xcs;
	uint32_t eflags;
	uint32_t esp;
	uint32_t xss;
};

enum e_arch_type {
	X86_64,
	I386
};

union x86_64_regs {
	struct user_regs_struct			x86_64;
	struct i386_user_regs_struct 	i386;
};

# include "syscall_arg.h"


char			*get_bin_path(char *prog_name);

size_t			get_and_print_syscall_64(struct user_regs_struct *x86_64_r, pid_t child);
size_t			get_and_print_syscall_32(struct i386_user_regs_struct *i386_r, pid_t child);


#endif
