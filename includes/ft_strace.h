#ifndef FT_STRACE_H
# define FT_STRACE_H

# include "libft.h"

typedef struct		s_elem {
	struct s_elem	*prec;
	struct s_elem	*next;
}					t_elem;

typedef struct		s_project {
	t_elem			*elem;
	t_elem			*current;
	t_elem			*last;
}					t_project;

#endif
