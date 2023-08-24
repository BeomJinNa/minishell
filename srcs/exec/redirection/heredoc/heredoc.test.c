#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <term.h>
#include "libft.h"
#include "heredoc.h"

int	main(void)
{
	int	fd;
	int	result;
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	result = heredoc("/tmp/tmp_heredoc", "end");
	// print all lines in fd.
	if (result)
	{
	}
	else
	{
		fd = open("/tmp/tmp_heredoc", O_RDONLY);
		while (1)
		{
			char	*line;

			line = get_next_line(fd);
			if (!line)
				break ;
			printf("%s", line);
			free(line);
		}
		close(fd);
	}
	unlink("/tmp/tmp_heredoc");
	return (0);
}
