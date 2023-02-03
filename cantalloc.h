#ifndef CANTALLOC_H
# define CANTALLOC_H

# include <stdlib.h>

# define NEW	0
# define CLEAN	1

/* garbage collector node */
typedef struct s_alloc
{
	void		*ptr;
	struct s_alloc	*next;
}	t_alloc;

/* funcs */
void	*cantalloc(size_t size);
void	cantalloc_clean(void);

#endif
