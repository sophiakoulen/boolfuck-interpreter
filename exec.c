#include <stdio.h>
#include <string.h>

#include "exec.h"
#include "memory.h"

void	change_endianness(char *str)
{
	char	byte;

	while (*str)
	{
		byte = 0;
		for (int i = 0; i < 8; i++)
		{
			if(*str & (1 << i))
				byte ^= (1 << (7 - i)); 	
		}
		*str = byte;
		str++;		
	}
}

int	is_zero(t_tape a)
{
	return ((a.data[a.ptr] & a.mask) == 0);
}

int	compare(t_tape a, t_tape b)
{
	char	A, B;

	A = a.data[a.ptr] & a.mask;
	B = b.data[b.ptr] & b.mask;
	return (A == B || (A != 0 && B != 0));
}

void	flip(t_tape *a)
{
	a->data[a->ptr] ^= a->mask;
}

void	output(t_memory *m, t_tape *o)
{	
	t_tape	*t;

	t = select_tape(m);
	if (!compare(*t, *o))
		flip(o);
	tape_up(o);
}

void	input(t_memory *m, t_tape *i)
{
	t_tape	*t;

	t = select_tape(m);
	if (!compare(*t, *i))
		flip(t);
	tape_up(i);
}
/*
int main(int argc, char **argv)
{
	char mask = 1 << 0;
	char c = 1 << 0;
	char new = mask & c;
	printf("%d, %c\n", new, new);
	return 0;
}
*/
