/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 10:51:43 by ahamdi            #+#    #+#             */
/*   Updated: 2024/03/24 23:42:05 by ahamdi           ###   ########.fr       */
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

void	erro_file(void);
void	execute(char *argv, char **envp);
char	**split_command(const char *command);
void	bad_argument(void);
void	run_script(char *script_path, char **envp);
int		ft_count_words(char const *str, char sep);
char	*get_path(char **envp, char *cmd, int i);
void	cas_special(char *argv, char **envp);
void	wit_process(int *fd, int pid, int pid1);
void	erro(void);
#endif
