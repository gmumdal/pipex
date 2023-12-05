/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:11:07 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/05 15:00:09 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>

typedef struct s_data
{
	char	**path;
	char	**cmd;
	int		*pipe;
	pid_t	*id;
	int		cmd_num;
}	t_data;

void	ending_free(t_data *data);
void	close_fd(t_data *data);
void	error_print(int flag);
void	first_setting(char **av, t_data *data, char **env);
char	*path_search(char **env, char *command);
char	**path_setting(char **env);
void	make_child(t_data *data, char **av, int i, char **env);
void	command_exec_end(t_data *data, char **av, char **env);
void	command_exec_first(t_data *data, char **av, char **env);
char	**make_command(char *cmd);
char	**cmd_split(char *cmd, char sep);
int		cmd_countword(char *cmd, char sep);
void	cmd_input(char *toss, char **cmd, char sep);
void	command_error(char *command);

#endif