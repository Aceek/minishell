/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/11/22 04:07:06 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	get_var_len(char *str, int i)
{
	int	var_len;

	var_len = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
	{	
		var_len += 1;
		i++;
	}
	return (var_len);
}

char	*get_var_val(char *var_name, int var_len, char **env)
{
	int	l;

	l = -1;
	while (env[++l])
	{
		if (ft_strnstr(env[l], var_name, var_len))
			return (ft_cpy(env[l], var_len + 1));
	}
	return (NULL);
}

char	*dollar_handler(char *str, int *i, char **env)
{
	int		var_len;
	char	*var_name;
	char	*var_val;

	var_len = 0;
	if (!str[*i + 1])
		return (NULL);
	// else if (!str[*i + 1] == '?')
		//...Stores the exit value of the last command that was executed
	else
	{	
		var_len = get_var_len(str, *i + 1);
		var_name = ft_strncpy_from (str, *i + 1, var_len);
		var_val = get_var_val(var_name, var_len, env);
		*i += var_len;
	}	
	return (var_val);
}
