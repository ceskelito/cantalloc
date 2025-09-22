#include "ezalloc.h"
#include "ezgalloc_internal.h"
#include "ezgalloc.h"
#include "stdbool.h"

static char *local_strcpy(char *dest, const char *src)
{
    while (*src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0'; // chiude la stringa
    return dest;
}

int local_strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

/* Returns a pointer to the tag group */
static t_group	*get_group(t_group **head, char *tag)
{
  t_group *curr;

  curr = *head;
  while(curr)
  {
    if (strcmp(curr->tag, tag) == 0)
      return (curr);
    curr = curr->next;
  }
  return (NULL);
}

static t_garbage_group *safe_new_group(t_group **head, t_group **tail, char *tag)
{
    t_group *group;

    if (get_group(*head, tag) != NULL)
      return (NULL);
    group = malloc(sizeof(t_group));
    local_strcpy(group->tag, tag);
    if (!*head)
    {
		*head = group;
		*tail = *head;
    }
	else
	{
		(*tail)->next = group;
		*tail = (*tail)->next;
	}
	return (group);

}

static void *ezg_alloc_handler(size_t size, int mode, char *tag, void *target)
{
    static t_group	*groups_head;
    static t_group	*groups_tail;
	t_group			*group;
	void			*new_ptr;

    if (mode == CREATE)
    {
        if (!tag || strcmp(tag, ALL_GROUPS) == 0)
            return (NULL);
        return (safe_new_group(&groups_head));
    }
	else
	{
		group = get_group(&groups_head, tag);
		if (!group)
			return (NULL);
		if (mode == NEW)
		{
			new_ptr = malloc(size);
			if (!new_ptr)
				return (NULL);
			safe_new_node(&(group->garbage_head), &(group->garbage_tail), new_ptr);
			return (new_ptr);
		}
		else if (mode == ADD)
		{
			if (!target)
				return (NULL);
			safe_new_node(&(group->garbage_head), &(group->garbage_tail), target);
			return (target);
		}
		else if (mode == CLEAN_GROUP)
			clean_garbage_list(group->garbage_head);
		else if (mode == CLEAN_ALL)
			clean_all_groups(&groups_head);
	}
	return (NULL);
}

int	ezg_group_create(char *tag)
{
	size_t	size;
	void	*target;

	size = 0;
	target = NULL;
    if (ezg_alloc_handler(size, CREATE, tag, target) == NULL)
		return (1);
	return (0);
}


void    *ezg_alloc(char *tag, size_t  size)
{
	void	*target;

	target = NULL;
	ezg_alloc_handler(size, NEW, tag, target);
}

void	*ezg_add(char *tag, void *ptr)
{
	size_t	size;

	size = 0;
	ezg_alloc_handler(size, ADD, tag, target);
	return (target);
}

ezg_clean_group(char *tag)
{
	size_t	size;
	void	*ptr;

	size = 0;
	ptr = NULL;
	ezg_alloc_handler(size, CLEAN_GROUP, tag, ptr);
}

ezg_clean(void)
{
	size_t	size;
	char	*tag;
	void	*ptr;

	size = 0;
	tag = NULL;
	ptr = NULL;
	ezg_alloc_handler(size, CLEAN_ALL, tag, ptr);
}

void	*ezg_calloc(char *tag, size_t size, size_t count)
{

}
