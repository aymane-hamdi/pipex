/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:55:14 by ahamdi            #+#    #+#             */
/*   Updated: 2024/03/19 20:11:05 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	run_script(char *script_path, char **envp)
{
	char	*path;
	char	**cmd;

	path = script_path;
	cmd = malloc(2 * sizeof(char *));
	cmd[0] = script_path;
	cmd[1] = NULL;
	if (execve(path, cmd, envp) == -1)
	{
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
	free(cmd);
}

char	*get_path(char **envp, char *cmd, int i)
{
	char	*path_new;
	char	*path;
	char	**path_split;

	while (envp[i++])
	{
		if (ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i]) - 5) != NULL)
		{
			path = ft_strnstr (envp[i], "PATH=", ft_strlen (envp[i]) - 5) + 5;
			break ;
		}
	}
	i = 0;
	path_split = ft_split(path, ':');
	while (path_split[i++])
	{
		path_split[i] = ft_strjoin (path_split[i], "/");
		path_split[i] = ft_strjoin (path_split[i], cmd);
		if (access(path_split[i], X_OK) == 0) 
			break ;
		free(path_split[i]);
	}
	return (path_split[i]);
}

static	void	child_process(char **argv, char **envp, int *fd)
{
	int		filein;

	filein = open(argv[1], O_RDONLY, 0777);
	if (filein == -1)
	{
		perror("Error l'orsque l'ouverture du fichier");
		return ;
	}
	dup2(filein, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	if (argv[2] != NULL && envp != NULL)
	{
		if (argv[2][0] == '/')
			cas_special(argv[2], envp);
		else if (argv[2][0] == '.')
			run_script(argv[2], envp);
		else
			execute(argv[2], envp);
	}
	else 
		perror("error dans argv ou envp");
}

void	parent(char **argv, char **envp, int *fd, int pid1)
{
	pid_t	pid2;
	int		fileout;

	pid2 = fork();
	if (pid2 == 0)
	{
		fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fileout == -1)
			perror("Error l'orsque l'ouverture du fichier");
		dup2(fd[0], STDIN_FILENO);
		dup2(fileout, STDOUT_FILENO);
		close(fd[1]);
		execute(argv[3], envp);
	}
	else
	{
		close(fd[0]);
		close(fd[1]);
		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);
	}
}

int	main(int argc, char *argv[], char **envp)
{
	int		fd[2];
	pid_t	pid1;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			perror("Error l'orsque de creation de pipe");
		pid1 = fork();
		if (pid1 == -1)
			perror("Error l'orsque de creation de processus");
		if (pid1 == 0)
			child_process(argv, envp, fd);
		else
			parent(argv, envp, fd, pid1);
	}
	else
		bad_argument();
}
