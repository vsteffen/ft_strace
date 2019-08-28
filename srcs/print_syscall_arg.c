#include "ft_strace.h"

# define __unused __attribute__((unused))
# define CEIL_MULTIPLE(val, mul) ((val / mul + 1) * mul)


size_t		print_escape_string(const uint8_t *str, const size_t size) {
	int8_t	escape_str[STR_UNESCAPE_MAX_SIZE * 4 + 1];
	size_t	i = 0;
	char	buff[4];
	const uint8_t *ptr = str;

	while ((size_t)(str - ptr) < size) {
		if (*str == '\f') {
			memcpy(escape_str + i, "\\f", 3);
			i += 3;
		}
		else if (*str == '\n') {
			memcpy(escape_str + i, "\\n", 3);
			i += 3;
		}
		else if (*str == '\r') {
			memcpy(escape_str + i, "\\r", 3);
			i += 3;
		}
		else if (*str == '\t') {
			memcpy(escape_str + i, "\\t", 3);
			i += 3;
		}
		else if (*str == '\v') {
			memcpy(escape_str + i, "\\v", 3);
			i += 3;
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
	if (size > STR_UNESCAPE_MAX_SIZE)
		return (fprintf(stderr, "\"%s\"...", escape_str));
	return (fprintf(stderr, "\"%s\"", escape_str));
}

static size_t print_char(uintmax_t *reg, __unused pid_t child)			{ return fprintf(stderr, "%hhd", (char)*reg); }
static size_t print_short(uintmax_t *reg, __unused pid_t child)			{ return fprintf(stderr, "%hd", (short)*reg); }
static size_t print_int(uintmax_t *reg, __unused pid_t child)			{ return fprintf(stderr, "%d", (int)*reg); }
static size_t print_longint(uintmax_t *reg, __unused pid_t child)		{ return fprintf(stderr, "%ld", (long int)*reg); }
static size_t print_longlongint(uintmax_t *reg, __unused pid_t child)	{ return fprintf(stderr, "%lld", (long long int)*reg); }
static size_t print_intmax(uintmax_t *reg, __unused pid_t child)		{ return fprintf(stderr, "%jd", (intmax_t)*reg); }

static size_t print_uchar(uintmax_t *reg, __unused pid_t child)			{ return fprintf(stderr, "%hhu", (unsigned char)*reg); }
static size_t print_ushort(uintmax_t *reg, __unused pid_t child)		{ return fprintf(stderr, "%hu", (unsigned short)*reg); }
static size_t print_uint(uintmax_t *reg, __unused pid_t child)			{ return fprintf(stderr, "%u", (unsigned int)*reg); }
static size_t print_ulongint(uintmax_t *reg, __unused pid_t child)		{ return fprintf(stderr, "%lu", (unsigned long int)*reg); }
static size_t print_ulonglongint(uintmax_t *reg, __unused pid_t child)	{ return fprintf(stderr, "%llu", (unsigned long long int)*reg); }
static size_t print_uintmax(uintmax_t *reg, __unused pid_t child)		{ return fprintf(stderr, "%ju", (uintmax_t)*reg); }

static size_t print_size_t(uintmax_t *reg, __unused pid_t child)		{ return fprintf(stderr, "%zu", (size_t)*reg); }

static size_t print_float(uintmax_t *reg, __unused pid_t child)			{ return fprintf(stderr, "%f", (float)*reg); }
static size_t print_double(uintmax_t *reg, __unused pid_t child)		{ return fprintf(stderr, "%f", (double)*reg); }
static size_t print_longdouble(uintmax_t *reg, __unused pid_t child)	{ return fprintf(stderr, "%Lf", (long double)*reg); }

static size_t print_ptr(uintmax_t *reg, __unused pid_t child)			{
	uint8_t		str[CEIL_MULTIPLE(STR_UNESCAPE_MAX_SIZE + 1, sizeof(uintmax_t))];
	size_t		total_read = 0;
	uintmax_t	tmp;

	while (total_read < STR_UNESCAPE_MAX_SIZE) {
		tmp = ptrace(PTRACE_PEEKDATA, child, *reg + total_read, NULL);
		if (tmp == (uintmax_t)-1) break;
		memcpy(str + total_read, &tmp, sizeof(tmp));
		total_read += sizeof(tmp);
	}
	str[total_read] = 0;
	return (print_escape_string(str, total_read));
}

static size_t print_str(uintmax_t *reg, pid_t child)					{
	uint8_t		str[CEIL_MULTIPLE(STR_UNESCAPE_MAX_SIZE + 1, sizeof(uintmax_t))];
	size_t		total_read = 0;
	uintmax_t	tmp;
	void		*ptr;

	while (total_read < STR_UNESCAPE_MAX_SIZE) {
		tmp = ptrace(PTRACE_PEEKDATA, child, *reg + total_read, NULL);
		if (tmp == (uintmax_t)-1) break;
		memcpy(str + total_read, &tmp, sizeof(tmp));
		total_read += sizeof(tmp);
		ptr = memchr(&tmp, 0, sizeof(tmp));
		total_read += ptr - (void *)&tmp;
		if (ptr) break;
	}
	str[total_read] = 0;
	return (print_escape_string(str, total_read));
}

static size_t print_struct(uintmax_t *reg, __unused pid_t child)			{ return fprintf(stderr, "Struct 0x%p", (void *)reg); }


size_t		print_arg(uintmax_t *reg, enum e_type_syscall_arg type, pid_t child)
{
	static size_t (* const print_fn[])(uintmax_t*, pid_t) = {
	# include "print_function.h"
	};
	return (print_fn[type](reg, child));
}

size_t		syscall64_generic_handler(struct user_regs_struct *x86_64_r, const struct s_syscall64_data *syscall_data, pid_t child)
{
	static const size_t regs_offset [] = {
		offsetof(struct user_regs_struct, rdi), 
		offsetof(struct user_regs_struct, rsi), 
		offsetof(struct user_regs_struct, rdx), 
		offsetof(struct user_regs_struct, r10), 
		offsetof(struct user_regs_struct, r8), 
		offsetof(struct user_regs_struct, r9)
	};

	fprintf(stderr, "ft_strace: in syscall_handler (%llu -> \"%s\")\n", x86_64_r->orig_rax, syscall_data->name);
	fprintf(stderr, "%s(", syscall_data->name);

	size_t nb_char_print = 0;
	for (uint8_t i = 0; syscall_data->args[i] != NONE; i++) {
		if (i && syscall_data->args[i + 1]) nb_char_print += fprintf(stderr, ", ");
		nb_char_print += print_arg((uintmax_t *)((void *)x86_64_r + regs_offset[i]), syscall_data->args[i], child);
	}
	return (nb_char_print);

	// if (nb_char_print < LINE_MIN_SIZE)
	// 	fprintf(stderr, "%*s", LINE_MIN_SIZE - (int)nb_char_print, "");
	// fprintf(stderr, ") =\n");
}

size_t		syscall32_generic_handler(struct i386_user_regs_struct *i386_r, const struct s_syscall32_data *syscall_data, pid_t child)
{
	static const size_t regs_offset [] = {
		offsetof(struct i386_user_regs_struct, ebx),
		offsetof(struct i386_user_regs_struct, ecx),
		offsetof(struct i386_user_regs_struct, edx),
		offsetof(struct i386_user_regs_struct, esi),
		offsetof(struct i386_user_regs_struct, edi),
		offsetof(struct i386_user_regs_struct, ebp)
	};

	fprintf(stderr, "ft_strace: in syscall_handler (%u -> \"%s\")\n", i386_r->orig_eax, syscall_data->name);
	fprintf(stderr, "%s(", syscall_data->name);

	size_t nb_char_print = 0;
	for (uint8_t i = 0; syscall_data->args[i] != NONE; i++) {
		if (i && syscall_data->args[i + 1]) nb_char_print += fprintf(stderr, ", ");
		nb_char_print += print_arg((uintmax_t *)((void *)i386_r + regs_offset[i]), syscall_data->args[i], child);
	}
	return (nb_char_print);

	// if (nb_char_print < LINE_MIN_SIZE)
	// 	fprintf(stderr, "%*s", LINE_MIN_SIZE - (int)nb_char_print, "");
	// fprintf(stderr, ") =\n");
}

size_t		get_and_print_syscall_64(struct user_regs_struct *x86_64_r, pid_t child) {
	static const struct s_syscall64_data syscall64[] = {
	# include "syscall64.h"
	};

	if (x86_64_r->orig_rax > 1)
		return (0);

	if (x86_64_r->orig_rax > COUNT_OF(syscall64)) {
		printf("ft_strace: wrong syscall number (%llu)\n", x86_64_r->orig_rax);
		exit(EXIT_FAILURE);
	}

	return syscall64[x86_64_r->orig_rax].handler(x86_64_r, &syscall64[x86_64_r->orig_rax], child);
}

size_t		get_and_print_syscall_32(struct i386_user_regs_struct *i386_r, pid_t child) {
	static const struct s_syscall32_data syscall32[] = {
	# include "syscall32.h"
	};

	if (i386_r->orig_eax > 4)
		return (0);

	if (i386_r->orig_eax > COUNT_OF(syscall32)) {
		printf("ft_strace: wrong syscall number (%u)\n", i386_r->orig_eax);
		exit(EXIT_FAILURE);
	}

	return syscall32[i386_r->orig_eax].handler(i386_r, &syscall32[i386_r->orig_eax], child);
}

