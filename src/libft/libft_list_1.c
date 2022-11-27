/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_list_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 05:51:45 by ilinhard          #+#    #+#             */
/*   Updated: 2022/11/27 06:15:33 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_list_add_back(t_cmd **list, t_cmd *new)
{
	t_cmd	*back;

	if (!*list)
	{
		*list = new;
		return ;
	}
	back = ft_get_list_last(*list);
	back->next = new;
}

int	lst_addback(t_env *mini_env, char *env)
{
	t_env	*temp;
	t_env	*env_clone;

	env_clone = mini_env;
	if (!env_clone->line)
		return (env_clone->line = ft_strdup(env), 1);
	temp = malloc(sizeof(t_env));
	if (!temp)
		return (0);
	temp->line = ft_strdup(env);
	temp->next = NULL;
	if (!temp->line)
		return (free(temp), 0);
	while (env_clone->next)
		env_clone = env_clone->next;
	env_clone->next = temp;
	return (1);
}

void	lst_freeall(t_env *mini_env)
{
	t_env	*temp;

	while (mini_env)
	{
		temp = mini_env;
		mini_env = mini_env->next;
		if (temp->line)
		{
			free(temp->line);
			temp->line = NULL;
		}
		free(temp);
	}
}

void	ft_clear_cmd_list(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_cmd	*next;

	tmp = cmd;
	while (tmp)
	{
		next = tmp->next;
		ft_clear_tab(tmp->tab);
		ft_clear_fd(tmp);
		if (tmp)
			free(tmp);
		tmp = next;
	}
	cmd = NULL;
}
