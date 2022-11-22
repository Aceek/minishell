/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 00:21:09 by ilinhard          #+#    #+#             */
/*   Updated: 2022/11/18 01:32:22 by ilinhard         ###   ########.fr       */
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

void	ft_unset_builtin(t_data *data, t_env *mini)
{
	int	i;
	int	error;

	if (!data->new_args[1])
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
	while (data->new_args && data->new_args[i])
	{
		error = ft_is_valid_env(data->new_args[i]);
		if (error < 0)
			printf("unset : %s : invalid parameter name\n", data->new_args[i]);
		else
			ft_remove_if_in_env(mini, data->new_args[i]);
		i++;
	}
}
