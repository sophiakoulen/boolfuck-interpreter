#include "parse.h"
#include "memory.h"
#include "exec.h"
#include <stdlib.h>
#include <stdio.h>

char* boolfuck (char *code, char *in)
{
	t_tape			i, o; //input and output
	t_memory		m;
	t_instruction	*root, *current; //for executing instructions
	char			*reverse_input;
	char			*reverse_output;

	reverse_input = change_endianness(in);
	init_tape(&i, reverse_input);
	init_tape(&o, 0);
	init_memory(&m);

	parse(&root, 0, &code);
	current = root;
	while (current)
	{
		if (current->val == '+')
		{
			flip(select_tape(&m));
		}
		else if (current->val == '>')
		{
			mem_right(&m);
		}
		else if (current->val == '<')
		{
			mem_left(&m);
		}
		else if (current->val == ';')
		{
			output(&m, &o);
		}
		else if (current->val == ',')
		{
			input(&m, &i);
		}
		else if (current->val == '[')
		{
			if (!is_zero(*select_tape(&m)))
			{
				current = current->left;
				continue;
			}
		}
		current = current->right;
	}
	reverse_output = change_endianness(o.data);
	free_tree(root);
	free_tape(&i);
	free_tape(&o);
	free_memory(&m);
	free(reverse_input);
	return (reverse_output);
}

int main(int argc, char **argv)
{
	char code[] = ">,>,>,>,>,>,>,>,<<<<<<<[>]+<[+<]>>>>>>>>>[+]+<<<<<<<<+[>+]<[<]>>>>>>>>>[+<<<<<<<<[>]+<[+<]>>>>>>>>>+<<<<<<<<+[>+]<[<]>>>>>>>>>[+]<<<<<<<<;>;>;>;>;>;>;>;<<<<<<<,>,>,>,>,>,>,>,<<<<<<<[>]+<[+<]>>>>>>>>>[+]+<<<<<<<<+[>+]<[<]>>>>>>>>>]<[+<]";
	//char code[] = ">,>,>,>,>,>,>,>,>+<<<<<<<<+[>+]<[<]>>>>>>>>>[+<<<<<<<<[>]+<[+<]>;>;>;>;>;>;>;>;>+<<<<<<<<+[>+]<[<]>>>>>>>>>[+<<<<<<<<[>]+<[+<]>>>>>>>>>+<<<<<<<<+[>+]<[<]>>>>>>>>>[+]+<<<<<<<<+[>+]<[<]>>>>>>>>>]<[+<]>,>,>,>,>,>,>,>,>+<<<<<<<<+[>+]<[<]>>>>>>>>>]<[+<]";
	//char code[] = ">,>,>,>,>,>,>,>,>>,>,>,>,>,>,>,>,<<<<<<<<+<<<<<<<<+[>+]<[<]>>>>>>>>>[+<<<<<<<<[>]+<[+<]>>>>>>>>>>>>>>>>>>+<<<<<<<<+[>+]<[<]>>>>>>>>>[+<<<<<<<<[>]+<[+<]>>>>>>>>>+<<<<<<<<+[>+]<[<]>>>>>>>>>[+]>[>]+<[+<]>>>>>>>>>[+]>[>]+<[+<]>>>>>>>>>[+]<<<<<<<<<<<<<<<<<<+<<<<<<<<+[>+]<[<]>>>>>>>>>]<[+<]>>>>>>>>>>>>>>>>>>>>>>>>>>>+<<<<<<<<+[>+]<[<]>>>>>>>>>[+<<<<<<<<[>]+<[+<]>>>>>>>>>+<<<<<<<<+[>+]<[<]>>>>>>>>>[+]<<<<<<<<<<<<<<<<<<<<<<<<<<[>]+<[+<]>>>>>>>>>[+]>>>>>>>>>>>>>>>>>>+<<<<<<<<+[>+]<[<]>>>>>>>>>]<[+<]<<<<<<<<<<<<<<<<<<+<<<<<<<<+[>+]<[<]>>>>>>>>>[+]+<<<<<<<<+[>+]<[<]>>>>>>>>>]<[+<]>>>>>>>>>>>>>>>>>>>;>;>;>;>;>;>;>;<<<<<<<<";
	//char code[] = ";;;+;+;;+;+;\
+;+;+;+;;+;;+;\
;;+;;+;+;;+;\
;;+;;+;+;;+;\
+;;;;+;+;;+;\
;;+;;+;+;+;;\
;;;;;+;+;;\
+;;;+;+;;;+;\
+;;;;+;+;;+;\
;+;+;;+;;;+;\
;;+;;+;+;;+;\
;;+;+;;+;;+;\
+;+;;;;+;+;;\
;+;+;+;";
	char in[] = "Codewars\xff";
	//char in[] = "Codewars";
	//char in[] = "\x08\x09";
	//char in[] = "";
	char *output;
	if (argc == 3)
		output = boolfuck(argv[1], argv[2]);
	else
		output = boolfuck(code, in);
	printf("%s\n", output);
	free(output);
	return 0;
}
