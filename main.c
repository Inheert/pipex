/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 21:28:08 by tclaereb          #+#    #+#             */
/*   Updated: 2024/06/18 19:02:18 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*check_path(char **cmd, char **envp, int i)
{
	char	*partial_path;
	char	*full_path;

	partial_path = ft_strjoin(envp[i], "/");
	if (!partial_path)
		return (free_split(envp), free_split(cmd),
			raise_error("Strjoin failed", "partial_path", 1), NULL);
	full_path = ft_strjoin(partial_path, cmd[0]);
	if (!full_path)
		return (free(partial_path), free_split(envp), free_split(cmd),
			raise_error("Strjoin failed", "partial_path", 1), NULL);
	free(partial_path);
	if (access(full_path, X_OK) == 0 || access(full_path, F_OK) == 0)
		return (free_split(envp), full_path);
	free(full_path);
	return (NULL);
}

int	create_fork(int argc, int i, int (*fd)[2], pid_t *pid)
{
	if (i < argc - 4)
		if (pipe(fd[i]) == -1)
			return (free(fd), raise_perror("Pipe creation failed"), 1);
	pid[i] = fork();
	if (pid[i] < 0)
		return (free(pid), free(fd), 1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int		(*fd)[2];
	int		status;

	if (argc < 5)
	{
		ft_printf("Minimum 4 arguments are required.");
		return (1);
	}
	argv++;
	fd = malloc((argc - 2) * sizeof(int [2]));
	if (!fd)
		raise_error("malloc error", "(*fd)[2] NULL", 1);
	status = manage_forks(argc, argv, envp, fd);
	envp++;
	free(fd);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}
