/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:15:14 by ahamdi            #+#    #+#             */
/*   Updated: 2024/03/24 21:47:15 by ahamdi           ###   ########.fr       */
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
void	whilloop(int *fd);
void	erro(void);
char	**split_command(const char *command);
void	execute(char *argv, char **envp);
void	commad_path(char *argv, char **envp);
void	wit_process(int argc, pid_t *pids, int *fd);
void	lop_her_doc(int argc, char *argv[], char **envp, int *fd);
void	parent_process_her_doc(int argc, char **argv, char **envp);
void	run_script(char *script_path, char **envp);

#endif
