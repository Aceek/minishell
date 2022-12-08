/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/12/08 22:38:26 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_builtin_code(char *str)
{
	if (!str)
		return (NOT_BUILT_IN);
	if (!ft_strncmp(str, "echo", 4) && !str[4])
		return (ECH);
	if (!ft_strncmp(str, "pwd", 3) && !str[3])
		return (PWD);
	if (!ft_strncmp(str, "cd", 2) && !str[2])
		return (CD);
	if (!ft_strncmp(str, "export", 6) && !str[6])
		return (EXPORT);
	if (!ft_strncmp(str, "unset", 5) && !str[5])
		return (UNSET);
	if (!ft_strncmp(str, "env", 3) && !str[3])
		return (ENV);
	if (!ft_strncmp(str, "exit", 4) && !str[4])
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
