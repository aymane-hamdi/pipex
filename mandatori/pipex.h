/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 10:51:43 by ahamdi            #+#    #+#             */
/*   Updated: 2024/03/17 20:18:13 by ahamdi           ###   ########.fr       */
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
#endif
