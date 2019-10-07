#include "ft_strace.h"

# define CEIL_MULTIPLE(val, mul) ((val / mul + 1) * mul)


size_t		print_escape_string(const uint8_t *str, const size_t size, const size_t max_print_size) {
	int8_t	*escape_str;
	size_t	i = 0;
	char	buff[4];
	const uint8_t *ptr = str;

	escape_str = malloc(max_print_size * 4 + 1);
	if (!escape_str) {
		printf("ft_strace: malloc: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	size_t max_size = (size < max_print_size ? size : max_print_size);
	while ((size_t)(str - ptr) < max_size) {
		if (*str == '\f') {
			memcpy(escape_str + i, "\\f", 3);
			i += 2;
		}
		else if (*str == '\n') {
			memcpy(escape_str + i, "\\n", 3);
			i += 2;
		}
		else if (*str == '\r') {
			memcpy(escape_str + i, "\\r", 3);
			i += 2;
		}
		else if (*str == '\t') {
			memcpy(escape_str + i, "\\t", 3);
			i += 2;
		}
		else if (*str == '\v') {
			memcpy(escape_str + i, "\\v", 3);
			i += 2;
		}
		else if (isprint(*str))
			escape_str[i++] = *str;
		else {
			sprintf(buff, "%hho", *str);
			escape_str[i++] = '\\';
			memcpy(escape_str + i, buff, strlen(buff));
			i += strlen(buff);
		}
		str++;
	}
	escape_str[i] = 0;

	size_t	ret_print;
	if (size >= max_print_size)
		ret_print = dprintf(STDERR_FILENO, "\"%s\"...", escape_str);
	else
		ret_print = dprintf(STDERR_FILENO, "\"%s\"", escape_str);
	free(escape_str);
	return (ret_print);
}

static size_t print_char(uintmax_t reg, __unused pid_t child, __unused size_t size)			{ return dprintf(STDERR_FILENO, "%hhd", (char)reg); }
static size_t print_short(uintmax_t reg, __unused pid_t child, __unused size_t size)		{ return dprintf(STDERR_FILENO, "%hd", (short)reg); }
static size_t print_int(uintmax_t reg, __unused pid_t child, __unused size_t size)			{ return dprintf(STDERR_FILENO, "%d", (int)reg); }
static size_t print_longint(uintmax_t reg, __unused pid_t child, __unused size_t size)		{ return dprintf(STDERR_FILENO, "%ld", (long int)reg); }
static size_t print_longlongint(uintmax_t reg, __unused pid_t child, __unused size_t size)	{ return dprintf(STDERR_FILENO, "%lld", (long long int)reg); }

static size_t print_uchar(uintmax_t reg, __unused pid_t child, __unused size_t size)		{ return dprintf(STDERR_FILENO, "%hhu", (unsigned char)reg); }
static size_t print_ushort(uintmax_t reg, __unused pid_t child, __unused size_t size)		{ return dprintf(STDERR_FILENO, "%hu", (unsigned short)reg); }
static size_t print_uint(uintmax_t reg, __unused pid_t child, __unused size_t size)			{ return dprintf(STDERR_FILENO, "%u", (unsigned int)reg); }
static size_t print_ulongint(uintmax_t reg, __unused pid_t child, __unused size_t size)		{ return dprintf(STDERR_FILENO, "%lu", (unsigned long int)reg); }
static size_t print_ulonglongint(uintmax_t reg, __unused pid_t child, __unused size_t size)	{ return dprintf(STDERR_FILENO, "%llu", (unsigned long long int)reg); }

static size_t print_float(uintmax_t reg, __unused pid_t child, __unused size_t size)		{ return dprintf(STDERR_FILENO, "%f", (float)reg); }
static size_t print_double(uintmax_t reg, __unused pid_t child, __unused size_t size)		{ return dprintf(STDERR_FILENO, "%f", (double)reg); }
static size_t print_longdouble(uintmax_t reg, __unused pid_t child, __unused size_t size)	{ return dprintf(STDERR_FILENO, "%Lf", (long double)reg); }

static size_t print_addr(uintmax_t reg, __unused pid_t child, __unused size_t size)			{ return (reg ? dprintf(STDERR_FILENO, "%p", (void *)reg) : dprintf(STDERR_FILENO, "NULL")); }
static size_t print_hex(uintmax_t reg, __unused pid_t child, __unused size_t size)			{ return dprintf(STDERR_FILENO, "0x%zx", reg); }

static size_t print_buff(uintmax_t reg, __unused pid_t child, size_t size)					{
	uint8_t		str[CEIL_MULTIPLE(BUFF_UNESCAPE_MAX_SIZE + 1, sizeof(uintmax_t))];
	size_t		total_read = 0;
	uintmax_t	tmp;

	while (total_read < size && total_read < BUFF_UNESCAPE_MAX_SIZE) {
		tmp = ptrace(PTRACE_PEEKDATA, child, reg + total_read, NULL);
		if (tmp == (uintmax_t)-1) break;
		memcpy(str + total_read, &tmp, sizeof(tmp));
		total_read += sizeof(tmp);
	}
	str[total_read] = 0;
	return (print_escape_string(str, (tmp == (uintmax_t)-1 ? total_read : size), BUFF_UNESCAPE_MAX_SIZE));
}

static size_t print_str(uintmax_t reg, pid_t child, __unused size_t size)					{
	uint8_t		str[CEIL_MULTIPLE(STR_UNESCAPE_MAX_SIZE + 1, sizeof(uintmax_t))];
	size_t		total_read = 0;
	uintmax_t	tmp;
	void		*ptr;

	while (total_read < STR_UNESCAPE_MAX_SIZE) {
		tmp = ptrace(PTRACE_PEEKDATA, child, reg + total_read, NULL);
		if (tmp == (uintmax_t)-1) break;
		memcpy(str + total_read, &tmp, sizeof(tmp));
		ptr = memchr(&tmp, 0, sizeof(tmp));
		if (ptr) {
			total_read += ptr - (void *)&tmp;
			break;
		}
		total_read += sizeof(tmp);
	}
	str[total_read] = 0;
	return (print_escape_string(str, total_read, STR_UNESCAPE_MAX_SIZE));
}

size_t		print_arg(uintmax_t reg, enum e_type_syscall_arg type, pid_t child, size_t size)
{
	static size_t (* const print_fn[])(uintmax_t, pid_t, size_t) = {
	# include "print_function.h"
	};

	return (print_fn[type](reg, child, size));
}

bool		print_ret_val(union x86_64_regs *regs, enum e_type_syscall_arg type, pid_t child, int *status, size_t nb_char_print, struct s_syscall_state state) {
	const char *const errnoent[] = {
		#include "errnoent.h"
	};
	nb_char_print += dprintf(STDERR_FILENO, ") ");
	if (nb_char_print < LINE_MIN_SIZE)
		dprintf(STDERR_FILENO, "%*s", LINE_MIN_SIZE - (int)nb_char_print, "");
	if ((state.time_status == SYSCALL_BEGIN && !handle_sig_and_wait_syscall(child, status)) || state.is_exited == true) {
		dprintf(STDERR_FILENO, "= ?\n");
		return (false);
	}
	get_registers_values(regs, child);
	dprintf(STDERR_FILENO, "= ");
	if (state.arch == SYSCALL_32) {
		uint32_t tmp;
		#ifdef __x86_64__
			tmp = (uint32_t)regs->x86_64_r.rax;
		#else
			tmp = regs->i386_r.eax;
		#endif
		if (tmp <= -1U && tmp >= -4096U)
			dprintf(STDERR_FILENO, "-1 %s (%s)", errnoent[-tmp], strerror(-tmp));
		else
			print_arg(tmp, type, child, 0);
	}
	else {
		if (regs->x86_64_r.rax <= -1UL && regs->x86_64_r.rax >= -4096UL)
			dprintf(STDERR_FILENO, "-1 %s (%s)", errnoent[-regs->x86_64_r.rax], strerror(-regs->x86_64_r.rax));
		else
			print_arg(regs->x86_64_r.rax, type, child, 0);

	}
	dprintf(STDERR_FILENO, "\n");
	return (true);
}

bool		syscall64_generic_handler(union x86_64_regs *regs, const struct s_syscall_data *syscall_data, pid_t child, enum e_syscall_arch syscall_arch, int *status)
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
		nb_char_print += print_arg(*(uintmax_t *)((void *)regs + regs_offset[i]), syscall_data->args[i], child, 0);
	}
	return print_ret_val(regs, syscall_data->args[6], child, status, nb_char_print, (struct s_syscall_state){SYSCALL_BEGIN, syscall_arch, false});
}

