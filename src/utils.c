/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:25:37 by tclaereb          #+#    #+#             */
/*   Updated: 2024/06/18 19:11:27 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	raise_perror(char *error)
{
	perror(error);
	exit(errno);
}

void	raise_error(char *error, char *details, int exit_code)
{
	write(2, error, ft_strlen(error));
	write(2, ": ", 2);
	write(2, details, ft_strlen(details));
	write(2, "\n", 1);
	exit(exit_code);
}

char	*find_path(char **cmd, char **envp)
{
	char	*full_path;
	int		i;

	if (!envp || !*envp)
		return (raise_error("envp error", "envp is missing or NULL", 1), NULL);
	if (access(cmd[0], X_OK) == 0)
		return (cmd[0]);
	else if (access(cmd[0], F_OK) == 0 && cmd[0][0] == '.')
		return (free_split(cmd), raise_error("Permission denied",
			"command can be executed", 126), NULL);
	while (envp && ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	envp = ft_split(*envp + 5, ':');
	if (!envp)
		return (NULL);
	i = -1;
	while (envp[++i])
	{
		full_path = check_path(cmd, envp, i);
		if (full_path)
			return (full_path);
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
