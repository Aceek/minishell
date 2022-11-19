/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 04:56:29 by ilinhard          #+#    #+#             */
/*   Updated: 2022/11/19 05:11:02 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str && str[i])
		i++;
	return (i);
}

int	ft_atoi(char *str, int *e)
{
	long	p;
	int		m;
	int		i;

	i = 0;
	p = 0;
	m = 1;
	if (!str)
		return (0);
	while ((str[i] <= 13 && str[i] >= 9) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			m = -m;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		p = p * 10;
		p = p + (str[i] - 48);
		i++;
	}
	*e = i;
	return (p * m);
}

void	lst_freeall(t_env *mini_env)
{
	t_env	*temp;

	while (mini_env)
	{
		temp = mini_env;
		mini_env = mini_env->next;
		if (temp->line)
			free(temp->line);
		free(temp);
	}
}
