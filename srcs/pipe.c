#include "../incs/minishell.h"

int spawn_proc (int in, int out,char ***av, char  **env)
{
	pid_t pid;

	if ((pid = fork ()) == 0)
	{
		if (in != 0)
		{
			dup2 (in, 0);
			close (in);
		}
		if (out != 1)
		{
			dup2 (out, 1);
			close (out);
		}
		return execve (*av[0],*av, env);
	}
	return (1);
}

int fork_pipes (int n, char ***av, char **env)
{
	int i;
	pid_t pid;
	int in; 
	int fd [2];

	in = 0;
	i = 0;
	while (i < n)
	{
		pipe (fd);
		if (spawn_proc (in, fd [1], av + i, env) < 0)
			return (-1);
		/* the child will write here.  */

		close (fd [1]);

      /* the next child will read from there.  */
		in = fd [0];
		i++;
	}
	if (in != 0)
		dup2 (in, 0);
	return execve (av[i][0],av[i],NULL);
}
