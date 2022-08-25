#include "parse.h"
#include "memory.h"
#include "exec.h"
#include <stdlib.h>
#include <stdio.h>
char* boolfuck (char *code, char *in)
{
	t_tape		i;
	t_tape		o;
	t_tape		zero;
	t_memory	m;
	t_instruction	*root;

	change_endianness(in);
	init_tape(&i, in);
	init_tape(&o, 0);
	init_tape(&zero, 0);
	init_memory(&m);

	root = malloc(sizeof(t_instruction));
	root->val = '<';
        root->left = 0;
        root->right = 0;
	parse(root, &code);
	t_instruction *current = root;
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
			if (!compare(*select_tape(&m), zero))
			{
				current = current->left;
				continue;
			}
		}
		current = current->right;
	}
	cleanup_tree(root);
	free(zero.data);
	free(m.left.data);
	free(m.right.data);
	free(i.data);
	/*
	int j;
	printf("input:\n");
	for (j = 0; j < i.size; j++)
	       printf(" %c - %d|", i.data[j], i.data[j]);	
	printf("\noutput:\n");
	for (j = 0; j < o.size; j++)
		printf(" %c - %d|", o.data[j], o.data[j]);
	printf("\nleft memory:\n");
	for (j = 0; j < m.left.size; j++)
	       printf(" %c - %d|", m.left.data[j], m.left.data[j]);
	printf("\nright memory:\n");
        for (j = 0; j < m.right.size; j++)
               printf(" %c - %d|", m.right.data[j], m.right.data[j]);
	printf("\n");
	*/
	change_endianness(o.data);	
	return o.data;
}

int main()
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
	char *output = boolfuck("", in);
	printf("%s\n", output);
	free(output);
	return 0;
}
