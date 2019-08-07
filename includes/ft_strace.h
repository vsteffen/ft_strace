#ifndef FT_STRACE_H
# define FT_STRACE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <string.h>
# include <sys/ptrace.h>
# include <sys/user.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdbool.h>
# include <errno.h>


char			*get_absolute_path(char *prog_name);


#endif
