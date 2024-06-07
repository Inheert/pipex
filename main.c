/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 21:28:08 by tclaereb          #+#    #+#             */
/*   Updated: 2024/06/07 19:43:45 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	main(int argc, char **argv, char **envp)
{
	int		(*fd)[2];

	if (argc < 5)
	{
		ft_printf("Minimum 4 arguments are required.");
		return (1);
	}
	argv++;
	fd = malloc((argc - 2) * sizeof(int [2]));
	if (!fd)
		raise_error("malloc error", "(*fd)[2] NULL");
	manage_forks(argc, argv, envp, fd);
	free(fd);
	return (0);
}

// void	fork_work(char **argv, char **envp)
// {
// 	int		fd;
// 	int		fd2;
// 	char	**cmd;
// 	char	*cmd_path;

// 	fd = open(argv[0], O_RDONLY);
// 	if (fd == -1)
// 		raise_perror("File open failed:");
// 	if (dup2(fd, 0) == -1)
// 		return (close(fd), raise_perror("Dup2 failed"));
// 	cmd = ft_split(argv[1], ' ');
// 	cmd_path = find_path(cmd, envp);
// 	if (!cmd_path)
// 		return (close(fd), raise_error("Command not found", argv[1]));
// 	fd2 = open(argv[3], O_WRONLY);
// 	dup2(fd2, 1);
// 	execve(cmd_path, cmd, envp);
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	pid_t	pid;

// 	if (argc < 5)
// 	{
// 		ft_printf("Minimum 4 arguments are required.");
// 		return (1);
// 	}
// 	argv++;
// 	pid = fork();
// 	if (pid < 0)
// 	{
// 		perror("Fork failed");
// 		exit(1);
// 	}
// 	if (pid == 0)
// 		fork_work(argv, envp);
// 	return (0);
// }
