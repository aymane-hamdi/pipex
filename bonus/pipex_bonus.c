/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:30:28 by ahamdi            #+#    #+#             */
/*   Updated: 2024/03/24 00:02:33 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	child_process(char **argv, char **envp, int *fd, int i, int filein)
{

	if (i == 2)
	{
		dup2(filein, STDIN_FILENO);
	}
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	if (argv[i][0] == '/')
		cas_special(argv[i], envp);
	else if (argv[i][0] == '.')
		run_script(argv[i], envp);
	else
		execute(argv[i], envp);
}

static void	bad_argument(void)
{
	int		i;
	char	*str;
	char	*s;

	i = 0;
	str = "\tError: Bad argument\n";
	while (str[i] != '\0')
	{
		write(2, &str[i], 1);
		i++;
	}
	i = 0;
	s = "\tEx: ./pipex <file1> <cmd1> <cmd2><file2>\n";
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
	}
}

static void	parent_process(char argc, char **argv, char **envp)
{
	int		fileout;

	fileout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fileout == -1)
	{
		perror("Error l'orsque l'ouverture du fichier");
		exit(1);  
	}
	dup2(fileout, STDOUT_FILENO);
	if (argv[argc - 2][0] == '/')
		cas_special(argv[argc - 2], envp);
	else if (argv[argc - 2][0] == '.')
		run_script(argv[argc - 2], envp);
	else
		execute(argv[argc - 2], envp);
}
void	wit_process(int argc, pid_t *pids, int *fd)
{
	int j = 0;
	while (j < argc - 2)
	{
		waitpid(*pids, NULL, 0);
		pids++;
		j++;
	}
	close(fd[0]);
	close(fd[1]);
}
static void whilloop(int *fd)
{
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);
}

static void	lop(int argc, char *argv[], char **envp, int filein)
{
	int		i;
	int		fd[2];
	pid_t	*pids;

	pids = (pid_t *)malloc((argc - 3) * sizeof(pid_t));
	i = 2;
	while (i <= argc - 2)
	{	
		if (pipe(fd) == -1)
		{
			perror("Error l'orsque de creation de pipe");
			exit(EXIT_FAILURE);  
		}
		pids[i - 2] = fork();
		if (pids[i - 2] == 0 && i != argc - 2)
			child_process(argv, envp, fd, i, filein);
		else if (pids[i - 2] == 0 && i == argc - 2)
			parent_process(argc, argv, envp);
		whilloop(fd);
		i++;
	}
	wit_process(argc, pids, fd);
}

int	main(int argc, char *argv[], char **envp)
{
	int		filein;
	int		fd[2];

	if (argc >= 5)
	{
		if (ft_strncmp ("here_doc", argv[1], ft_strlen(argv[1])) == 0)
			lop_her_doc(argc, argv, envp, fd);
		else
		{
			filein = open(argv[1], O_RDONLY, 0777);
			if (filein == -1)
			{
				perror("Error l'orsque l'ouverture du fichier");
				exit(EXIT_FAILURE);
			}
			lop (argc, argv, envp, filein);
		}
	}
	else
		bad_argument();
}
