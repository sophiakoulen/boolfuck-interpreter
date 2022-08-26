#ifndef EXEC_H
# define EXEC_H
# include "memory.h"

void	change_endianness(char *str);

int	is_zero(t_tape a);

int	compare(t_tape a, t_tape b);

void	flip(t_tape *a);

void	input(t_memory *m, t_tape *i);

void	output(t_memory *m, t_tape *o);

#endif
