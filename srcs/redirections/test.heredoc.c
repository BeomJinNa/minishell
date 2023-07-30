#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int	heredoc(char *filename, int *fd, char *delimiter);

void	set_exit_status(int exit_status)
{
	printf("exit_status Set to %d\n", exit_status);
}

int	main(void)
{
	int	fd;
	int	result;

	result = heredoc("tmp_heredoc", &fd, "end");
	return (0);
}
