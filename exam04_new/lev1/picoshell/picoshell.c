#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void	exec_child(char **cmd, int (*pipe_fd)[2], int *prev, char **next)
{
	if (*prev != -1)
	{
		dup2(*prev, STDIN_FILENO);
		close(*prev);
	}
	if (next != NULL)
		dup2((*pipe_fd)[1], STDOUT_FILENO);
	close((*pipe_fd)[0]);
	close((*pipe_fd)[1]);
	if (execvp(cmd[0], cmd) == -1)
		exit(1);
}

int	picoshell(char ***cmds)
{
	if (!cmds || !*cmds || !**cmds)
		return (1);
	int	pipe_fd[2];
	pid_t	pid;
	int	stat;
	int	prev = -1;
	int	last = 0;
	int	i = 0;

	while (cmds[i])
	{
		if (cmds[i + 1] != NULL)
		{
			if (pipe(pipe_fd) == -1)
				return (1);
		}
		pid = fork();
		if (pid == -1)
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			return (1);
		}
		if (pid == 0)
			exec_child(cmds[i], &pipe_fd, &prev, cmds[i + 1]);
		if (cmds[i + 1] != NULL)
		{
			close(pipe_fd[1]);
			prev = pipe_fd[0];
		}
		i ++;
	}
	while (wait(&stat) > 0)
	{
		if (WIFEXITED(stat) && WEXITSTATUS(stat) != 0)
			last = WEXITSTATUS(stat);
	}
	return (last);
}

#include <stdio.h>

int	main()
{
	char	*cmd1[] = {"ls", "-la", NULL};
	char	*cmd2[] = {"echo", "ciao!", NULL};
	char	*cmd3[] = {"whoami", NULL};
	char	*cmd4[] = {"booh", NULL};
	char	*cmd5[] = {"grep", "picoshell", NULL};

	char	**test1[] = {cmd1, cmd5, NULL};
	char	**test2[] = {cmd2, cmd3, NULL};
	char	**test3[] = {cmd2, NULL};
	char	**test4[] = {cmd4, NULL};

	printf("Test1: ls -la | grep picoshell\n");
	printf("Exit code: %d\n", picoshell(test1));
	printf("Test2: echo ciao | whoami\n");
	printf("Exit code: %d\n", picoshell(test2));
	printf("Test3: echo ciao\n");
	printf("Exit code: %d\n", picoshell(test3));
	printf("Test4: booh\n");
	printf("Exit code: %d\n", picoshell(test4));
}

