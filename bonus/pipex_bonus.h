/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:15:14 by ahamdi            #+#    #+#             */
/*   Updated: 2024/03/18 20:10:22 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include "../libft/libft.h"
# include "../get-next-line/get_next_line_bonus.h"

char	*get_path(char **envp, char *cmd, int i);
char    **split_command(const char *command, int size);
void	execute(char *argv, char **envp);
void cas_special(char *argv, char **envp);
void	lop_her_doc(int argc, char *argv[], char **envp, int *fd);
void	parent_process_her_doc(int argc, char **argv, char **envp);

#endif
