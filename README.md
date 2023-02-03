# cantalloc

*void	\*cantalloc(size_t size)*

Allocates size bytes of memory with malloc() and
saves the pointer in a static linked list, before
returning it.
Returns NULL if malloc fails.

*void	\*ccantalloc(size_t size, size_t count)*

Allocates size * count bytes of memory with malloc(),
fills everything with 0s and saves the pointer in a
static linked list, before returning it.
Returns NULL if malloc fails.

*void	cantalloc_clean(void)*

Frees all the memory previously allocated by cantalloc
and ccantalloc.
