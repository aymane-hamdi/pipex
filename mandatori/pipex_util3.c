/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 16:45:21 by ahamdi            #+#    #+#             */
/*   Updated: 2024/03/24 23:02:07 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	erro(void)
{
	perror("Error in pipe or process");
	exit(EXIT_FAILURE);
}

int	ft_count_words(char const *str, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		while (str[i] == sep)
			i++;
		if (str[i] != '\0')
			count++;
		while (str[i] && str[i] != sep)
			i++;
	}
	return (count);
}

void	wit_process(int *fd, int pid, int pid1)
{
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid1, NULL, 0);
}
