#ifndef EZGALLOC_H
# define EZGALLOC_H

# include <stdlib.h>

// typedef enum e_mode
// {
// 	NEW,
// 	CLEAN,
// 	RELEASE,
// 	ADD
// } t_mode;

/* garbage collector node */
typedef struct s_galloc
{
	void			*ptr;
	char            *group;
	struct s_galloc	*next;
}	t_galloc;

/* Allocates size bytes of memory with malloc() and saves
** the pointer in a static linked list, before returning it.
** Every "group" is a different list which can be managed separatly from the other.
** Returns NULL if malloc fails. */
void	*ezg_alloc(char *group, size_t size);

/* Allocates size * count bytes of memory with malloc(), fills
** everything with 0s and saves the pointer in a static linked list,
** before returning it.
** Every "group" is a different list which can be managed separatly from the other.
** Returns NULL if malloc fails.*/
void	*ezg_calloc(char *group, size_t size, size_t count);

/* Add an already allocated address at the end of the "group" garbage list.
 * Return the pointer we passed it. */
void	*ezg_add(char *group, void *ptr);

/* Search for the pointer in the "group" list, and frees the pointer and the node itself;
 * after removed the node from the list */
void	ezg_free(char *group, void	*ptr);

/* Frees all the memory previously allocated by ezg_alloc and ezg_calloc
 * in the "grou" named list.
. */
void	ezg_clean(char *group);

#endif
