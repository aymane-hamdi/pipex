/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util3_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 21:21:19 by ahamdi            #+#    #+#             */
/*   Updated: 2024/03/29 16:46:40 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	wit_process(int argc, pid_t **pids, int *fd)
{
	int	j;

	j = 0;
	while (j < argc - 2)
	{
		waitpid((*pids)[j], NULL, 0);
		j++;
	}
	free(*pids);
	close(fd[0]);
	close(fd[1]);
}

void	whilloop(int *fd)
{
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);
}

void	erro(void)
{
	perror("Error in pipe or process");
	exit(3);
}

void	errer_cmd(void)
{
	perror("invalide command");
	exit(127);
}

void	filecommade(char **argv, char **envp, int argc)
{
	if (argv[argc - 2][0] == '\0')
		errer_cmd();
	if (argv[argc - 2][0] == '/')
	{
		if (access(argv[argc - 2], X_OK) != 0)
			errer_cmd();
	}
	if (argv[argc - 2][0] == '.' && argv[argc - 2][1] == '/')
	{
		if (access(argv[argc - 2], X_OK) != 0)
			errer_cmd();
	}
}
