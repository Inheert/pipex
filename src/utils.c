/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:25:37 by tclaereb          #+#    #+#             */
/*   Updated: 2024/06/07 20:20:24 by tclaereb         ###   ########.fr       */
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
	int		i;

	while (envp && ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	envp = ft_split(*envp, ':');
	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		partial_path = ft_strjoin(envp[i], "/");
		full_path = ft_strjoin(partial_path, cmd[0]);
		free(partial_path);
		if (access(full_path, X_OK) == 0)
			return (free_split(envp), full_path);
		free(full_path);
		i++;
	}
	free_split(envp);
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

void	free_split(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}
