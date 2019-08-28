[  0] = {"restart_syscall", {NONE, NONE, NONE, NONE, NONE, NONE, INT}, &syscall32_generic_handler},
[  1] = {"exit", {INT, NONE, NONE, NONE, NONE, NONE, INT}, &syscall32_generic_handler},
[  2] = {"fork", {NONE, NONE, NONE, NONE, NONE, NONE, UINT}, &syscall32_generic_handler},
[  3] = {"read", {INT, BUFF, SIZE_T, NONE, NONE, NONE, SIZE_T}, &syscall_read_write_handler},
[  4] = {"write", {INT, BUFF, SIZE_T, NONE, NONE, NONE, SIZE_T}, &syscall_read_write_handler}