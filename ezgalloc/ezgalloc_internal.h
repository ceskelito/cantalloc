#ifndef EZGALLOC_INTERNAL_H
# define EZGALLOC_INTERNAL_H

# include <stdlib.h>

typedef enum e_mode
{
	ADD,
	CLEAN_ALL,
	CLEAN_GROUP;
	CREATE,
	NEW,
	RELEASE,
} t_mode;

/* garbage collector node */
typedef struct s_alloc
{
	void			*ptr;
	struct s_alloc	*next;
}	t_alloc;

/* garbage group node */
typedef struct s_group
{
  t_alloc         *garbage_head;
  t_alloc         *garbage_tail;
  char            *tag;
  struct s_group  *next;
} t_group;


/* Allocates size bytes of memory with malloc() and saves
** the pointer in a static linked list, before returning it.
** Returns NULL if malloc fails. */
void	*ez_alloc(size_t size);

/* Allocates size * count bytes of memory with malloc(), fills
** everything with 0s and saves the pointer in a static linked list,
** before returning it. Returns NULL if malloc fails.*/
void	*ez_calloc(size_t size, size_t count);

/* Add an already allocated address at the end of the garbage list.
 * Return the pointer we passed it. */
void	*ez_add(void *ptr);

/* Search for the pointer in the list, and frees the pointer and the node itself;
 * after removed the node from the list */
void	ez_free(void	*ptr);

/* Frees all the memory previously allocated by ezalloc and ezcalloc. */
void	ez_clean(void);

#endif
