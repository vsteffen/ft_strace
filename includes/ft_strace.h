#ifndef FT_STRACE_H
# define FT_STRACE_H

# define _GNU_SOURCE

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

# define __unused __attribute__((unused))
# define COUNT_OF(ptr) (sizeof(ptr) / sizeof((ptr)[0]))


# define SI_CODE_UNKNWON_TO_STR "UNKNWON"

struct s_si_code_regular {
	const int	si_code;
	const char	*to_str;
};

struct s_si_code {
	const int	si_signo;
	const int	si_code;
	const char	*to_str;
};

enum e_si_life {
  SI_DEAD,
  SI_ALIVE
};

struct x86_64_user_regs_struct
{
  __extension__ unsigned long long int r15;
  __extension__ unsigned long long int r14;
  __extension__ unsigned long long int r13;
  __extension__ unsigned long long int r12;
  __extension__ unsigned long long int rbp;
  __extension__ unsigned long long int rbx;
  __extension__ unsigned long long int r11;
  __extension__ unsigned long long int r10;
  __extension__ unsigned long long int r9;
  __extension__ unsigned long long int r8;
  __extension__ unsigned long long int rax;
  __extension__ unsigned long long int rcx;
  __extension__ unsigned long long int rdx;
  __extension__ unsigned long long int rsi;
  __extension__ unsigned long long int rdi;
  __extension__ unsigned long long int orig_rax;
  __extension__ unsigned long long int rip;
  __extension__ unsigned long long int cs;
  __extension__ unsigned long long int eflags;
  __extension__ unsigned long long int rsp;
  __extension__ unsigned long long int ss;
  __extension__ unsigned long long int fs_base;
  __extension__ unsigned long long int gs_base;
  __extension__ unsigned long long int ds;
  __extension__ unsigned long long int es;
  __extension__ unsigned long long int fs;
  __extension__ unsigned long long int gs;
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

union x86_64_regs {
	struct x86_64_user_regs_struct	x86_64_r;
	struct i386_user_regs_struct 	i386_r;
};

# include "syscall_arg.h"


char			*get_bin_path(char *prog_name);

bool			handle_sig_and_wait_syscall(pid_t child, enum e_si_life si_life);
void			get_registers_values(union x86_64_regs *regs, int child);

bool			get_and_print_syscall_64(union x86_64_regs *x86_64_r, pid_t child);
bool			get_and_print_syscall_32(union x86_64_regs *i386_r, pid_t child);

size_t			print_arg(size_t reg, enum e_type_syscall_arg type, pid_t child, size_t size);
bool			print_ret_val(union x86_64_regs *regs, enum e_type_syscall_arg type, pid_t child, size_t nb_char_print, struct s_syscall_state state);

bool			syscall64_generic_handler(union x86_64_regs *regs, const struct s_syscall_data *syscall_data, pid_t child, enum e_syscall_arch syscall_arch);
bool			syscall32_generic_handler(union x86_64_regs *regs, const struct s_syscall_data *syscall_data, pid_t child, enum e_syscall_arch syscall_arch);

bool			syscall_read_write_handler(union x86_64_regs *regs, const struct s_syscall_data *syscall_data, pid_t child, enum e_syscall_arch sys_arch);

#endif
