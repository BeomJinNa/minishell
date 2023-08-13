#include <stdio.h>
#include <readline/readline.h>
#include "hash.h"
#include "libft.h"
#include "terminal_parser.h"

int	execute_commands(t_command *commands, int size);

int	main(void)
{
	t_command	command;
	const int	cmd_size = 1;
	const int	redir_size = 0;
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
		command.command[idx] = readline("cmd (size = 3): ");
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
				= readline("inner redirection (size = 3): ");
			++inner_idx;
		}
		++idx;
	}
	if (execute_commands(&command, cmd_size))
		printf("Error\n");
	return (0);
}
