#ifndef PARSE_H
# define PARSE_H

# include <stdlib.h>
# include <stdio.h>

typedef struct s_instruction
{
	char			val;
	struct s_instruction	*right;
	struct s_instruction	*left;
} t_instruction;

void	append_node(t_instruction *node, t_instruction **next);

void	parse(t_instruction **root, t_instruction *parent, char **str);

void	free_tree(t_instruction *root);

#endif
