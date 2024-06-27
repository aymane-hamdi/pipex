/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:54:23 by ahamdi            #+#    #+#             */
/*   Updated: 2024/06/27 10:40:25 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*remove_spaces_and_single_quotes(const char *str)
{
	char	*dst;
	int		i;

	i = 0;
	dst = (char *)malloc(ft_strlen(str) + 1);
	if (!dst)
		exit(EXIT_FAILURE);
	while (*str)
	{
		if (*str != '\'' && (*(str + 1) != '{' || *(str - 1) != '}'))
			dst[i++] = *str;
		str++;
	}
	dst[i] = '\0';
	return (dst);
}

char	**realloc_cmd(char ***cmd, int *capacity)
{
	int		i;
	char	**new_cmd;

	*capacity *= 2;
	new_cmd = malloc(*capacity * sizeof(char *));
	if (!new_cmd)
	{
		free(*cmd);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < *capacity / 2)
	{
		new_cmd[i] = (*cmd)[i];
		i++;
	}
	free(*cmd);
	return (new_cmd);
}

void	add_arg_to_cmd(char **cmd, int *size, char *start_ptr)
{
	char	*arg;

	arg = remove_spaces_and_single_quotes(start_ptr);
	if (ft_strlen(arg) > 0)
	{
		cmd[*size] = arg;
		(*size)++;
	}
}

void	process_char(char ***cmd, int *capacity, 
		char **start_ptr, char **end_ptr)
{
	int	in_single_quotes;
	int	size ;

	size = 0;
	in_single_quotes = 0;
	while (**end_ptr)
	{
		if (**end_ptr == '\'')
			in_single_quotes++;
		else if (**end_ptr == ' ' && (in_single_quotes % 2) == 0)
		{
			**end_ptr = '\0';
			if (size >= *capacity - 1) 
				*cmd = realloc_cmd(cmd, capacity);
			add_arg_to_cmd(*cmd, &size, *start_ptr);
			*start_ptr = *end_ptr + 1;
		}
		(*end_ptr)++;
	}
	if (**start_ptr != **end_ptr)
	{
		if (size >= *capacity - 1) 
			*cmd = realloc_cmd(cmd, capacity);
		add_arg_to_cmd(*cmd, &size, *start_ptr);
	}
}

char	**split_command(const char *command)
{
	int		capacity;
	char	*start_ptr;
	char	*end_ptr;
	char	**cmd;

	if (!command)
		return (NULL);
	capacity = 10;
	cmd = malloc(capacity * sizeof(char *));
	if (!cmd)
		exit(EXIT_FAILURE);
	start_ptr = ft_strdup(command);
	end_ptr = start_ptr;
	process_char(&cmd, &capacity, &start_ptr, &end_ptr);
	return (cmd);
}
// int main ()
// {
// 	char **str ;
// 	str = split_command("/bin/ls -l");
// 	while(*str)
// 	{
// 		printf("%s\n", *str);
// 		str++;
// 	}
// }