/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/11/26 04:04:00 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_var_env_name(char *str, int *i)
{
	char	*var;
	char	*tmp;

	var = create_buffer();
	if (!var)
		return (NULL);
	while (ft_isalnum(str[*i]) || str[*i] == '_')
	{
		tmp = ft_charjoin(var, str[*i]);
		free(var);
		var = tmp;
		*i += 1;
	}
	return (var);
}

char	*get_var_env_val(char *var_env, int len, t_env *mini)
{
	t_env	*tmp;
	
	tmp = mini;
	while (tmp)
	{
		if (!ft_strncmp(tmp->line, var_env, len))
			return (ft_cpy(tmp->line, len + 1));
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_dollar(char *str, int *i, t_env *mini)
{
	char	*var_env_name;
	char	*dollar;
	
	*i += 1;
	if (!str[*i])
		return (NULL);
	else if (str[*i] == '?')
	{
		dollar = ft_itoa(g_exit);
		*i += ft_strlen(dollar);
	}
	else
	{	
		var_env_name = get_var_env_name(str, i);
		if (!var_env_name)
			return (NULL);
		dollar = get_var_env_val(var_env_name, ft_strlen(var_env_name), mini);
		free(var_env_name);
	}
	return (dollar);
}
