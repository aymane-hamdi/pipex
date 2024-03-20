/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 10:51:43 by ahamdi            #+#    #+#             */
/*   Updated: 2024/03/19 19:18:59 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h> 
# include <sys/wait.h>
# include <fcntl.h>
# include "../libft/libft.h"

void	execute(char *argv, char **envp);
char	**split_command(const char *command, int size);
void	bad_argument(void);
void	run_script(char *script_path, char **envp);
int		ft_count_words(char const *str, char sep);
char	*get_path(char **envp, char *cmd, int i);
void	cas_special(char *argv, char **envp);
#endif
