/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/11/26 03:40:45 by pbeheyt          ###   ########.fr       */
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

char	*get_var_env_val(char *var_env, int var_len, char **env)
{
	int	l;

	l = -1;
	while (env[++l])
	{
		if (ft_strnstr(env[l], var_env, var_len))
			return (ft_cpy(env[l], var_len + 1));
	}
	return (NULL);
}

char	*get_dollar(char *str, int *i, char **env)
{
	char	*var_env;
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
		var_env = get_var_env_name(str, i);
		if (!var_env)
			return (NULL);
		dollar = get_var_env_val(var_env, ft_strlen(var_env), env);
		free(var_env);
	}
	return (dollar);
}
