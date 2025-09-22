#include "ezalloc.h"
#include "ezgalloc_internal.h"
#include "ezgalloc.h"

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

static t_garbage_group *safe_new_group(char *name)
{
    t_garbage_group *group;

    group = malloc(sizeof(t_garbage_group));
    local_strcpy(group->group, name);

}

static void *ezalloc_group_handler(size_t size, int mode, char *group, void *target)
{
    static t_garbage_group *groups_head;
    static t_garbage_group *groups_tail;

    if (mode == CREATE)
    {
        if (!group)
            return (NULL);
    }


}

void    ezg_create_group(char *group)
{
    ezalloc_group_handler(0, CREATE, group, NULL);
}


void    *ezg_alloc(char *group, size_t  size)
{

}
