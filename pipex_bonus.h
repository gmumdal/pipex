/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:11:07 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/02 18:34:50 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft.h"
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_data
{
	char	**path;
	char	**cmd;
	int		**pipe;
	pid_t	*id;
	int		cmd_num;
}	t_data;

void	error_print(int flag);
char	**path_setting(char **env);
char	*path_search(char **env, char *command);
int		open_check(int ac, char **av, int *fd, char **heredoc);
void	first_setting(int ac, char **av, t_data *data, char **env);
void	error_print(int flag);
void	make_child(t_data *data, int *fd, int i, char **env);
void	command_exec_first(t_data *data, int fd, char **env);
void	command_exec_mid(t_data *data, int i, char **env);
void	command_exec_end(t_data *data, int fd, char **env);
void	command_exec_only(t_data *data, int *fd, char **env);
void	close_fd(t_data *data, int *fd);
void	make_heredoc(int *fd, char **av, char *heredoc);
void	heredoc_setting(int ac, char **av, t_data *data, char **env);
void	ending(t_data *data, int *fd, char *heredoc);

#endif