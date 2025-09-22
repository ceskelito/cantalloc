#include "ezalloc.h"

static t_alloc	*new_node(void	*ptr)
{
	t_alloc	*node;

	node = malloc(sizeof(t_alloc));
	node->ptr = ptr;
	node->next = NULL;
	return (node);
}

static t_alloc *safe_new_node(t_alloc **head, t_alloc **tail, void *ptr)
{
	if (!ptr)
		return (NULL);
	if (!*head)
	{
		*head = new_node(ptr);
		*tail = *head;
		num e_mode
	else
	{
		(*tail)->next = new_node(ptr);
		*tail = (*tail)->next;
	}
	return (ptr);

}

static void	clean_garbage_list(t_alloc *head)
{
	t_alloc	*tmp;

	tmp = head;
	while (tmp)
	{
		head = head->next;
		free(tmp->ptr);
		free(tmp);
		tmp = head;
	}
}

static void	clean_garbage_node(t_alloc **head, void *target_to_free)
{
	t_alloc	*curr;
	t_alloc	*prev;

	if (target_to_free == NULL)
		return ;
	curr = *head;
	prev = NULL;
	while (curr != NULL)
	{
		if (curr->ptr == target_to_free)
		{
			if (curr == *head)
				*head = curr->next;
			else
				prev->next = curr->next;
			free(curr->ptr);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

static void	*ezalloc_handler(size_t size, int mode, void *target)
{
	static t_alloc	*garbage_head;
	static t_alloc	*garbage_tail;
	void			*new_ptr;

	if (mode == NEW)
	{
		new_ptr = malloc(size);
		if (!new_ptr)
			return (NULL);
		safe_new_node(&garbage_head, &garbage_tail, new_ptr);
		return (new_ptr);
	}
	else if (mode == ADD)
	{
		if (!target)
			return (NULL);
		safe_new_node(&garbage_head, &garbage_tail, target);
		return (target);
	}
	else if (mode == CLEAN)
		clean_garbage_list(garbage_head);
	else if (mode == RELEASE)
		clean_garbage_node(&garbage_head, target);
	return (NULL);
}

void	*ez_alloc(size_t size)
{
	return (ezalloc_handler(size, NEW, NULL));
}

void	*ez_calloc(size_t size, size_t count)
{
	char	*new_ptr;
	size_t	i;

	new_ptr = ezalloc_handler(size * count, NEW, NULL);
	if (!new_ptr)
		return (NULL);
	i = 0;
	while (i < size * count)
	{
		new_ptr[i] = 0;
		++i;
	}
	return ((void *)new_ptr);
}

void	*ez_add(void	*ptr)
{
	ezalloc_handler(0, ADD, ptr);
	return (ptr);
}

void	ez_free(void *ptr)
{
	ezalloc_handler(0, RELEASE, ptr);
}

void	ez_clean(void)
{
	ezalloc_handler(0, CLEAN, NULL);
}
