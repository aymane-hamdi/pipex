/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fontion_herdoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:24:49 by ahamdi            #+#    #+#             */
/*   Updated: 2024/03/27 00:51:27 by ahamdi           ###   ########.fr       */
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
			if (!str
				||!ft_strncmp(ft_strjoin(argv[i], "\n"), str, ft_strlen(str)))
				break ;
			ft_putstr_fd(str, fd[1]);
			free(str);
		}
		free(str);
	}
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	if (argv[i][0] == '/' && i != 2)
		commad_path(argv[i], envp);
	else if (argv[i][0] == '.' && (argv[i][1] == '/' && i != 2))
		run_script(argv[i], envp);
	else if (i != 2)
		execute(argv[i], envp);
	else
		exit(0);
}

void	parent_process_her_doc(int argc, char **argv, char **envp)
{
	int		fileout;

	fileout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fileout == -1)
	{
		perror("Error in open file");
		exit(2);
	}
	dup2(fileout, STDOUT_FILENO);
	if (argv[argc - 2][0] == '/')
		commad_path(argv[argc - 2], envp);
	else if (argv[argc - 2][0] == '.' && argv[argc - 2][1] == '/')
		run_script(argv[argc - 2], envp);
	else
		execute(argv[argc - 2], envp);
}

void	lop_her_doc(int argc, char **argv, char **envp, int *fd)
{
	int		i;
	pid_t	pid1;
	pid_t	*pids;

	pids = (pid_t *)malloc((argc - 3) * sizeof(pid_t));
	if (!pids)
		exit(1);
	i = 2;
	while (i <= argc - 2)
	{
		filecommade(argv, envp, argc);
		if (pipe(fd) == -1)
			erro();
		pid1 = fork();
		if (pid1 == -1)
			erro();
		if (pid1 == 0 && i != argc - 2)
			child_process_her_doc(argv, envp, fd, i);
		else if (pid1 == 0 && i == argc - 2)
			parent_process_her_doc(argc, argv, envp);
		whilloop(fd);
		i++;
	}
	wit_process(argc, &pids, fd);
}

void	malloc_erro(int *str)
{
	if (!str)
		exit(1);
}
