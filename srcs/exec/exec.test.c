#include <stdio.h>
#include <readline/readline.h>
#include "hash.h"
#include "libft.h"
#include "terminal_parser.h"

int	execute_commands(t_command *commands, int size);

/*
redirection + cmd

<single command>
cat -> read from stdin, out to stdout 
cat < infile -> read from infile, out to stdout
cat > outfile -> read from stdin, out to outfile
cat < infile > outfile -> read from infile, out to outfile
<double command>
cat | cat -> read from stdin, out to stdout
cat < infile | cat -> read from infile, out to stdout
cat | cat > outfile -> read from stdin, out to outfile
cat < infile | cat > outfile -> read from infile, out to outfile
====
cat < infile > outfile | cat -> read from infile, out to outfile, (read from stdin, no input / out to stdout)

ex)
> ./test_exec
cmd: cat
inner redirection: <
inner redirection: infile
*/
int	main(void)
{
	t_command	command;
	const int	cmd_size = 1;
	const int	redir_size = 2;
	int			inner_idx;
	int			idx;

	get_hashtable(1);
	command.command = malloc(sizeof(char *) * (cmd_size + 1));
	command.command[cmd_size] = NULL;
	command.redirections = malloc(sizeof(char **) * (cmd_size + 1));
	command.redirections[cmd_size] = NULL;
	idx = 0;
	while (idx < cmd_size)
	{
		command.command[idx] = readline("cmd: ");
		++idx;
	}
	idx = 0;
	while (idx < cmd_size)
	{
		command.redirections[idx]
			= malloc(sizeof(char *) * (redir_size + 1));
		command.redirections[idx][redir_size] = NULL;
		inner_idx = 0;
		while (inner_idx < redir_size)
		{
			command.redirections[idx][inner_idx]
				= readline("inner redirection: ");
			++inner_idx;
		}
		++idx;
	}
	if (execute_commands(&command, cmd_size))
		printf("Error\n");
	return (0);
}
