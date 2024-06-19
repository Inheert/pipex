/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 21:33:32 by tclaereb          #+#    #+#             */
/*   Updated: 2024/06/19 13:20:16 by tclaereb         ###   ########.fr       */
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
# include <errno.h>

void	raise_perror(char *error);
void	raise_error(char *error, char *details, int exit_code);
char	*find_path(char **cmd, char **envp);
char	*check_path(char **cmd, char **envp);
void	free_split(char **ptr);
void	close_fd(int i, int (*fd)[2]);
int		create_fork(int argc, int i, int (*fd)[2], pid_t *pid);
int		manage_forks(int argc, char **argv, char **envp, int (*fd)[2]);

#endif
