#ifndef FT_STRACE_H
# define FT_STRACE_H

# include "libft.h"

# include <sys/ptrace.h>
# include <sys/user.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdbool.h>
# include <errno.h>


char			*get_absolute_path(char *prog_name);


#endif
