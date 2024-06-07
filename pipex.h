/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 21:33:32 by tclaereb          #+#    #+#             */
/*   Updated: 2024/06/07 19:28:52 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>

void	raise_perror(char *error);
void	raise_error(char *error, char *details);
char	*find_path(char **cmd, char **envp);
void	first_fork(char **argv, char **envp, int fd[2]);
void	middle_fork(char **envp, char *argv, int old_fd[2], int new_fd[2]);
void	last_fork(char **argv, char **envp, int old_fd[2]);

#endif
