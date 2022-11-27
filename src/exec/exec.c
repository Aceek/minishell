/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 00:19:10 by ilinhard          #+#    #+#             */
/*   Updated: 2022/11/27 03:22:49 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cmd(t_cmd *cmd, t_env *mini)
{
	char	*path;
	char	**env;

	path = NULL;
	if ((cmd->tab[0][0] == '/' || cmd->tab[0][0] == '.')
	&& !cmd->builtin)
		path = ft_strdup(cmd->tab[0]);
	else if (!cmd->builtin)
		path = ft_get_path(cmd->tab[0], cmd->env);
	if ((cmd->fd_in < 0 || cmd->fd_out < 0) || (!path && !cmd->builtin))
		return (free(path), -2);
	if (cmd->fd_in > STDIN_FILENO)
		dup2(cmd->fd_in, STDIN_FILENO);
	if (cmd->fd_out > STDOUT_FILENO)
		dup2(cmd->fd_out, STDOUT_FILENO);
	if (cmd->builtin)
		ft_builtin(cmd, mini);
	else
	{
		env = ft_make_tab_from_env(mini);
		execve(path, cmd->tab, env);
		free_tab(env);
	}
	return (free(path), -1);
}

int	ft_fork(t_env *mini, t_cmd *cmd)
{
	int	fd[2];
	int	pid;

	pipe(fd);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid != 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	else if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		ft_cmd(cmd, mini);
		close(fd[1]);
		return (-1);
	}
	return (0);
}

int	ft_last_child(t_cmd *cmd, t_env *mini)
{
	int	pid;
	int	status;

	if (cmd->builtin)
		return (ft_cmd(cmd, mini), 0);
	pid = fork();
	signal(SIGINT, ft_signal_newline2);
	if (pid == 0)
	{
		if (ft_cmd(cmd, mini) < 0)
		{
			if (cmd->tab[0] && !cmd->builtin)
				ft_exec_err(cmd->tab[0], " : command not found\n");
			return (-1);
		}
	}
	else if (pid)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_exit = WEXITSTATUS(status);
	}
	return (signal(SIGINT, ft_signal_newline), 0);
}

void	ft_close_and_reset_exec(t_cmd *cmd, int out, int in, int error)
{
	while (wait(NULL) > 0)
		;
	if (error)
		g_exit = 1;
	ft_clear_cmd_list(cmd);
	dup2(out, STDOUT_FILENO);
	dup2(in, STDIN_FILENO);
	close(in);
	close(out);
}

int	ft_exe(t_env *mini, t_cmd *cmd, int error)
{
	int		out;
	int		in;
	t_cmd	*tmp;

	if (!cmd)
		return (g_exit = 1, 1);
	in = dup(0);
	out = dup(1);
	tmp = cmd;
	while (tmp && tmp->next)
	{
		if (ft_fork(mini, tmp) < 0)
		{
			dup2(out, STDOUT_FILENO);
			if (!tmp->builtin)
				ft_exec_err(cmd->tab[0], " : command not found\n");
			ft_exit_clean(mini, cmd, 127);
		}
		tmp = tmp->next;
	}
	if (ft_last_child(tmp, mini) < 0)
		ft_exit_clean(mini, cmd, 127);

	ft_close_and_reset_exec(cmd, out, in, error);
	return (0);
}
