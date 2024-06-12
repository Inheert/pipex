/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 21:28:08 by tclaereb          #+#    #+#             */
/*   Updated: 2024/06/12 13:47:01 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	(*fd)[2];
	int	status;

	if (argc < 5)
	{
		ft_printf("Minimum 4 arguments are required.");
		return (1);
	}
	argv++;
	fd = malloc((argc - 2) * sizeof(int [2]));
	if (!fd)
		raise_error("malloc error", "(*fd)[2] NULL");
	status = manage_forks(argc, argv, envp, fd);
	free(fd);
	ft_printf("Status code: %d\n", WEXITSTATUS(status));
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}
