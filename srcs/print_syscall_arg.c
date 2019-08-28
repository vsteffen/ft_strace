#include "ft_strace.h"

bool	str_too_long(char *str)
{
	uint8_t i = 0;
	while (str[i] && i < PRINT_STR_MAX_SIZE) i++;
	if (str[i])	return true;
	else		return false;
}

static size_t print_char(uint64_t reg_arg)			{ return fprintf(stderr, "%hhd", (char)reg_arg); }
static size_t print_short(uint64_t reg_arg)			{ return fprintf(stderr, "%hd", (short)reg_arg); }
static size_t print_int(uint64_t reg_arg)			{ return fprintf(stderr, "%d", (int)reg_arg); }
static size_t print_longint(uint64_t reg_arg)		{ return fprintf(stderr, "%ld", (long int)reg_arg); }
static size_t print_longlongint(uint64_t reg_arg)	{ return fprintf(stderr, "%lld", (long long int)reg_arg); }
static size_t print_intmax(uint64_t reg_arg)		{ return fprintf(stderr, "%jd", (intmax_t)reg_arg); }

static size_t print_uchar(uint64_t reg_arg)			{ return fprintf(stderr, "%hhu", (unsigned char)reg_arg); }
static size_t print_ushort(uint64_t reg_arg)		{ return fprintf(stderr, "%hu", (unsigned short)reg_arg); }
static size_t print_uint(uint64_t reg_arg)			{ return fprintf(stderr, "%u", (unsigned int)reg_arg); }
static size_t print_ulongint(uint64_t reg_arg)		{ return fprintf(stderr, "%lu", (unsigned long int)reg_arg); }
static size_t print_ulonglongint(uint64_t reg_arg)	{ return fprintf(stderr, "%llu", (unsigned long long int)reg_arg); }
static size_t print_uintmax(uint64_t reg_arg)		{ return fprintf(stderr, "%ju", (uintmax_t)reg_arg); }

static size_t print_size_t(uint64_t reg_arg)		{ return fprintf(stderr, "%zu", (uintmax_t)reg_arg); }

static size_t print_float(uint64_t reg_arg)			{ return fprintf(stderr, "%f", (float)reg_arg); }
static size_t print_double(uint64_t reg_arg)		{ return fprintf(stderr, "%f", (double)reg_arg); }
static size_t print_longdouble(uint64_t reg_arg)	{ return fprintf(stderr, "%Lf", (long double)reg_arg); }

static size_t print_ptr(uint64_t reg_arg)			{ return fprintf(stderr, "0x%p", (void *)reg_arg); }

static size_t print_str(uint64_t reg_arg)			{
	(void)reg_arg;
	return (0);
}

static size_t print_struct(uint64_t reg_arg)		{ return fprintf(stderr, "Struct 0x%p", (void *)reg_arg); }


size_t		print_arg(uint64_t reg, enum e_type_syscall_arg type)
{
	static size_t (* const print_fn[])(uint64_t) = {
	# include "print_function.h"
	};
	return (print_fn[type](reg));
}

void		syscall32_handler(struct i386_user_regs_struct *i386_r, const struct s_syscall_data *syscall_data)
{
	// static const uint16_t regs_offset [] = {
	// 	offsetof(struct user_regs_struct, rdi), 
	// 	offsetof(struct user_regs_struct, rsi), 
	// 	offsetof(struct user_regs_struct, rdx), 
	// 	offsetof(struct user_regs_struct, r10), 
	// 	offsetof(struct user_regs_struct, r8), 
	// 	offsetof(struct user_regs_struct, r9)
	// };
	static  size_t regs_offset [] = {
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
		if (i) nb_char_print += fprintf(stderr, ", ");
		nb_char_print += print_arg(*(uint64_t *)((void *)i386_r + regs_offset[i]), syscall_data->args[i]);
	}
	if (nb_char_print < LINE_MIN_SIZE)
		fprintf(stderr, "%*s", LINE_MIN_SIZE - (int)nb_char_print, "");
	fprintf(stderr, ") =\n");
}

void		get_and_print_syscall_64(struct user_regs_struct *x86_64_r) {
	(void)x86_64_r;
}

void		get_and_print_syscall_32(struct i386_user_regs_struct *i386_r) {
	static const struct s_syscall_data syscall32[] = {
	# include "syscall32.h"
	};

	if (i386_r->orig_eax > 4)
		return ;

	if (i386_r->orig_eax > COUNT_OF(syscall32)) {
		printf("ft_strace: wrong syscall number (%u)\n", i386_r->orig_eax);
		exit(EXIT_FAILURE);
	}

	syscall32[i386_r->orig_eax].handler(i386_r, &syscall32[i386_r->orig_eax]);
}

