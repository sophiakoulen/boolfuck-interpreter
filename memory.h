#ifndef MEMORY_H
# define MEMORY_H

# include <stdlib.h>
# include <string.h>

typedef struct s_tape
{
	char	*data;
	int	size;
	int	ptr;
	char	mask;
} t_tape;

typedef struct s_memory
{
	t_tape	left;
	t_tape	right;
} t_memory;

#define INIT_SIZE 16

void	init_tape(t_tape *t, char *str);

void	init_memory(t_memory *m);

void	free_tape(t_tape *a);

void	free_memory(t_memory *m);

void    tape_up(t_tape *a);

int     tape_down(t_tape *a);

void    mem_right(t_memory *m);

void    mem_left(t_memory *m);

t_tape	*select_tape(t_memory *m);

#endif