bool		syscall32_generic_handler(union x86_64_regs *regs, const struct s_syscall_data *syscall_data, pid_t child, enum e_syscall_arch syscall_arch, int *status)
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
		nb_char_print += print_arg((*(uint32_t *)((void *)regs + regs_offset[i])), syscall_data->args[i], child, 0);
	}
	return print_ret_val(regs, syscall_data->args[6], child, status, nb_char_print, (struct s_syscall_state){SYSCALL_BEGIN, syscall_arch, false});
}

bool		get_and_print_syscall_64(union x86_64_regs *regs, pid_t child, int *status) {
	static const struct s_syscall_data syscall64[] = {
	# include "syscall64.h"
	};

	if (regs->x86_64_r.orig_rax > COUNT_OF(syscall64)) {
		printf("ft_strace: wrong syscall number (%llu)\n", regs->x86_64_r.orig_rax);
		exit(EXIT_FAILURE);
	}

	return syscall64[regs->x86_64_r.orig_rax].handler(regs, &syscall64[regs->x86_64_r.orig_rax], child, SYSCALL_64, status);
}

bool		get_and_print_syscall_32(union x86_64_regs *regs, pid_t child, int *status) {
	static const struct s_syscall_data syscall32[] = {
	# include "syscall32.h"
	};

	if (regs->i386_r.orig_eax > COUNT_OF(syscall32)) {
		printf("ft_strace: wrong syscall number (%u)\n", regs->i386_r.orig_eax);
		exit(EXIT_FAILURE);
	}

	return syscall32[regs->i386_r.orig_eax].handler(regs, &syscall32[regs->i386_r.orig_eax], child, SYSCALL_32, status);
}

