/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 23:15:36 by ilinhard          #+#    #+#             */
/*   Updated: 2022/12/09 00:13:14 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit_minishell(t_env *mini, t_cmd *cmd)
{
	int	i;
	int	error;
	int	exit;

	i = 0;
	error = 0;
	if (!cmd->tab[1])
		ft_exit_clean(mini, cmd, 0);
	while (cmd->tab && cmd->tab[i])
		i++;
	if (i >= 3 && (cmd->tab[1][0] >= '0' && cmd->tab[1][0] <= '9'))
	{
		write(2, "mini : exit: too many arguments\n", 32);
		ft_exit_clean(mini, cmd, 1);
	}
	else if (i >= 3 && !(cmd->tab[1][0] >= '0' && cmd->tab[1][0] <= '9'))
	{
		ft_exec_err(cmd->tab[1], ": mini: exit: numeric argument required\n");
		ft_exit_clean(mini, cmd, 2);
	}
	exit = ft_atoi(cmd->tab[1], &error);
	if (!error)
		ft_exit_clean(mini, cmd, exit);
	ft_exec_err(cmd->tab[1], ": mini: exit: numeric argument required\n");
	ft_exit_clean(mini, cmd, 2);
}
