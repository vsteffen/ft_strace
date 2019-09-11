// Basic type
[CHAR	] = &print_char,
[SHORT	] = &print_short,
[INT	] = &print_int,
[LINT	] = &print_longint,
[LLINT	] = &print_longlongint,
[UCHAR	] = &print_uchar,
[USHORT	] = &print_ushort,
[UINT	] = &print_uint,
[ULINT	] = &print_ulongint,
[ULLINT	] = &print_ulonglongint,
[FLOAT	] = &print_float,
[DOUBLE	] = &print_double,
[LDOUBLE] = &print_longdouble,
[ADDR	] = &print_addr,
[BUFF	] = &print_buff,
[STR	] = &print_str,
[UNKNOWN] = &print_longlongint,

// Specific type
[T_CADDR_T		] = &print_addr,
[T_SIGHANDLER_T		] = &print_addr,
[E_PTRACE_REQUEST	] = &print_addr
