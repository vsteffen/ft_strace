#include "ft_strace.h"

bool		syscall64_generic_handler(union x86_64_regs *regs, const struct s_syscall_data *syscall_data, pid_t child, enum e_syscall_arch syscall_arch)
{
	static const size_t regs_offset [] = {
		offsetof(struct x86_64_user_regs_struct, rdi),
		offsetof(struct x86_64_user_regs_struct, rsi),
		offsetof(struct x86_64_user_regs_struct, rdx),
		offsetof(struct x86_64_user_regs_struct, r10),
		offsetof(struct x86_64_user_regs_struct, r8),
		offsetof(struct x86_64_user_regs_struct, r9)
	};

	size_t nb_char_print = 0;
	nb_char_print += dprintf(STDERR_FILENO, "%s(", syscall_data->name);

	for (uint8_t i = 0; syscall_data->args[i] != T_NONE && i < MAX_ARG; i++) {
		if (i > 0) nb_char_print += dprintf(STDERR_FILENO, ", ");
		nb_char_print += print_arg(*(size_t *)((void *)regs + regs_offset[i]), syscall_data->args[i], child, -1);
	}
	return print_ret_val(regs, syscall_data->args[6], child, nb_char_print, (struct s_syscall_state){SYSCALL_BEGIN, syscall_arch, false});
}

bool		syscall32_generic_handler(union x86_64_regs *regs, const struct s_syscall_data *syscall_data, pid_t child, enum e_syscall_arch syscall_arch)
{
	static const size_t regs_offset [] = {
		offsetof(struct i386_user_regs_struct, ebx),
		offsetof(struct i386_user_regs_struct, ecx),
		offsetof(struct i386_user_regs_struct, edx),
		offsetof(struct i386_user_regs_struct, esi),
		offsetof(struct i386_user_regs_struct, edi),
		offsetof(struct i386_user_regs_struct, ebp)
	};

	size_t nb_char_print = 0;
	nb_char_print += dprintf(STDERR_FILENO, "%s(", syscall_data->name);

	for (uint8_t i = 0; syscall_data->args[i] != T_NONE && i < MAX_ARG; i++) {
		if (i > 0) nb_char_print += dprintf(STDERR_FILENO, ", ");
		nb_char_print += print_arg((*(uint32_t *)((void *)regs + regs_offset[i])), syscall_data->args[i], child, -1);
	}
	return print_ret_val(regs, syscall_data->args[6], child, nb_char_print, (struct s_syscall_state){SYSCALL_BEGIN, syscall_arch, false});
}

bool		get_and_print_syscall_64(union x86_64_regs *regs, pid_t child) {
	static const struct s_syscall_data syscall64[] = {
	# include "syscall_tables/syscall64.h"
	};

	if (regs->x86_64_r.orig_rax > COUNT_OF(syscall64)) {
		printf("ft_strace: wrong syscall number (%llu)\n", regs->x86_64_r.orig_rax);
		exit(EXIT_FAILURE);
	}

	return syscall64[regs->x86_64_r.orig_rax].handler(regs, &syscall64[regs->x86_64_r.orig_rax], child, SYSCALL_64);
}

bool		get_and_print_syscall_32(union x86_64_regs *regs, pid_t child) {
	static const struct s_syscall_data syscall32[] = {
	# include "syscall_tables/syscall32.h"
	};

	if (regs->i386_r.orig_eax > COUNT_OF(syscall32)) {
		printf("ft_strace: wrong syscall number (%u)\n", regs->i386_r.orig_eax);
		exit(EXIT_FAILURE);
	}

	return syscall32[regs->i386_r.orig_eax].handler(regs, &syscall32[regs->i386_r.orig_eax], child, SYSCALL_32);
}
