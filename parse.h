#ifndef PARSE_H
# define PARSE_H

# include <stdlib.h>
# include <stdio.h>

typedef struct s_instruction
{
	char			val;
	struct s_instruction	*right;
	struct s_instruction	*left;
	struct s_instruction	*parent;
} t_instruction;

void	append_node(t_instruction *node, t_instruction **next);

void	parse(t_instruction *root, char **str);

void	cleanup_tree(t_instruction *root);

#endif
