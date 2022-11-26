/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 00:19:10 by ilinhard          #+#    #+#             */
/*   Updated: 2022/11/26 06:04:25 by ilinhard         ###   ########.fr       */
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
		return (free(path), -2); // add error code -2 == fd_in or out error
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
	int	error;

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
		error = ft_cmd(cmd, mini);
		close(fd[1]);
		return (error);
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
	if (pid == 0)
	{
		if (ft_cmd(cmd, mini) < 0)
		{
			if (cmd->tab[0] && !cmd->builtin)
			{
				ft_putstr_fd(cmd->tab[0], 2);
				ft_putstr_fd(" : command not found\n", 2);
			}
			return (-1);
		}
	}
	else if (pid)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			g_exit = WEXITSTATUS(status);
			printf("g_exit == %d\n", g_exit);
		}
	}
	return (0);
}

void	ft_close_and_reset_exec(t_cmd *cmd, int out, int in)
{
	ft_clear_cmd_list(cmd);
	dup2(out, STDOUT_FILENO);
	dup2(in, STDIN_FILENO);
	close(in);
	close(out);
	while (wait(NULL) > 0)
		;
}

void	ft_exe(t_env *mini, t_cmd *cmd)
{
	int		out;
	int		in;
	t_cmd	*tmp;

	in = dup(0);
	out = dup(1);
	tmp = cmd;
	while (tmp && tmp->next)
	{
		if (ft_fork(mini, tmp) < 0)
		{
			dup2(out, STDOUT_FILENO);
			if (!tmp->builtin)
			{
				ft_putstr_fd(tmp->tab[0], 2);
				ft_putstr_fd(" : command not found\n", 2);
			}
			ft_exit_clean(mini, cmd, 127);
		}
		tmp = tmp->next;
	}
	if (ft_last_child(tmp, mini) < 0)
		ft_exit_clean(mini, cmd, 127);
	ft_close_and_reset_exec(cmd, out, in);
}
