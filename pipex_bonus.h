/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:11:07 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/04 18:48:32 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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
void	make_child(t_data *data, char **av, int i, char **env);
void	command_exec_first(t_data *data, char **av, char **env);
void	command_exec_mid(t_data *data, int i, char **env);
void	command_exec_end(t_data *data, char **env);
void	close_pipe(t_data *data, int i);
void	make_heredoc(char **av, char **heredoc);
void	heredoc_setting(int ac, char **av, t_data *data, char **env);
int		ending(t_data *data, char *heredoc);
void	ending_free(t_data *data);
char	**make_command(char *cmd);
char	**xfile_split(char *cmd);
char	**cmd_split(char *cmd, char sep);
int		cmd_countword(char *cmd, char sep);
void	cmd_input(char *toss, char **cmd, char sep);
void	make_child_heredoc(t_data *data, char *heredoc, char **env);
void	command_exec_first_heredoc(t_data *data, char *heredoc, char **env);
void	command_exec_end_heredoc(t_data *data, char **env);

#endif