[  0] = {"read", {T_INT, T_BUFF, T_ULINT, T_NONE, T_NONE, T_NONE, T_LINT}, &syscall_read_write_handler},
[  1] = {"write", {T_INT, T_BUFF, T_ULINT, T_NONE, T_NONE, T_NONE, T_LINT}, &syscall_read_write_handler},
[  2] = {"open", {T_STR, T_INT, T_UINT, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[  3] = {"close", {T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[  4] = {"stat", {T_STR, T_ADDR, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[  5] = {"fstat", {T_INT, T_ADDR, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[  6] = {"lstat", {T_STR, T_ADDR, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[  7] = {"poll", {T_ADDR, T_ULINT, T_INT, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[  8] = {"lseek", {T_INT, T_LINT, T_INT, T_NONE, T_NONE, T_NONE, T_LINT}, &syscall64_generic_handler},
[  9] = {"mmap", {T_ADDR, T_ULINT, T_INT, T_INT, T_INT, T_LINT, T_ADDR}, &syscall64_generic_handler},
[ 10] = {"mprotect", {T_ADDR, T_ULINT, T_INT, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 11] = {"munmap", {T_ADDR, T_ULINT, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 12] = {"brk", {T_ADDR, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_HEX}, &syscall64_generic_handler},
[ 13] = {"rt_sigaction", {T_INT, T_ADDR, T_ADDR, T_ULINT, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 14] = {"rt_sigprocmask", {T_INT, T_ADDR, T_ADDR, T_ULINT, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 15] = {"rt_sigreturn", {T_HEX, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 16] = {"ioctl", {T_INT, T_ULINT, T_HEX, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 17] = {"pread", {T_INT, T_ADDR, T_ULINT, T_LINT, T_NONE, T_NONE, T_LINT}, &syscall64_generic_handler},
[ 18] = {"pwrite", {T_INT, T_ADDR, T_ULINT, T_LINT, T_NONE, T_NONE, T_LINT}, &syscall64_generic_handler},
[ 19] = {"readv", {T_INT, T_ADDR, T_INT, T_NONE, T_NONE, T_NONE, T_LINT}, &syscall64_generic_handler},
[ 20] = {"writev", {T_INT, T_ADDR, T_INT, T_NONE, T_NONE, T_NONE, T_LINT}, &syscall64_generic_handler},
[ 21] = {"access", {T_STR, T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 22] = {"pipe", {T_ADDR, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 23] = {"select", {T_INT, T_ADDR, T_ADDR, T_ADDR, T_ADDR, T_NONE, T_INT}, &syscall64_generic_handler},
[ 24] = {"sched_yield", {T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 25] = {"mremap", {T_ADDR, T_ULINT, T_ULINT, T_HEX, T_NONE, T_NONE, T_ADDR}, &syscall64_generic_handler},
[ 26] = {"msync", {T_ADDR, T_ULINT, T_INT, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 27] = {"mincore", {T_ADDR, T_ULINT, T_ADDR, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 28] = {"madvise", {T_ADDR, T_ULINT, T_INT, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 29] = {"shmget", {T_UNKNOWN, T_ULINT, T_INT, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 30] = {"shmat", {T_INT, T_ADDR, T_INT, T_NONE, T_NONE, T_NONE, T_ADDR}, &syscall64_generic_handler},
[ 31] = {"shmctl", {T_INT, T_INT, T_ADDR, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 32] = {"dup", {T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 33] = {"dup2", {T_INT, T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 34] = {"pause", {T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 35] = {"nanosleep", {T_ADDR, T_ADDR, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 36] = {"getitimer", {T_INT, T_ADDR, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 37] = {"alarm", {T_UINT, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_UINT}, &syscall64_generic_handler},
[ 38] = {"setitimer", {T_INT, T_ADDR, T_ADDR, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 39] = {"getpid", {T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 40] = {"sendfile", {T_INT, T_INT, T_ADDR, T_ULINT, T_NONE, T_NONE, T_LINT}, &syscall64_generic_handler},
[ 41] = {"socket", {T_INT, T_INT, T_INT, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 42] = {"connect", {T_INT, T_ADDR, T_UINT, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 43] = {"accept", {T_INT, T_ADDR, T_ADDR, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 44] = {"sendto", {T_INT, T_ADDR, T_ULINT, T_INT, T_ADDR, T_UINT, T_LINT}, &syscall64_generic_handler},
[ 45] = {"recvfrom", {T_INT, T_ADDR, T_ULINT, T_INT, T_ADDR, T_ADDR, T_LINT}, &syscall64_generic_handler},
[ 46] = {"sendmsg", {T_INT, T_ADDR, T_INT, T_NONE, T_NONE, T_NONE, T_LINT}, &syscall64_generic_handler},
[ 47] = {"recvmsg", {T_INT, T_ADDR, T_INT, T_NONE, T_NONE, T_NONE, T_LINT}, &syscall64_generic_handler},
[ 48] = {"shutdown", {T_INT, T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 49] = {"bind", {T_INT, T_ADDR, T_UINT, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 50] = {"listen", {T_INT, T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 51] = {"getsockname", {T_INT, T_ADDR, T_ADDR, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 52] = {"getpeername", {T_INT, T_ADDR, T_ADDR, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 53] = {"socketpair", {T_INT, T_INT, T_INT, T_ADDR, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 54] = {"setsockopt", {T_INT, T_INT, T_INT, T_ADDR, T_UINT, T_NONE, T_INT}, &syscall64_generic_handler},
[ 55] = {"getsockopt", {T_INT, T_INT, T_INT, T_ADDR, T_ADDR, T_NONE, T_INT}, &syscall64_generic_handler},
[ 56] = {"clone", {T_ADDR, T_ADDR, T_INT, T_ADDR, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 57] = {"fork", {T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 58] = {"vfork", {T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 59] = {"execve", {T_STR, T_ADDR, T_ADDR, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 60] = {"exit", {T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE}, &syscall64_generic_handler},
[ 61] = {"wait4", {T_INT, T_ADDR, T_INT, T_ADDR, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 62] = {"kill", {T_INT, T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 63] = {"uname", {T_ADDR, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 64] = {"semget", {T_UNKNOWN, T_INT, T_INT, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 65] = {"semop", {T_INT, T_ADDR, T_ULINT, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 66] = {"semctl", {T_INT, T_INT, T_INT, T_HEX, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 67] = {"shmdt", {T_ADDR, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 68] = {"msgget", {T_UNKNOWN, T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 69] = {"msgsnd", {T_INT, T_ADDR, T_ULINT, T_INT, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 70] = {"msgrcv", {T_INT, T_ADDR, T_ULINT, T_LINT, T_INT, T_NONE, T_LINT}, &syscall64_generic_handler},
[ 71] = {"msgctl", {T_INT, T_INT, T_ADDR, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 72] = {"fcntl", {T_INT, T_INT, T_HEX, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 73] = {"flock", {T_INT, T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 74] = {"fsync", {T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 75] = {"fdatasync", {T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 76] = {"truncate", {T_STR, T_LINT, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 77] = {"ftruncate", {T_INT, T_LINT, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 78] = {"getdents", {T_UINT, T_ADDR, T_UINT, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 79] = {"getcwd", {T_STR, T_ULINT, T_NONE, T_NONE, T_NONE, T_NONE, T_STR}, &syscall64_generic_handler},
[ 80] = {"chdir", {T_STR, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 81] = {"fchdir", {T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 82] = {"rename", {T_STR, T_STR, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 83] = {"mkdir", {T_STR, T_UINT, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 84] = {"rmdir", {T_STR, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 85] = {"creat", {T_STR, T_UINT, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 86] = {"link", {T_STR, T_STR, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 87] = {"unlink", {T_STR, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 88] = {"symlink", {T_STR, T_STR, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 89] = {"readlink", {T_STR, T_STR, T_ULINT, T_NONE, T_NONE, T_NONE, T_LINT}, &syscall64_generic_handler},
[ 90] = {"chmod", {T_STR, T_UINT, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 91] = {"fchmod", {T_INT, T_UINT, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 92] = {"chown", {T_STR, T_UINT, T_UINT, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 93] = {"fchown", {T_INT, T_UINT, T_UINT, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 94] = {"lchown", {T_STR, T_UINT, T_UINT, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 95] = {"umask", {T_UINT, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_UINT}, &syscall64_generic_handler},
[ 96] = {"gettimeofday", {T_ADDR, T_ADDR, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 97] = {"getrlimit", {T_INT, T_ADDR, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 98] = {"getrusage", {T_INT, T_ADDR, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[ 99] = {"sysinfo", {T_ADDR, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[100] = {"times", {T_ADDR, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_LINT}, &syscall64_generic_handler},
[101] = {"ptrace", {T_E_PTRACE_REQUEST, T_INT, T_ADDR, T_ADDR, T_NONE, T_NONE, T_LINT}, &syscall64_generic_handler},
[102] = {"getuid", {T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_UINT}, &syscall64_generic_handler},
[103] = {"syslog", {T_INT, T_STR, T_INT, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[104] = {"getgid", {T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_UINT}, &syscall64_generic_handler},
[105] = {"setuid", {T_UINT, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[106] = {"setgid", {T_UINT, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[107] = {"geteuid", {T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_UINT}, &syscall64_generic_handler},
[108] = {"getegid", {T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_UINT}, &syscall64_generic_handler},
[109] = {"setpgid", {T_INT, T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[110] = {"getppid", {T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[111] = {"getpgrp", {T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[112] = {"setsid", {T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[113] = {"setreuid", {T_UINT, T_UINT, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[114] = {"setregid", {T_UINT, T_UINT, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[115] = {"getgroups", {T_INT, T_ADDR, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[116] = {"setgroups", {T_ULINT, T_ADDR, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[117] = {"setresuid", {T_UINT, T_UINT, T_UINT, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[118] = {"getresuid", {T_ADDR, T_ADDR, T_ADDR, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[119] = {"setresgid", {T_UINT, T_UINT, T_UINT, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[120] = {"getresgid", {T_ADDR, T_ADDR, T_ADDR, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[121] = {"getpgid", {T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[122] = {"setfsuid", {T_UINT, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[123] = {"setfsgid", {T_UINT, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[124] = {"getsid", {T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[125] = {"capget", {T_HEX, T_HEX, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[126] = {"capset", {T_HEX, T_HEX, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[127] = {"rt_sigpending", {T_ADDR, T_ULINT, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[128] = {"rt_sigtimedwait", {T_ADDR, T_ADDR, T_ADDR, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[129] = {"rt_sigqueueinfo", {T_INT, T_INT, T_ADDR, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[130] = {"rt_sigsuspend", {T_ADDR, T_ULINT, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[131] = {"sigaltstack", {T_ADDR, T_ADDR, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[132] = {"utime", {T_STR, T_ADDR, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[133] = {"mknod", {T_STR, T_UINT, T_ULINT, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[134] = {"uselib", {T_STR, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[135] = {"personality", {T_ULINT, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[136] = {"ustat", {T_ULINT, T_ADDR, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[137] = {"statfs", {T_STR, T_ADDR, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[138] = {"fstatfs", {T_INT, T_ADDR, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[139] = {"sysfs", {T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[140] = {"getpriority", {T_INT, T_UINT, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[141] = {"setpriority", {T_INT, T_UINT, T_INT, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[142] = {"sched_setparam", {T_INT, T_ADDR, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[143] = {"sched_getparam", {T_INT, T_ADDR, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[144] = {"sched_setscheduler", {T_INT, T_INT, T_ADDR, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[145] = {"sched_getscheduler", {T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[146] = {"sched_get_priority_max", {T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[147] = {"sched_get_priority_min", {T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[148] = {"sched_rr_get_interval", {T_INT, T_ADDR, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[149] = {"mlock", {T_ADDR, T_ULINT, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[150] = {"munlock", {T_ADDR, T_ULINT, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[151] = {"mlockall", {T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[152] = {"munlockall", {T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[153] = {"vhangup", {T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[154] = {"modify_ldt", {T_INT, T_ADDR, T_ULINT, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[155] = {"pivot_root", {T_STR, T_STR, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[156] = {"_sysctl", {T_ADDR, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[157] = {"prctl", {T_INT, T_ULINT, T_ULINT, T_ULINT, T_ULINT, T_NONE, T_INT}, &syscall64_generic_handler},
[158] = {"arch_prctl", {T_INT, T_ADDR, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[159] = {"adjtimex", {T_ADDR, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[160] = {"setrlimit", {T_INT, T_ADDR, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[161] = {"chroot", {T_STR, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[162] = {"sync", {T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE}, &syscall64_generic_handler},
[163] = {"acct", {T_STR, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[164] = {"settimeofday", {T_ADDR, T_ADDR, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[165] = {"mount", {T_STR, T_STR, T_STR, T_ULINT, T_ADDR, T_NONE, T_INT}, &syscall64_generic_handler},
[166] = {"umount2", {T_STR, T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[167] = {"swapon", {T_STR, T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[168] = {"swapoff", {T_STR, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[169] = {"reboot", {T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[170] = {"sethostname", {T_STR, T_ULINT, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[171] = {"setdomainname", {T_STR, T_ULINT, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[172] = {"iopl", {T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[173] = {"ioperm", {T_ULINT, T_ULINT, T_INT, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[174] = {"create_module", {T_STR, T_ULINT, T_NONE, T_NONE, T_NONE, T_NONE, T_CADDR_T}, &syscall64_generic_handler},
[175] = {"init_module", {T_ADDR, T_ULINT, T_STR, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[176] = {"delete_module", {T_STR, T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[177] = {"get_kernel_syms", {T_ADDR, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[178] = {"query_module", {T_STR, T_INT, T_ADDR, T_ULINT, T_ADDR, T_NONE, T_INT}, &syscall64_generic_handler},
[179] = {"quotactl", {T_INT, T_STR, T_INT, T_CADDR_T, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[180] = {"nfsservctl", {T_INT, T_ADDR, T_ADDR, T_NONE, T_NONE, T_NONE, T_LINT}, &syscall64_generic_handler},
[181] = {"getpmsg", {T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_LLINT}, &syscall64_generic_handler},
[182] = {"putpmsg", {T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_LLINT}, &syscall64_generic_handler},
[183] = {"afs_syscall", {T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_LLINT}, &syscall64_generic_handler},
[184] = {"tuxcall", {T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_LLINT}, &syscall64_generic_handler},
[185] = {"security", {T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_LLINT}, &syscall64_generic_handler},
[186] = {"gettid", {T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[187] = {"readahead", {T_INT, T_LINT, T_ULINT, T_NONE, T_NONE, T_NONE, T_LINT}, &syscall64_generic_handler},
[188] = {"setxattr", {T_STR, T_STR, T_ADDR, T_ULINT, T_INT, T_NONE, T_INT}, &syscall64_generic_handler},
[189] = {"lsetxattr", {T_STR, T_STR, T_ADDR, T_ULINT, T_INT, T_NONE, T_INT}, &syscall64_generic_handler},
[190] = {"fsetxattr", {T_INT, T_STR, T_ADDR, T_ULINT, T_INT, T_NONE, T_INT}, &syscall64_generic_handler},
[191] = {"getxattr", {T_STR, T_STR, T_ADDR, T_ULINT, T_NONE, T_NONE, T_LINT}, &syscall64_generic_handler},
[192] = {"lgetxattr", {T_STR, T_STR, T_ADDR, T_ULINT, T_NONE, T_NONE, T_LINT}, &syscall64_generic_handler},
[193] = {"fgetxattr", {T_INT, T_STR, T_ADDR, T_ULINT, T_NONE, T_NONE, T_LINT}, &syscall64_generic_handler},
[194] = {"listxattr", {T_STR, T_STR, T_ULINT, T_NONE, T_NONE, T_NONE, T_LINT}, &syscall64_generic_handler},
[195] = {"llistxattr", {T_STR, T_STR, T_ULINT, T_NONE, T_NONE, T_NONE, T_LINT}, &syscall64_generic_handler},
[196] = {"flistxattr", {T_INT, T_STR, T_ULINT, T_NONE, T_NONE, T_NONE, T_LINT}, &syscall64_generic_handler},
[197] = {"removexattr", {T_STR, T_STR, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[198] = {"lremovexattr", {T_STR, T_STR, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[199] = {"fremovexattr", {T_INT, T_STR, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[200] = {"tkill", {T_INT, T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[201] = {"time", {T_ADDR, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_LINT}, &syscall64_generic_handler},
[202] = {"futex", {T_ADDR, T_INT, T_INT, T_ADDR, T_ADDR, T_INT, T_INT}, &syscall64_generic_handler},
[203] = {"sched_setaffinity", {T_INT, T_ULINT, T_ADDR, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[204] = {"sched_getaffinity", {T_INT, T_ULINT, T_ADDR, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[205] = {"set_thread_area", {T_ULINT, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[206] = {"io_setup", {T_UINT, T_ADDR, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[207] = {"io_destroy", {T_ULINT, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[208] = {"io_getevents", {T_ULINT, T_LINT, T_LINT, T_ADDR, T_ADDR, T_NONE, T_INT}, &syscall64_generic_handler},
[209] = {"io_submit", {T_ULINT, T_LINT, T_ADDR, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[210] = {"io_cancel", {T_ULINT, T_ADDR, T_ADDR, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[211] = {"get_thread_area", {T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[212] = {"lookup_dcookie", {T_ULLINT, T_STR, T_ULINT, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[213] = {"epoll_create", {T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[214] = {"epoll_ctl_old", {T_HEX, T_HEX, T_HEX, T_ADDR, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[215] = {"epoll_wait_old", {T_HEX, T_ADDR, T_HEX, T_HEX, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[216] = {"remap_file_pages", {T_ADDR, T_ULINT, T_INT, T_ULINT, T_INT, T_NONE, T_INT}, &syscall64_generic_handler},
[217] = {"getdents", {T_UINT, T_ADDR, T_UINT, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[218] = {"set_tid_address", {T_ADDR, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_LINT}, &syscall64_generic_handler},
[219] = {"restart_syscall", {T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[220] = {"semtimedop", {T_INT, T_ADDR, T_ULINT, T_ADDR, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[221] = {"fadvise64", {T_INT, T_LINT, T_LINT, T_HEX, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[222] = {"timer_create", {T_INT, T_ADDR, T_ADDR, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[223] = {"timer_settime", {T_INT, T_INT, T_ADDR, T_ADDR, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[224] = {"timer_gettime", {T_INT, T_ADDR, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[225] = {"timer_getoverrun", {T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[226] = {"timer_delete", {T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[227] = {"clock_settime", {T_INT, T_ADDR, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[228] = {"clock_gettime", {T_INT, T_ADDR, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[229] = {"clock_getres", {T_INT, T_ADDR, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[230] = {"clock_nanosleep", {T_INT, T_INT, T_ADDR, T_ADDR, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[231] = {"exit_group", {T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE}, &syscall64_generic_handler},
[232] = {"epoll_wait", {T_HEX, T_ADDR, T_HEX, T_HEX, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[233] = {"epoll_ctl", {T_HEX, T_HEX, T_HEX, T_ADDR, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[234] = {"tgkill", {T_INT, T_INT, T_INT, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[235] = {"utimes", {T_STR, T_ADDR, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[236] = {"vserver", {T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_LLINT}, &syscall64_generic_handler},
[237] = {"mbind", {T_ADDR, T_ULINT, T_INT, T_ADDR, T_ULINT, T_UINT, T_LINT}, &syscall64_generic_handler},
[238] = {"set_mempolicy", {T_INT, T_ADDR, T_ULINT, T_NONE, T_NONE, T_NONE, T_LINT}, &syscall64_generic_handler},
[239] = {"get_mempolicy", {T_ADDR, T_ADDR, T_ULINT, T_ADDR, T_ULINT, T_NONE, T_LINT}, &syscall64_generic_handler},
[240] = {"mq_open", {T_STR, T_INT, T_UINT, T_ADDR, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[241] = {"mq_unlink", {T_STR, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[242] = {"mq_timedsend", {T_INT, T_STR, T_ULINT, T_UINT, T_ADDR, T_NONE, T_INT}, &syscall64_generic_handler},
[243] = {"mq_timedreceive", {T_INT, T_STR, T_ULINT, T_ADDR, T_ADDR, T_NONE, T_LINT}, &syscall64_generic_handler},
[244] = {"mq_notify", {T_INT, T_ADDR, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[245] = {"mq_getsetattr", {T_INT, T_ADDR, T_ADDR, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[246] = {"kexec_load", {T_ULINT, T_ULINT, T_ADDR, T_ULINT, T_NONE, T_NONE, T_LINT}, &syscall64_generic_handler},
[247] = {"waitid", {T_UINT, T_UINT, T_ADDR, T_INT, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[248] = {"add_key", {T_STR, T_STR, T_ADDR, T_ULINT, T_INT, T_NONE, T_INT}, &syscall64_generic_handler},
[249] = {"request_key", {T_STR, T_STR, T_STR, T_INT, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[250] = {"keyctl", {T_HEX, T_HEX, T_HEX, T_HEX, T_HEX, T_NONE, T_LINT}, &syscall64_generic_handler},
[251] = {"ioprio_set", {T_INT, T_INT, T_INT, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[252] = {"ioprio_get", {T_INT, T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[253] = {"inotify_init", {T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[254] = {"inotify_add_watch", {T_INT, T_STR, T_UINT, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[255] = {"inotify_rm_watch", {T_INT, T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[256] = {"migrate_pages", {T_INT, T_ULINT, T_ADDR, T_ADDR, T_NONE, T_NONE, T_LINT}, &syscall64_generic_handler},
[257] = {"openat", {T_INT, T_STR, T_INT, T_UINT, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[258] = {"mkdirat", {T_INT, T_STR, T_UINT, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[259] = {"mknodat", {T_INT, T_STR, T_UINT, T_ULINT, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[260] = {"fchownat", {T_INT, T_STR, T_UINT, T_UINT, T_INT, T_NONE, T_INT}, &syscall64_generic_handler},
[261] = {"futimesat", {T_INT, T_STR, T_ADDR, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[262] = {"newfstatat", {T_INT, T_ADDR, T_ADDR, T_INT, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[263] = {"unlinkat", {T_INT, T_STR, T_INT, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[264] = {"renameat", {T_INT, T_STR, T_INT, T_STR, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[265] = {"linkat", {T_INT, T_STR, T_INT, T_STR, T_INT, T_NONE, T_INT}, &syscall64_generic_handler},
[266] = {"symlinkat", {T_STR, T_INT, T_STR, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[267] = {"readlinkat", {T_INT, T_STR, T_STR, T_ULINT, T_NONE, T_NONE, T_LINT}, &syscall64_generic_handler},
[268] = {"fchmodat", {T_INT, T_STR, T_UINT, T_INT, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[269] = {"faccessat", {T_INT, T_STR, T_INT, T_INT, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[270] = {"pselect6", {T_INT, T_ADDR, T_ADDR, T_ADDR, T_ADDR, T_ADDR, T_INT}, &syscall64_generic_handler},
[271] = {"ppoll", {T_ADDR, T_ULINT, T_ADDR, T_ADDR, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[272] = {"unshare", {T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[273] = {"set_robust_list", {T_ADDR, T_ULINT, T_NONE, T_NONE, T_NONE, T_NONE, T_LINT}, &syscall64_generic_handler},
[274] = {"get_robust_list", {T_INT, T_ADDR, T_ADDR, T_NONE, T_NONE, T_NONE, T_LINT}, &syscall64_generic_handler},
[275] = {"splice", {T_INT, T_ADDR, T_INT, T_ADDR, T_ULINT, T_UINT, T_LINT}, &syscall64_generic_handler},
[276] = {"tee", {T_INT, T_INT, T_ULINT, T_UINT, T_NONE, T_NONE, T_LINT}, &syscall64_generic_handler},
[277] = {"sync_file_range", {T_INT, T_LINT, T_LINT, T_UINT, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[278] = {"vmsplice", {T_INT, T_ADDR, T_ULINT, T_UINT, T_NONE, T_NONE, T_LINT}, &syscall64_generic_handler},
[279] = {"move_pages", {T_INT, T_ULINT, T_ADDR, T_ADDR, T_ADDR, T_INT, T_LINT}, &syscall64_generic_handler},
[280] = {"utimensat", {T_INT, T_STR, T_ADDR, T_INT, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[281] = {"epoll_pwait", {T_INT, T_ADDR, T_INT, T_INT, T_ADDR, T_NONE, T_INT}, &syscall64_generic_handler},
[282] = {"signalfd", {T_INT, T_ADDR, T_INT, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[283] = {"timerfd_create", {T_INT, T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[284] = {"eventfd", {T_UINT, T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[285] = {"fallocate", {T_INT, T_INT, T_LINT, T_LINT, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[286] = {"timerfd_settime", {T_INT, T_INT, T_ADDR, T_ADDR, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[287] = {"timerfd_gettime", {T_INT, T_ADDR, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[288] = {"accept4", {T_INT, T_ADDR, T_ADDR, T_INT, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[289] = {"signalfd4", {T_INT, T_ADDR, T_INT, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[290] = {"eventfd2", {T_UINT, T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[291] = {"epoll_create1", {T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[292] = {"dup3", {T_INT, T_INT, T_INT, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[293] = {"pipe2", {T_ADDR, T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[294] = {"inotify_init1", {T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[295] = {"preadv", {T_INT, T_ADDR, T_INT, T_LINT, T_NONE, T_NONE, T_LINT}, &syscall64_generic_handler},
[296] = {"pwritev", {T_INT, T_ADDR, T_INT, T_LINT, T_NONE, T_NONE, T_LINT}, &syscall64_generic_handler},
[297] = {"rt_tgsigqueueinfo", {T_INT, T_INT, T_INT, T_ADDR, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[298] = {"perf_event_open", {T_ADDR, T_INT, T_INT, T_INT, T_ULINT, T_NONE, T_INT}, &syscall64_generic_handler},
[299] = {"recvmmsg", {T_INT, T_ADDR, T_UINT, T_INT, T_ADDR, T_NONE, T_INT}, &syscall64_generic_handler},
[300] = {"fanotify_init", {T_UINT, T_UINT, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[301] = {"fanotify_mark", {T_INT, T_UINT, T_ULINT, T_INT, T_STR, T_NONE, T_INT}, &syscall64_generic_handler},
[302] = {"prlimit", {T_INT, T_INT, T_ADDR, T_ADDR, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[303] = {"name_to_handle_at", {T_INT, T_STR, T_ADDR, T_ADDR, T_INT, T_NONE, T_INT}, &syscall64_generic_handler},
[304] = {"open_by_handle_at", {T_INT, T_ADDR, T_INT, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[305] = {"clock_adjtime", {T_HEX, T_ADDR, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[306] = {"syncfs", {T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[307] = {"sendmmsg", {T_INT, T_ADDR, T_UINT, T_INT, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[308] = {"setns", {T_INT, T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[309] = {"getcpu", {T_ADDR, T_ADDR, T_ADDR, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[310] = {"process_vm_readv", {T_INT, T_ADDR, T_ULINT, T_ADDR, T_ULINT, T_ULINT, T_LINT}, &syscall64_generic_handler},
[311] = {"process_vm_writev", {T_INT, T_ADDR, T_ULINT, T_ADDR, T_ULINT, T_ULINT, T_LINT}, &syscall64_generic_handler},
[312] = {"kcmp", {T_INT, T_INT, T_INT, T_ULINT, T_ULINT, T_NONE, T_INT}, &syscall64_generic_handler},
[313] = {"finit_module", {T_INT, T_STR, T_INT, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[314] = {"sched_setattr", {T_INT, T_ADDR, T_UINT, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[315] = {"sched_getattr", {T_INT, T_ADDR, T_UINT, T_UINT, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[316] = {"renameat2", {T_INT, T_STR, T_INT, T_STR, T_UINT, T_NONE, T_INT}, &syscall64_generic_handler},
[317] = {"seccomp", {T_UINT, T_UINT, T_ADDR, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[318] = {"getrandom", {T_ADDR, T_ULINT, T_UINT, T_NONE, T_NONE, T_NONE, T_LINT}, &syscall64_generic_handler},
[319] = {"memfd_create", {T_STR, T_UINT, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[320] = {"kexec_file_load", {T_INT, T_INT, T_ULINT, T_STR, T_ULINT, T_NONE, T_LINT}, &syscall64_generic_handler},
[321] = {"bpf", {T_INT, T_ADDR, T_UINT, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[322] = {"execveat", {T_INT, T_STR, T_ADDR, T_ADDR, T_INT, T_NONE, T_INT}, &syscall64_generic_handler},
[323] = {"userfaultfd", {T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[324] = {"membarrier", {T_INT, T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[325] = {"mlock2", {T_ADDR, T_ULINT, T_INT, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[326] = {"copy_file_range", {T_INT, T_ADDR, T_INT, T_ADDR, T_ULINT, T_UINT, T_LINT}, &syscall64_generic_handler},
[327] = {"preadv2", {T_INT, T_ADDR, T_INT, T_LINT, T_INT, T_NONE, T_LINT}, &syscall64_generic_handler},
[328] = {"pwritev2", {T_INT, T_ADDR, T_INT, T_LINT, T_INT, T_NONE, T_LINT}, &syscall64_generic_handler},
[329] = {"pkey_mprotect", {T_ADDR, T_ULINT, T_INT, T_INT, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[330] = {"pkey_alloc", {T_UINT, T_UINT, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[331] = {"pkey_free", {T_INT, T_NONE, T_NONE, T_NONE, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler},
[332] = {"statx", {T_INT, T_STR, T_INT, T_UINT, T_ADDR, T_NONE, T_INT}, &syscall64_generic_handler},
[333] = {"io_pgetevents", {T_ULINT, T_LINT, T_LINT, T_ADDR, T_ADDR, T_NONE, T_INT}, &syscall64_generic_handler},
[334] = {"rseq", {T_ADDR, T_HEX, T_HEX, T_HEX, T_NONE, T_NONE, T_INT}, &syscall64_generic_handler}
