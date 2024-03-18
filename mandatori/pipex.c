/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:55:14 by ahamdi            #+#    #+#             */
/*   Updated: 2024/03/18 18:09:03 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_path(char **envp, char *cmd, int i)
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

static int	ft_count_words(char const *str, char sep)
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
void cas_special(char *argv, char **envp)
{
		char **res;
		char	**cmd ;
		int		i = 0;
		char	*path = NULL;
		
	path = argv;
    int k = ft_count_words(argv, '/');
    cmd = malloc(2* sizeof(char *));
    res = ft_split(argv, '/');
    cmd[0] = res[k - 1];
    cmd[1] = NULL;
    free(res); 
	if(execve(path, cmd, envp)== -1)
    {
        perror("execve failed");
        exit(EXIT_FAILURE);
    }
	free(path);
	free(cmd);
}
void	execute(char *argv, char **envp)
{
    char	**cmd = NULL;
    int		i = 0;
    char	*path = NULL;
    
    cmd = split_command(argv,i);
    path = get_path(envp, cmd[0], i);
    if (!path)
    {
        i = 0;
        while (cmd[i])  // Only free if cmd[i] is not NULL
            free(cmd[i++]);
        free(cmd);
        exit(EXIT_FAILURE);
    }
    if(execve(path, cmd, envp)== -1)
    {
        perror("execve failed");
        exit(EXIT_FAILURE);
    }

}


static void	child_process(char **argv, char **envp, int *fd)
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
		if(argv[2][0]== '/')
			cas_special(argv[2],envp);
		else
			execute(argv[2], envp);
	}
	else 
		perror("error dans argv ou envp");
}

void	bad_argument(void)
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

int	main(int argc, char *argv[], char **envp)
{
	int		fd[2];
	pid_t	pid;
	int		fileout;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			perror("Error l'orsque de creation de pipe");
		pid = fork();
		if (pid == -1)
			perror("Error l'orsque de creation de processus");
		if (pid == 0)
			child_process(argv, envp, fd);
		waitpid(pid, NULL, 0);
		fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fileout == -1)
			perror("Error l'orsque l'ouverture du fichier");
		dup2(fd[0], STDIN_FILENO);
		dup2(fileout, STDOUT_FILENO);
		close(fd[1]);
		execute(argv[3], envp);
		perror("error dans argv ou envp");
	}
	else
		bad_argument();
}
