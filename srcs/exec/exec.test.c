#include <stdio.h>
#include <readline/readline.h>
#include "hash.h"
#include "libft.h"
#include "terminal_parser.h"

int	execute_commands(t_command *commands, int size);

void	free_commands(t_command *commands, int size)
{
	for(int i = 0; i < size; ++i)
	{
		// free command
		for (int c = 0; commands[i].command[c] != NULL; ++c)
			free(commands[i].command[c]);
		free(commands[i].command);
		// free redirections
		for (int r = 0; commands[i].redirections[r] != NULL; ++r)
		{
			for (int t = 0; commands[i].redirections[r][t] != NULL; ++t)
				free(commands[i].redirections[r][t]);
			free(commands[i].redirections[r]);
		}
		free(commands[i].redirections);
	}
	free(commands);
}

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
	int cmd_cnt;
	printf("cmd_cnt: ");
	scanf("%d", &cmd_cnt);
	t_command	*commands = malloc(sizeof(t_command) * cmd_cnt);
	for(int i = 0; i < cmd_cnt; ++i)
	{
		// read command
		char *line = readline("cmd: ");
		commands[i].command = ft_split(line, ' ');
		free(line);
		int t = 0;
		while (1)
		{
			printf("%s ", commands[i].command[t]);
			if (commands[i].command[t] == NULL)
			{
				printf("\n");
				break;
			}
			t++;
		}
		// read redirections
		int	redir_cnt;
		printf("redir cnt: ");
		scanf("%d", &redir_cnt);
		commands[i].redirections = malloc(sizeof(char **) * (redir_cnt + 1));
		commands[i].redirections[redir_cnt] = NULL;
		for (int r = 0; r < redir_cnt; ++r)
		{
			line = readline("inner redirection: ");
			commands[i].redirections[r] = ft_split(line, ' ');
			t = 0;
			while (1)
			{
				printf("%s ", commands[i].redirections[r][t]);
				if (commands[i].redirections[r][t] == NULL)
				{
					printf("\n");
					break;
				}
				t++;
			}
			free(line);
		}
	}

	get_hashtable(1);
	printf("[Execute commands]\n");
	if (execute_commands(commands, cmd_cnt))
		printf("Error\n");
	free_commands(commands, cmd_cnt);
	remove_hashtable(get_hashtable(0));
	return (0);
}
