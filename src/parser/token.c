/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/12/08 11:57:15 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_builtin_code(char *str)
{
	if (!str)
		return (NOT_BUILT_IN);
	if (!ft_strncmp(str, "echo", ft_strlen("echo")))
		return (ECH);
	if (!ft_strncmp(str, "pwd", ft_strlen("pwd")))
		return (PWD);
	if (!ft_strncmp(str, "cd", ft_strlen("cd")))
		return (CD);
	if (!ft_strncmp(str, "export", ft_strlen("export")))
		return (EXPORT);
	if (!ft_strncmp(str, "unset", ft_strlen("unset")))
		return (UNSET);
	if (!ft_strncmp(str, "env", ft_strlen("env")))
		return (ENV);
	if (!ft_strncmp(str, "exit", ft_strlen("exit")))
		return (EXIT);
	return (NOT_BUILT_IN);
}

int	get_token_code(char *str, int *i)
{
	if (str[*i + 1])
	{
		if (!check_quote_pos(str, *i) && !check_quote_pos(str, *i + 1))
		{
			if (!ft_strncmp(str + *i, ">>", 2))
				return (*i += 2, DGREAT);
			if (!ft_strncmp(str + *i, "<<", 2))
				return (*i += 2, DLESS);
		}
	}
	if (!check_quote_pos(str, *i))
	{
		if (!ft_strncmp(str + *i, "<", 1))
			return (*i += 1, LESS);
		if (!ft_strncmp(str + *i, ">", 1))
			return (*i += 1, GREAT);
		if (!ft_strncmp(str + *i, "|", 1))
			return (*i += 1, PIPE);
	}
	return (NOT_TOKEN);
}

int	check_token_error(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (get_token_code(str, &i))
		{
			if (get_token_code(str, &i))
				return (1);
			while (ft_isspace(str[i]))
				i++;
			if (!str[i])
				return (1);
		}
	}
	return (0);
}

int	check_token(t_data *data, int *i)
{
	data->token = get_token_code(data->input, i);
	if (data->token == PIPE && check_quote_pos(data->input, *i) == 0)
		return (1);
	if (data->token > PIPE && check_quote_pos(data->input, *i) == 0)
		redir_handler(data, data->input, i);
	return (0);
}
