#include <stdlib.h>
#include <stdio.h>

typedef struct s_instruction
{
	char					val;
	struct s_instruction	*right;
	struct s_instruction	*left;
} t_instruction;

t_instruction	*factory(char val)
{
	t_instruction	*node;

	node = malloc(sizeof(t_instruction));
	node->val = val;
	node->left = 0;
	node->right = 0;
	return (node);
}

void	parse(t_instruction **root, t_instruction *parent, char **str)
{
	t_instruction	**current;

	current = root;
	while (**str)
	{
		if (**str == '[')
		{
			*current = factory(**str);
			(*str)++;
			parse(&(*current)->left, *current, str);
			current = &(*current)->right;
		}
		else if (**str == ']')
		{
			*current = parent;
			return ;
		}
		else if (**str == ',' || **str == ';' || **str == '+' || **str == '>' || **str == '<')
		{
			*current = factory(**str);
			current = &(*current)->right;
		}
		(*str)++;
	}
}

void	free_tree(t_instruction *root)
{
	if (!root)
		return ;
	if (root->val == '[')
	{
		root->val = ']';
		free_tree(root->left);
	}
	else
	{
		free_tree(root->right);
		free(root);
	}
}
/*
int main(int argc, char **argv)
{
	char *str = argv[1];
	t_instruction *root = 0;
	parse(&root, 0, &str);
	free_tree(root);
	return 0;
}
*/
