/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:27:16 by tclaereb          #+#    #+#             */
/*   Updated: 2024/06/19 13:25:59 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_fork(char **argv, char **envp, int (*fd)[2], int i)
{
	int		infile;
	char	**cmd;
	char	*cmd_path;

	infile = open(argv[0], O_RDONLY);
	if (infile == -1)
		return (close(fd[i][0]), close(fd[i][1]), free(fd),
			raise_perror("File open failed"));
	if (dup2(infile, 0) == -1)
		return (close(infile), free(fd), raise_perror("dup2 failed"));
	close(infile);
	if (dup2(fd[i][1], 1) == -1)
		return (free(fd), free(fd), raise_perror("dup2 failed"));
	close(fd[i][0]);
	close(fd[i][1]);
	free(fd);
	cmd = ft_split(argv[1], ' ');
	if (!cmd)
		return (raise_error("Command not found", argv[1], 127));
	cmd_path = find_path(cmd, envp);
	if (!cmd_path)
		return (free_split(cmd), raise_error("Command not found",
				argv[1], 127));
	if (execve(cmd_path, cmd, envp) == -1)
		return (free(cmd), free(cmd_path), raise_perror("execve error"));
}

void	middle_fork(char **envp, char *argv, int (*fd)[2], int i)
{
	char	**cmd;
	char	*cmd_path;

	if (dup2(fd[i - 1][0], 0) == -1)
		return (close(fd[i - 1][0]), close(fd[i - 1][1]), close(fd[i][0]),
			close(fd[i][1]), raise_perror("dup2 failed"));
	if (dup2(fd[i][1], 1) == -1)
		return (close(fd[i - 1][0]), close(fd[i - 1][1]), close(fd[i][0]),
			close(fd[i][1]), raise_perror("dup2 failed"));
	close(fd[i - 1][0]);
	close(fd[i - 1][1]);
	close(fd[i][0]);
	close(fd[i][1]);
	free(fd);
	cmd = ft_split(argv, ' ');
	if (!cmd)
		return (raise_error("malloc error", "char **cmd", 1));
	cmd_path = find_path(cmd, envp);
	if (!cmd_path)
		return (free_split(cmd), raise_error("Command not found", argv, 127));
	if (execve(cmd_path, cmd, envp) == -1)
		return (free(cmd), free(cmd_path), raise_perror("execve error"));
}

void	last_fork(char **argv, char **envp, int (*fd)[2], int i)
{
	int		outfile;
	char	**cmd;
	char	*cmd_path;

	if (dup2(fd[i][0], 0) == -1)
		return (close(fd[i][0]), close(fd[i][1]), free(fd),
			raise_perror("dup2 failed"));
	close(fd[i][0]);
	close(fd[i][1]);
	free(fd);
	outfile = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
		raise_perror("File open failed");
	if (dup2(outfile, 1) == -1)
		raise_perror("dup2 failed");
	close(outfile);
	cmd = ft_split(argv[0], ' ');
	if (!cmd)
		return (raise_error("Command not found", argv[1], 127));
	cmd_path = find_path(cmd, envp);
	if (!cmd_path)
		return (free_split(cmd), raise_error("Command not found",
				argv[0], 127));
	if (execve(cmd_path, cmd, envp) == -1)
		return (free(cmd), free(cmd_path), raise_perror("execve error"));
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

int	manage_forks(int argc, char **argv, char **envp, int (*fd)[2])
{
	pid_t	*pid;
	int		i;

	i = -1;
	pid = malloc(sizeof(int) * argc - 2);
	if (!pid)
		return (1);
	pid[argc - 3] = 0;
	while (++i < argc - 3)
	{
		if (create_fork(argc, i, fd, pid) != 0)
			return (-1);
		if (pid[i] == 0)
		{
			free(pid);
			if (i == 0)
				first_fork(argv, envp, fd, i);
			else if (i == argc - 4)
				last_fork(argv + i + 1, envp, fd, i - 1);
			else
				middle_fork(envp, argv[i + 1], fd, i);
		}
		close_fd(i, fd);
	}
	return (ft_wait_pid(pid));
}
