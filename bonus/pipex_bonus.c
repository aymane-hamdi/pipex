/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:30:28 by ahamdi            #+#    #+#             */
/*   Updated: 2024/03/18 20:12:21 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	child_process(char **argv, char **envp, int *fd, int i)
{
	int		filein;

	if (i == 2)
	{
		filein = open(argv[1], O_RDONLY, 0777);
		if (filein == -1)
		{
			perror("Error l'orsque l'ouverture du fichier");
			exit(EXIT_FAILURE);  
		}
		dup2(filein, STDIN_FILENO);
		close(filein);
	}
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	if(argv[i][0]== '/')
		cas_special(argv[i], envp);
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
		exit(EXIT_FAILURE);  
	}
	dup2(fileout, STDOUT_FILENO);
	if(argv[argc - 2][0]== '/')
		cas_special(argv[argc - 2], envp);
	else
		execute(argv[argc - 2], envp);
}

static void	lop(int argc, char *argv[], char **envp, int *fd)
{
	int		i;
	pid_t	pid1;

	i = 2;
	while (i < argc - 2)
	{
		if (pipe(fd) == -1)
		{
			perror("Error l'orsque de creation de pipe");
			exit(EXIT_FAILURE);  
		}
		pid1 = fork();
		if (pid1 == -1)
		{
			perror("Error l'orsque de creation de processus");
			exit(EXIT_FAILURE);  
		}
		if (pid1 == 0)
			child_process(argv, envp, fd, i);
		waitpid(pid1, NULL, 0);
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		i++;
	}
}

int	main(int argc, char *argv[], char **envp)
{
	int		fd[2];

	if (argc >= 5)
	{
		if (ft_strncmp ("here_doc", argv[1], ft_strlen(argv[1])) == 0)
		{
			lop_her_doc(argc, argv, envp, fd);
			parent_process_her_doc (argc, argv, envp);
		}
		else
		{
			lop (argc, argv, envp, fd);
			parent_process(argc, argv, envp);
		}
	}
	else
		bad_argument();
}
