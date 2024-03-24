/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:30:56 by ahamdi            #+#    #+#             */
/*   Updated: 2024/03/24 00:53:34 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cas_special(char *argv, char **envp)
{
	char	**res;
	char	**cmd ;
	int		i;
	char	*path;
	int		k;

	i = 0;
	path = NULL;
	path = argv;
	k = ft_count_words(argv, '/');
	cmd = malloc(2 * sizeof(char *));
	res = ft_split(argv, '/');
	cmd[0] = res[k - 1];
	cmd[1] = NULL;
	free(res); 
	if (execve(path, cmd, envp) == -1)
	{
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
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
        while (cmd[i])
            free(cmd[i++]);
        free(cmd);
    }
    if(execve(path, cmd, envp)== -1)
    {
        perror("execve failed");
        exit(EXIT_FAILURE);
    }
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