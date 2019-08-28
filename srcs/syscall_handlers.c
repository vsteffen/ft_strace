#include "ft_strace.h"

size_t		syscall_read(union x86_64_regs *regs, const struct s_syscall_data *syscall_data, pid_t child, enum e_syscall_arch sys_arch, enum e_syscall_state sys_state)
{
	static size_t	size;
	static union x86_64_regs *regs_ugly; 

	regs_ugly = regs;
	if (sys_state == SYSCALL_BEGIN)
	{
		if (sys_arch == SYSCALL32)
			size = regs->i386.edx;
		else
			size = regs->x86_64.rdx;
		return (0);
	}
	size_t nb_char_print = 0;
	nb_char_print += fprintf(stderr, "%s(", syscall_data->x86_64.name);
	// fprintf(stderr, "\nSIZE IN HANDLER [%zu]\n", size);
	if (sys_arch == SYSCALL32)
		nb_char_print += print_arg(regs_ugly->i386.ecx, syscall_data->x86_64.args[1], child, size);
	else
		nb_char_print += print_arg(regs_ugly->x86_64.rsi, syscall_data->x86_64.args[1], child, size);
	SYSCALL32 ? fprintf(stderr, ") = %u\n", regs_ugly->i386.eax) : fprintf(stderr, ") = %llu\n", regs_ugly->x86_64.rax);
	return (nb_char_print);
}

size_t		syscall_read_handler32(struct i386_user_regs_struct *regs, const struct s_syscall32_data *syscall_data, pid_t child, enum e_syscall_arch sys_arch, enum e_syscall_state sys_state)
{
	return syscall_read((union x86_64_regs *)regs, (struct s_syscall_data *)syscall_data, child, sys_arch, sys_state);
}

size_t		syscall_read_handler64(struct user_regs_struct *regs, const struct s_syscall64_data *syscall_data, pid_t child, enum e_syscall_arch sys_arch, enum e_syscall_state sys_state)
{
	return syscall_read((union x86_64_regs *)regs, (struct s_syscall_data *)syscall_data, child, sys_arch, sys_state);
}

void		syscall_read_end_handler32(uintmax_t reg, const struct s_syscall32_data *syscall_data, size_t nb_char_print, pid_t child, enum e_syscall_arch sys_arch, enum e_syscall_state sys_state)
{
	syscall_read(NULL, (struct s_syscall_data *)syscall_data, child, sys_arch, sys_state);
}

void		syscall_read_end_handler64(uintmax_t reg, const struct s_syscall64_data *syscall_data, size_t nb_char_print, pid_t child, enum e_syscall_arch sys_arch, enum e_syscall_state sys_state)
{
	syscall_read(NULL, (struct s_syscall_data *)syscall_data, child, sys_arch, sys_state);
}