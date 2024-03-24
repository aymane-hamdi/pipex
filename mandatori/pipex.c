/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:55:14 by ahamdi            #+#    #+#             */
/*   Updated: 2024/03/24 01:05:45 by ahamdi           ###   ########.fr       */
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

static void	child(char **argv, char **envp, int *fd, int filein)
{
	dup2(filein, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	if (argv[2][0] == '/')
		cas_special(argv[2], envp);
	else if (argv[2][0] == '.')
		run_script(argv[2], envp);
	else
		execute(argv[2], envp);
}

static void	parent(int *fd, char **argv, char **envp)
{
	int		fileout;

	fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fileout == -1)
	{
		perror("Error l'orsque l'ouverture du fichier");
		exit(1);  
	}
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	dup2(fileout, STDOUT_FILENO);
	if (argv[3][0] == '/')
		cas_special(argv[3], envp);
	else if (argv[3][0] == '.')
		run_script(argv[3], envp);
	else
		execute(argv[3], envp);
}
void	wit_process(int *fd ,int pid)
{
	waitpid(pid, NULL, 0);
	close(fd[0]);
	close(fd[1]);
}
int	main(int argc, char *argv[], char **envp)
{
    int		fd[2];
    int		pid;
    int		filein;
    if (argc == 5)
    {
        filein = open(argv[1], O_RDONLY);
        if (filein == -1)
        {
            perror("Error l'orsque l'ouverture du fichier");
            exit(EXIT_FAILURE);
        }
        if (pipe(fd) == -1)
        {
            perror("Error l'orsque de creation de pipe");
            exit(EXIT_FAILURE);  
        }
        pid = fork();
        if (pid == -1)
        {
            perror("Error lors de la création du processus");
            exit(EXIT_FAILURE);
        }
        if (pid == 0)
		{
			child(argv, envp, fd, filein);
			system("leaks pipex");
		}
        else
		{
			 parent(fd, argv, envp);
			 system("leaks pipex");
		}
        wit_process(fd, pid);	
	}
	else
		bad_argument();
}
