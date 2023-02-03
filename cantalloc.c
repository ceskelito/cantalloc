#include "cantalloc.h"

static t_alloc	*new_node(void	*ptr)
{
	t_alloc	*node;

	node = malloc(sizeof(t_alloc));
	node->ptr = ptr;
	node->next = NULL;
	return (node);
}

static void	*cantalloc_handler(size_t size, int mode)
{
	static t_alloc	*garbage_head;
	static t_alloc	*garbage_tail;
	void		*new_ptr;

	if (mode == NEW)
	{
		new_ptr = malloc(size);
		if (!new_ptr)
			return (NULL);
		if (!garbage_head)
		{
			garbage_head = new_node(new_ptr);
			garbage_tail = garbage_head;
		}
		else
		{
			garbage_tail->next = new_node(new_ptr);
			garbage_tail = garbage_tail->next;
		}
		return (new_ptr);
	}
	else if (mode == CLEAN)
	{
		t_alloc	*tmp;

		tmp = garbage_head;
		while (tmp)
		{
			garbage_head = garbage_head->next;
			free(tmp->ptr);
			free(tmp);
			tmp = garbage_head;
		}
	}
	return (NULL);
}

void	*cantalloc(size_t size)
{
	return (cantalloc_handler(size, NEW));
}

void	cantalloc_clean(void)
{
	cantalloc_handler(0, CLEAN);
}
