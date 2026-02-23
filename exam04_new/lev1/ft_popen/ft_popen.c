#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

void	read_case(const char *file, char *const av[], int (*pipe_fd)[2], int *fd, pid_t pid)
{
	if (pid == 0)
	{
		close((*pipe_fd)[0]);
		dup2((*pipe_fd)[1], STDOUT_FILENO);
		close((*pipe_fd)[1]);
		if (execvp(file, av) == -1)
			exit(-1);
	}
	else
	{
		close((*pipe_fd)[1]);
		*fd = *pipe_fd[0];
	}
}


void	write_case(const char *file, char *const av[], int (*pipe_fd)[2], int *fd, pid_t pid)
{
	if (pid == 0)
	{
		close((*pipe_fd)[1]);
		dup2((*pipe_fd)[0], STDIN_FILENO);
		close((*pipe_fd)[0]);
		if (execvp(file, av) == -1)
			exit(-1);
	}
	else
	{
		close((*pipe_fd)[0]);
		*fd = *pipe_fd[1];
	}
}

int	ft_popen(const char *file, char *const av[], char type)
{
	if (!file || !av || !*av || !(type == 'r' || type == 'w'))
		return (-1);
	int	pipe_fd[2];
	pid_t	pid;
	int	fd = -1;

	if (pipe(pipe_fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	if (type == 'r')
		read_case(file, av, &pipe_fd, &fd, pid);
	else
		write_case(file, av, &pipe_fd, &fd, pid);
	return (fd);
}

/*
#include <stdio.h>
#include <sys/wait.h>

int	main()
{
	char	buff[1024];
	int	fd;
	int	n;

	printf("Test1: echo\n");
	char	*test1[] = {"echo", "Hi from popen!", NULL};
	fd = ft_popen("echo", test1, 'r');
	if (fd != -1)
	{	
		while ((n = read(fd, buff, sizeof(buff) - 1)) > 0)
		{
			buff[n] = '\0';
			printf("%s", buff);
		}
		close(fd);
		wait(NULL);
	}
	else
		printf("Error\n");
}*/

