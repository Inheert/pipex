/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:25:37 by tclaereb          #+#    #+#             */
/*   Updated: 2024/06/11 18:40:33 by tclaereb         ###   ########.fr       */
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
	write(2, error, ft_strlen(error));
	write(2, ": ", 2);
	write(2, details, ft_strlen(details));
	write(2, "\n", 1);
	exit(1);
}

char	*find_path(char **cmd, char **envp)
{
	char	*partial_path;
	char	*full_path;
	int		i;

	if (access(cmd[0], X_OK) == 0)
		return (cmd[0]);
	while (envp && ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	envp = ft_split(*envp, ':');
	if (!envp)
		return (NULL);
	envp[0] = ft_substr(envp[0], 5, ft_strlen(envp[0]));
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
