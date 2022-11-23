/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 00:21:09 by ilinhard          #+#    #+#             */
/*   Updated: 2022/11/23 01:54:46 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_remove_list(t_env *old, t_env *tmp)
{
	if (tmp && old)
	{
		free(tmp->line);
		if (tmp->next)
			old->next = tmp->next;
		else
			old->next = NULL;
		free(tmp);
		return ;
	}
	else
	{
		if (tmp->next)
		{
			free(tmp->line);
			tmp->line = ft_strdup(tmp->next->line);
			ft_remove_list(tmp, tmp->next);
		}
		else
		{
			free(tmp->line);
			tmp->line = NULL;
		}
	}
}

void	ft_remove_if_in_env(t_env *mini, char *args)
{
	t_env	*tmp;
	t_env	*old;
	char	*tmp_args;

	tmp = mini;
	old = NULL;
	while (tmp)
	{
		tmp_args = ft_cpy_env_name(args);
		if (ft_strncmp(tmp->line, tmp_args, ft_strlen(tmp_args)) == 0)
		{
			ft_remove_list(old, tmp);
			free(tmp_args);
			return ;
		}
		free(tmp_args);
		old = tmp;
		tmp = tmp->next;
	}
}

void	ft_unset_builtin(t_cmd *cmd, t_env *mini)
{
	int	i;
	int	error;

	if (!cmd->tab[1])
	{
		printf("unset : not enough arguments\n");
		return ;
	}
	if (!mini || !mini->line)
	{
		printf("error env mini\n");
		return ;
	}
	i = 1;
	while (cmd->tab && cmd->tab[i])
	{
		error = ft_is_valid_env(cmd->tab[i]);
		if (error < 0)
			printf("unset : %s : invalid parameter name\n", cmd->tab[i]);
		else
			ft_remove_if_in_env(mini, cmd->tab[i]);
		i++;
	}
}
