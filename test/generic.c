#include <stdio.h>
#include <time.h>
#include <sys/uio.h>

# define COUNT_OF(ptr) (sizeof(ptr) / sizeof((ptr)[0]))



enum e_type_syscall_arg {
	DEFAULT,
	CHAR,
	SHORT,
	INT,
	LINT,
	LLINT,
	UCHAR,
	USHORT,
	UINT,
	ULINT,
	ULLINT,
	FLOAT,
	DOUBLE,
	LDOUBLE,
	PTR,
	PTRCHAR,
	PTRINT
};

# include <stdint.h>

static void print_char(uintmax_t reg_arg)			{ printf("%hhd", (char)reg_arg); }
static void print_short(uintmax_t reg_arg)			{ printf("%hd", (short)reg_arg); }
static void print_int(uintmax_t reg_arg)			{ printf("%d", (int)reg_arg); }
static void print_longint(uintmax_t reg_arg)		{ printf("%ld", (long int)reg_arg); }
static void print_longlongint(uintmax_t reg_arg)	{ printf("%lld", (long long int)reg_arg); }

static void print_uchar(uintmax_t reg_arg)			{ printf("%hhu", (unsigned char)reg_arg); }
static void print_ushort(uintmax_t reg_arg)			{ printf("%hu", (unsigned short)reg_arg); }
static void print_uint(uintmax_t reg_arg)			{ printf("%u", (unsigned int)reg_arg); }
static void print_ulongint(uintmax_t reg_arg)		{ printf("%lu", (unsigned long int)reg_arg); }
static void print_ulonglongint(uintmax_t reg_arg)	{ printf("%llu", (unsigned long long int)reg_arg); }

static void print_float(uintmax_t reg_arg)			{ printf("%f", (float)reg_arg); }
static void print_double(uintmax_t reg_arg)			{ printf("%f", (double)reg_arg); }
static void print_longdouble(uintmax_t reg_arg)		{ printf("%Lf", (long double)reg_arg); }

static void print_ptr(uintmax_t reg_arg)			{ printf("0x%p", (void *)reg_arg); }
static void print_str(uintmax_t reg_arg)			{ printf("\"%s\"", (char *)reg_arg); }

static void print_struct(uintmax_t reg_arg)			{ printf("Struct 0x%p", (void *)reg_arg); }


#define GET_ARG_TYPE(expr) \
	(_Generic((expr), \
		char: CHAR, unsigned char: UCHAR, \
		short: SHORT, unsigned short: USHORT, \
		int: INT, unsigned int: UINT, \
		long: LINT, unsigned long: ULINT, \
		long long: LLINT, unsigned long long: ULLINT, \
		float: FLOAT, \
		double: DOUBLE, \
		long double: LDOUBLE, \
		void*: PTR, \
		char*: PTRCHAR, \
		int*: PTRINT, \
		struct iovec: -2, \
		default: DEFAULT))

// #define GET_ARG_TYPE(expr) \
// 	(_Generic((expr), \
// 		char: CHAR, unsigned char: UCHAR, \
// 		short: SHORT, unsigned short: USHORT, \
// 		int: INT, unsigned int: UINT, \
// 		long: LINT, unsigned long: ULINT, \
// 		long long: LLINT, unsigned long long: ULLINT, \
// 		float: FLOAT, \
// 		double: DOUBLE, \
// 		long double: LDOUBLE, \
// 		void*: PTR, \
// 		default: STRUCT))

# define STRUCT_IOVEC (unsigned long long)42
# define CHAR_PTR (int *)42

# define T_CHAR 	(char)42
# define T_SHORT 	(short)42
# define T_INT 		(int)42
# define T_LINT 	(long int)42
# define T_LLINT 	(long long int)42
# define T_UCHAR 	(unsigned char)42
# define T_USHORT 	(unsigned short)42
# define T_UINT 	(unsigned int)42
# define T_ULINT 	(unsigned long int)42
# define T_ULLINT 	(unsigned long long int)42
# define T_FLOAT 	(float)42
# define T_DOUBLE 	(double)42
# define T_LDOUBLE 	(long double)42
# define T_PTR 		(void *)42
# define T_PTRCHAR 	(char *)42
# define T_PTRINT 	(int *)42
# define T_SIZE_T 	(size_t)42


int main(void) {
	struct iovec io;
	char 	allow1;
	gid_t  lulz;
	enum { foo, bar };
	printf("%s is of type %d\n", "'a'", GET_ARG_TYPE(T_SIZE_T));
	// printf("%d is of type %d\n", 42, GET_ARG_TYPE(42));
	// printf("%f is of type %d\n", 1.5, GET_ARG_TYPE(1.5));
	// printf("%s is of type %d\n", "foo", GET_ARG_TYPE(foo));
	// printf("%s is of type %d\n", "foo", GET_ARG_TYPE(foo));
	// putchar('\n');
	// printf("%s is of type %d\n", "STRUCT", GET_ARG_TYPE(io));
	// printf("%s is of type %d\n", "gid_t", GET_ARG_TYPE(lulz));
	// printf("%d\n", io);
	// printf("%s is of type %d\n", "sizeof foo", GET_ARG_TYPE(sizeof foo));
	// printf("%s is of type %d\n", "LOL = 1", GET_ARG_TYPE(1L));
	// printf("%s is of type %d\n", "time(NULL)", GET_ARG_TYPE(time(NULL)));
}
