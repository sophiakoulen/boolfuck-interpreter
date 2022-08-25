#include <stdlib.h>
#include <stdio.h>

typedef struct s_instruction
{
	char			val;
	struct s_instruction	*right;
	struct s_instruction	*left;
	struct s_instruction	*parent;
} t_instruction;

void	append_node(t_instruction *node, t_instruction **next)
{
	*next = malloc(sizeof(t_instruction));
	(*next)->parent = node;
	(*next)->right = 0;
	(*next)->left = 0;
}

void	parse(t_instruction *root, char **str)
{
	t_instruction	*current;

	current = root;
	while (**str)
	{
		if (**str == '[')
		{
			current->val = '[';

			append_node(current, &(current->left));
			append_node(current, &(current->right));

			(*str)++;
			parse(current->left, str);
		}
		else if (**str == ']')
		{
			current = current->parent;
			free(current->right);
			current->right = root->parent;

			(*str)++;
			return ;
		}
		else if (**str == ',' || **str == ';' || **str == '+' || **str == '>' || **str == '<')
		{
			current->val = **str;

			append_node(current, &(current->right));

			(*str)++;
		}
		else
		{
			(*str)++;
		}
		current = current->right;
	}
}

void	cleanup_tree(t_instruction *root)
{
	if (!root)
		return ;
	if (root->val == '[')
	{
		root->val = ']';
		cleanup_tree(root->left);
	}
	else
	{
		cleanup_tree(root->right);
		free(root);
	}
}
/*
int main(int argc, char **argv)
{
	char *str = argv[1];
	t_instruction *root = malloc(sizeof(t_instruction));
	parse(root, &str);
	cleanup_tree(root);
	return 0;
}
*/
