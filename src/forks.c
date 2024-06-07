/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:27:16 by tclaereb          #+#    #+#             */
/*   Updated: 2024/06/07 20:04:53 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_fork(char **argv, char **envp, int fd[2])
{
	int		ffd;
	char	**cmd;
	char	*cmd_path;

	ffd = open(argv[0], O_RDONLY);
	if (ffd == -1)
		raise_perror("File open failed");
	if (dup2(ffd, 0) == -1)
		return (close(ffd), raise_perror("dup2 failed"));
	close(ffd);
	if (dup2(fd[1], 1) == -1)
		return (raise_perror("dup2 failed"));
	close(fd[0]);
	close(fd[1]);
	cmd = ft_split(argv[1], ' ');
	cmd_path = find_path(cmd, envp);
	if (!cmd_path)
		return (free(cmd), raise_error("Command not found", argv[1]));
	execve(cmd_path, cmd, envp);
	raise_perror("execve error");
}

void	middle_fork(char **envp, char *argv, int old_fd[2], int new_fd[2])
{
	char	**cmd;
	char	*cmd_path;

	if (dup2(old_fd[0], 0) == -1)
		return (close(old_fd[0]), close(old_fd[1]), close(new_fd[0]),
			close(new_fd[1]), raise_perror("dup2 failed"));
	if (dup2(new_fd[1], 1) == -1)
		return (close(old_fd[0]), close(old_fd[1]), close(new_fd[0]),
			close(new_fd[1]), raise_perror("dup2 failed"));
	close(old_fd[0]);
	close(old_fd[1]);
	close(new_fd[0]);
	close(new_fd[1]);
	cmd = ft_split(argv, ' ');
	cmd_path = find_path(cmd, envp);
	if (!cmd_path)
		return (free(cmd), raise_error("Command not found", argv));
	execve(cmd_path, cmd, envp);
}

void	last_fork(char **argv, char **envp, int old_fd[2])
{
	int		fd;
	char	**cmd;
	char	*cmd_path;

	if (dup2(old_fd[0], 0) == -1)
		return (close(old_fd[0]), close(old_fd[1]),
			raise_perror("dup2 failed"));
	close(old_fd[0]);
	close(old_fd[1]);
	fd = open(argv[1], O_WRONLY);
	if (fd == -1)
		raise_perror("File open failed");
	if (dup2(fd, 1) == -1)
		raise_perror("dup2 failed");
	close(fd);
	cmd = ft_split(argv[0], ' ');
	cmd_path = find_path(cmd, envp);
	if (!cmd_path)
		return (free(cmd), raise_error("Command not found", argv[1]));
	execve(cmd_path, cmd, envp);
}
