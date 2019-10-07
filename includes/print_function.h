// Basic type
[T_CHAR		] = &print_char,
[T_SHORT	] = &print_short,
[T_INT		] = &print_int,
[T_LINT		] = &print_longint,
[T_LLINT	] = &print_longlongint,
[T_UCHAR	] = &print_uchar,
[T_USHORT	] = &print_ushort,
[T_UINT		] = &print_uint,
[T_ULINT	] = &print_ulongint,
[T_ULLINT	] = &print_ulonglongint,
[T_FLOAT	] = &print_float,
[T_DOUBLE	] = &print_double,
[T_LDOUBLE	] = &print_longdouble,
[T_ADDR		] = &print_addr,
[T_BUFF		] = &print_buff,
[T_STR		] = &print_str,
[T_UNKNOWN	] = &print_longlongint,

// Specific type
[T_CADDR_T		] = &print_addr,
[T_SIGHANDLER_T		] = &print_addr,
[T_E_PTRACE_REQUEST	] = &print_addr
