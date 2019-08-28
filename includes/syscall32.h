[  0] = {"restart_syscall", {NONE, NONE, NONE, NONE, NONE, NONE, INT}, &syscall32_generic_handler, &syscall32_generic_end_handler},
[  1] = {"exit", {INT, NONE, NONE, NONE, NONE, NONE, INT}, &syscall32_generic_handler, &syscall32_generic_end_handler},
[  2] = {"fork", {NONE, NONE, NONE, NONE, NONE, NONE, UINT}, &syscall32_generic_handler, &syscall32_generic_end_handler},
[  3] = {"read", {INT, PTR, SIZE_T, NONE, NONE, NONE, SIZE_T}, &syscall_read_handler32, &syscall_read_end_handler32},
[  4] = {"write", {INT, PTR, SIZE_T, NONE, NONE, NONE, SIZE_T}, &syscall32_generic_handler, &syscall32_generic_end_handler}