/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 21:28:08 by tclaereb          #+#    #+#             */
/*   Updated: 2024/06/06 21:48:56 by tclaereb         ###   ########.fr       */
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
	printf("%s: %s\n", error, details);
	exit(1);
}

char	*find_path(char **cmd, char **envp)
{
	char	*partial_path;
	char	*full_path;

	while (ft_strncmp(*envp, "PATH=", 5) != 0)
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

void	fork_work(char **argv, char **envp)
{
	int		fd;
	int		fd2;
	int		pfd[2];
	char	**cmd;
	char	*cmd_path;

	fd = open(argv[0], O_RDONLY);
	if (fd == -1)
		raise_perror("File open failed:");
	if (pipe(pfd) == -1)
		raise_perror("Pipe creation failed");
	if (dup2(fd, 0) == -1)
		raise_perror("Dup2 failed");
	cmd = ft_split(argv[1], ' ');
	cmd_path = find_path(cmd, envp);
	if (!cmd_path)
		raise_error("Command not found", argv[1]);
	fd2 = open(argv[3], O_WRONLY);
	dup2(fd2, 1);
	execve(cmd_path, cmd, envp);
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;

	if (argc < 5)
	{
		ft_printf("Minimum 4 arguments are required.");
		return (1);
	}
	argv++;
	pid = fork();
	if (pid < 0)
	{
		perror("Fork failed");
		exit(1);
	}
	if (pid == 0)
		fork_work(argv, envp);
	return (0);
}
