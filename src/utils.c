/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:25:37 by tclaereb          #+#    #+#             */
/*   Updated: 2024/06/07 19:28:44 by tclaereb         ###   ########.fr       */
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
