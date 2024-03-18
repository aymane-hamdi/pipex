/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fontion_herdoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:24:49 by ahamdi            #+#    #+#             */
/*   Updated: 2024/03/18 21:56:14 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	child_process_her_doc(char **argv, char **envp, int *fd, int i)
{
	char	*str;

	if (i == 2)
	{
		while (1)
		{
			str = get_next_line(0);
			if (!str)
			{
				perror("get_next_line failed");
				break ;
			}
			if (!ft_strncmp(argv[i], str, ft_strlen(argv[i])))
				break ;
			ft_putstr_fd(str, fd[1]);
			free(str);
		}
	}
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	if (argv[i][0] == '/')
		cas_special(argv[i], envp);
	else if(argv[i][0]== '.')
		run_script(argv[i], envp);
	else
		execute(argv[i], envp);
}

void	parent_process_her_doc(int argc, char **argv, char **envp)
{
	int		fileout;

	fileout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fileout == -1)
	{
		perror("Error lors de l'ouverture du fichier");
		exit(1);
	}
	if (dup2(fileout, STDOUT_FILENO) == -1)
	{
		perror("Error lors de la duplication du descripteur de fichier");
		exit(1);
	}
	execute(argv[argc - 2], envp);
}

void	lop_her_doc(int argc, char *argv[], char **envp, int *fd)
{
	int		i;
	pid_t	pid1;

	i = 2 ;
	while (i < argc - 2)
	{
		if (pipe(fd) == -1)
		{
			perror("Error l'orsque de creation de pipe");
			exit(1); 
		}
		pid1 = fork();
		if (pid1 == -1)
		{
			perror("Error l'orsque de creation de processus");
			exit(1);
		}
		if (pid1 == 0)
			child_process_her_doc(argv, envp, fd, i);
		waitpid(pid1, NULL, 0);
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		i++;
	}
}
