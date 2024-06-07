/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:25:37 by tclaereb          #+#    #+#             */
/*   Updated: 2024/06/07 20:05:03 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	raise_perror(char *error)
{
	perror(error);
	exit(1);
}

void	raise_error(char *error, char *details)
{
	ft_printf("%s: %s\n", error, details);
	exit(1);
}

char	*find_path(char **cmd, char **envp)
{
	char	*partial_path;
	char	*full_path;

	while (envp && ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	envp = ft_split(*envp, ':');
	while (*envp)
	{
		partial_path = ft_strjoin(*envp, "/");
		full_path = ft_strjoin(partial_path, cmd[0]);
		free(partial_path);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		envp++;
	}
	return (NULL);
}

void	close_fd(int i, int (*fd)[2])
{
	if (i > 0)
	{
		close(fd[i - 1][0]);
		close(fd[i - 1][1]);
	}
}

void	manage_forks(int argc, char **argv, char **envp, int (*fd)[2])
{
	pid_t	pid;
	int		i;

	i = 0;
	while (i < argc - 3)
	{
		if (pipe(fd[i]) == -1)
			return (free(fd), raise_perror("Pipe creation failed"));
		pid = fork();
		if (pid == 0)
		{
			if (i == 0)
				first_fork(argv, envp, fd[i]);
			else if (i == argc - 4)
				last_fork(argv + i + 1, envp, fd[i - 1]);
			else
				middle_fork(envp, argv[i + 1], fd[i - 1], fd[i]);
			exit(0);
		}
		close_fd(i, fd);
		waitpid(pid, NULL, 0);
		i++;
	}
}
