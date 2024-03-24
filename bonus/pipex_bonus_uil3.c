/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_uil3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 21:21:19 by ahamdi            #+#    #+#             */
/*   Updated: 2024/03/24 21:48:03 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	wit_process(int argc, pid_t *pids, int *fd)
{
	int	j;

	j = 0;
	while (j < argc - 2)
	{
		waitpid(*pids, NULL, 0);
		pids++;
		j++;
	}
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
	exit(EXIT_FAILURE);
}
