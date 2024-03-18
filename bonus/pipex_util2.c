/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:54:23 by ahamdi            #+#    #+#             */
/*   Updated: 2024/03/18 21:53:41 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"


char	*get_path(char **envp, char *cmd, int i)
{
	char	*path_new = NULL;
	char	*path;
	char	**path_split;

	while (envp[i++])
	{
		if (ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i]) - 5) != NULL)
		{
			path = ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i]) - 5) + 5; 
			break ;
		}
	}
	i = 0;
	path_split = ft_split(path, ':');
	while (path_split[i])
	{
		path_split[i] = ft_strjoin(ft_strjoin(path_split[i], "/"), cmd);
		if (access(path_split[i], X_OK) == 0)
		{
			path_new = path_split[i];
			break ;
		}
		i++;
	}
	return (path_new);
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
void run_script(char *script_path, char **envp)
{
	char *path;
	char **cmd;
	path=script_path;
	cmd = malloc(2* sizeof(char *));
	cmd[0] = script_path;
	cmd[1] = NULL;
	if(execve(path, cmd, envp)== -1)
	{
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
	free(cmd);
}
