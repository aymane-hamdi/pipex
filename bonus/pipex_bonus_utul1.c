/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utul1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:55:03 by ahamdi            #+#    #+#             */
/*   Updated: 2024/03/23 23:10:58 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*remove_spaces_and_single_quotes(const char *str)
{
	char	*result;
	char	*dst;

	result = (char *)malloc(strlen(str) + 1);
	if (!result)
		exit(EXIT_FAILURE);
	dst = result;
	while (*str)
	{
		if (*str != '\'' && (*(str + 1) != '{' || *(str - 1) != '}'))
			*dst++ = *str;
		str++;
	}
	*dst = '\0';
	return (result);
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
	*cmd = new_cmd;
	return (*cmd);
}

void	add_arg_to_cmd(char **cmd, int *size, char *start_ptr)
{
	char	*arg;

	arg = remove_spaces_and_single_quotes(start_ptr);
	if (strlen(arg) > 0)
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
	while (**end_ptr)
	{
		if (**end_ptr == '\'' && ((*(*end_ptr + 1) && *(*end_ptr + 1) == '{') 
				|| (*end_ptr != *start_ptr && *(*end_ptr - 1) == '}')))
			in_single_quotes = !in_single_quotes;
		else if (**end_ptr == ' ' && !in_single_quotes)
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

char	**split_command(const char *command, int size)
{
	int		capacity;
	char	*start_ptr;
	char	*end_ptr;
	char	**cmd;

	capacity = 10;
	cmd = malloc(capacity * sizeof(char *));
	if (!cmd)
		exit(EXIT_FAILURE);
	start_ptr = ft_strdup(command);
	end_ptr = start_ptr;
	process_char(&cmd, &capacity, &start_ptr, &end_ptr);
	return (cmd);
}
