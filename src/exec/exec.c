/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 00:19:10 by ilinhard          #+#    #+#             */
/*   Updated: 2023/01/14 03:24:04 by ilinhard         ###   ########.fr       */
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
		path = ft_get_path(cmd->tab[0], mini);
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
		ft_verify_errno(cmd);
		ft_clear_tab(env);
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
		if (cmd->builtin)
			wait(NULL);
		close(fd[0]);
	}
	else if (pid == 0)
	{
		signal(SIGQUIT, ft_signal_quit);
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

	pid = fork();
	signal(SIGINT, ft_signal_newline2);
	signal(SIGQUIT, ft_signal_quit);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (ft_cmd(cmd, mini) < 0)
		{
			if (cmd->tab[0] && !cmd->builtin && cmd->tab[0][0] != '.')
				return (g_exit = 127,
					ft_exec_err(cmd->tab[0], " : command not found\n"), -1);
			return (-1);
		}
	}
	else if (pid)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_exit = WEXITSTATUS(status);
	}
	return (signal(SIGINT, ft_signal_newline), signal(SIGQUIT, SIG_IGN), 0);
}

int	ft_exe_last_child(t_cmd *cmd, t_cmd *tmp, t_env *mini)
{
	if (tmp->builtin == EXIT)
	{
		close(cmd->cpy_in);
		close(cmd->cpy_out);
		return (ft_exit_minishell(mini, cmd), 0);
	}
	if (tmp->builtin == EXPORT || tmp->builtin == UNSET || tmp->builtin == CD)
		ft_cmd(tmp, mini);
	else if (ft_last_child(tmp, mini) < 0)
	{
		close(cmd->cpy_in);
		close(cmd->cpy_out);
		return (ft_exit_clean (mini, cmd, g_exit), 0);
	}
	return (0);
}

int	ft_exe(t_env *mini, t_cmd *cmd, int error)
{
	t_cmd	*tmp;

	if (!cmd)
		return (g_exit = 1, 1);
	cmd->cpy_in = dup(0);
	cmd->cpy_out = dup(1);
	tmp = cmd;
	while (tmp && tmp->next)
	{
		if (ft_fork(mini, tmp) < 0)
		{
			dup2(cmd->cpy_out, STDOUT_FILENO);
			if (!tmp->builtin && tmp->tab[0][0] != '.')
				ft_exec_err(tmp->tab[0], " : command not found\n");
			close(cmd->cpy_in);
			close(cmd->cpy_out);
			return (ft_exit_clean(mini, cmd, g_exit), 0);
		}
		tmp = tmp->next;
	}
	ft_exe_last_child(cmd, tmp, mini);
	return (ft_close_and_reset_exec(cmd, error), 0);
}
