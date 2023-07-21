#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libft.h>

void	execute(char **redirections, char ***exec_list, size_t exec_cnt);

void	ft_leaks()
{
	system("leaks a.out");
}

int main()
{
	atexit(ft_leaks);
	char **redirections = malloc(sizeof(char *) * 2);
	redirections[0] = strdup(">input");
	redirections[1] = NULL;
	char ***exec_list = malloc(sizeof(char **) * 5);
	exec_list[0] = ft_split("cat", ' ');
	exec_list[1] = ft_split("cat", ' ');
	exec_list[2] = ft_split("cat", ' ');
	exec_list[3] = ft_split("cat", ' ');
	exec_list[4] = NULL;
	execute(redirections, exec_list, 4);
	free(exec_list[0]);
	free(exec_list[0][0]);
	free(exec_list[1]);
	free(exec_list[1][0]);
	free(exec_list[2]);
	free(exec_list[2][0]);
	free(exec_list[3]);
	free(exec_list[3][0]);
	free(exec_list[4]);
	free(exec_list);
	free(redirections[0]);
	free(redirections);
	return 0;
}