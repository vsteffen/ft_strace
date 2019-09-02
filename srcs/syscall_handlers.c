#include "ft_strace.h"

bool		syscall_read_write_handler(union x86_64_regs *regs, const struct s_syscall_data *syscall_data, pid_t child, enum e_syscall_arch sys_arch, int *status)
{
	size_t buff_size;
	size_t nb_char_print = 0;
	bool is_exited = false;

	nb_char_print += fprintf(stderr, "%s(", syscall_data->name);

	if (sys_arch == SYSCALL_32) {
		nb_char_print += print_arg((uint32_t)regs->i386_r.ebx, syscall_data->args[0], child, 0);
		buff_size = regs->i386_r.edx;
	}
	else {
		nb_char_print += print_arg(regs->x86_64_r.rdi, syscall_data->args[0], child, 0);
		buff_size = regs->x86_64_r.rdx;
	}

	if (!handle_sig_and_wait_syscall(child, status)) is_exited = true;

	if (sys_arch == SYSCALL_32) {
		nb_char_print += fprintf(stderr, ", ");
		nb_char_print += print_arg((uint32_t)regs->i386_r.ecx, syscall_data->args[1], child, buff_size);
		nb_char_print += fprintf(stderr, ", ");
		nb_char_print += print_arg((uint32_t)regs->i386_r.edx, syscall_data->args[2], child, 0);
	}
	else {
		nb_char_print += fprintf(stderr, ", ");
		nb_char_print += print_arg(regs->x86_64_r.rsi, syscall_data->args[1], child, buff_size);
		nb_char_print += fprintf(stderr, ", ");
		nb_char_print += print_arg(regs->x86_64_r.rdx, syscall_data->args[2], child, 0);
	}

	get_registers_values(regs, child);
	if (sys_arch == SYSCALL_32)
		return print_ret_val((uint32_t)regs->i386_r.eax, syscall_data->args[6], child, status, nb_char_print, (struct s_syscall_state){SYSCALL_END, is_exited});
	else
		return print_ret_val(regs->x86_64_r.rax, syscall_data->args[6], child, status, nb_char_print, (struct s_syscall_state){SYSCALL_END, is_exited});
}
