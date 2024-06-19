/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:25:37 by tclaereb          #+#    #+#             */
/*   Updated: 2024/06/19 13:26:08 by tclaereb         ###   ########.fr       */
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

int	ft_wait_pid(pid_t *pid)
{
	int	i;
	int	status;

	if (!pid)
		return (1);
	i = 0;
	while (pid[i])
	{
		if (waitpid(pid[i], &status, 0) == -1)
			raise_perror("wait pid failed");
		i++;
	}
	free(pid);
	return (status);
}

char	*check_path(char **cmd, char **envp)
{
	int		i;
	char	*partial_path;
	char	*full_path;

	i = -1;
	while (envp[++i])
	{
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
	}
	free_split(envp);
	return (NULL);
}

char	*find_path(char **cmd, char **envp)
{
	if (!envp || !*envp)
		return (raise_error("envp error", "envp is missing or NULL", 1), NULL);
	if (access(cmd[0], X_OK) == 0)
		return (cmd[0]);
	else if (access(cmd[0], F_OK) == 0 && cmd[0][0] == '.')
		return (free_split(cmd), raise_error("Permission denied",
				"command can be executed", 126), NULL);
	while (envp && ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	envp = ft_split(*envp, ':');
	if (!envp)
		return (free_split(cmd), NULL);
	*envp = ft_substr(*envp, 5, ft_strlen(*envp));
	if (!envp)
		return (free_split(cmd), NULL);
	return (check_path(cmd, envp));
}
