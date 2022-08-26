#include "memory.h"
#include <stdio.h>

void	init_tape(t_tape *t, char *str)
{
	if (str)
		t->size = strlen(str) + 1;
	else
		t->size = INIT_SIZE;
	t->data = calloc(t->size, sizeof(char));
	t->mask = 1 << 7;
	t->ptr = 0;
	if (str)
		strcpy(t->data, str);
}

void	init_memory(t_memory *m)
{
	init_tape(&(m->left), 0);
	init_tape(&(m->right), 0);
	(m->left).ptr = -1;
}

void	free_tape(t_tape *a)
{
	free(a->data);
}

void	free_memory(t_memory *m)
{
	free_tape(&(m->left));
	free_tape(&(m->right));
}

void    tape_up(t_tape *a)
{
        if (a->mask != 1)
                a->mask = (char)((unsigned char)a->mask >> 1);
        else
        {
                if (a->ptr == a->size - 1)
                {
                        a->data = realloc(a->data, 2 * a->size);
			for (int i = a->size; i < 2 * a->size; i++)
				(a->data)[i] = 0;
			a->size *= 2;
                }
                a->ptr++;
                a->mask = 1 << 7;
        }
}

int     tape_down(t_tape *a)
{
        if ((unsigned char) a->mask != 1 << 7)
                a->mask = (char)((unsigned char)a->mask << 1);
        else
        {
                if (a->ptr == 0)
                        return (0);
                a->ptr--;
                a->mask = 1;
        }
        return (1);
}

void    mem_right(t_memory *m)
{
        if ((m->left).ptr == -1)
        {
                tape_up(&(m->right));
        }
        else
        {
                if (!tape_down(&(m->left)))
                {
                        (m->left).ptr = -1;
                        (m->right).ptr = 0;
                        (m->right).mask = 1 << 7;
                }
        }
}

void    mem_left(t_memory *m)
{
        if ((m->right).ptr == -1)
        {
                tape_up(&(m->left));
        }
        else
        {
                if (!tape_down(&(m->right)))
                {
                        (m->right).ptr = -1;
                        (m->left).ptr = 0;
                        (m->left).mask = 1 << 7;
                }
        }
}

t_tape	*select_tape(t_memory *m)
{
	if ((m->left).ptr == -1)
		return &(m->right);
	else
		return &(m->left);
}
