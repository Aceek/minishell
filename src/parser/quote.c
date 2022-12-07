/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/12/07 18:25:24 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_quote(bool *quote)
{
	if (*quote == false)
		*quote = true;
	else if (*quote == true)
		*quote = false;
}

int	check_quote_error(char *str)
{
	bool	simple_quote;
	bool	double_quote;
	int		i;

	if (!str)
		return (-1);
	simple_quote = false;
	double_quote = false;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' && double_quote == false)
			update_quote(&simple_quote);
		if (str[i] == '\"' && simple_quote == false)
			update_quote(&double_quote);
	}
	if (double_quote == true)
		return (2);
	if (simple_quote == true)
		return (1);
	return (0);
}

int	check_quote_pos(char *str, int pos)
{
	bool	simple_quote;
	bool	double_quote;
	int		i;

	if (!str)
		return (-1);
	simple_quote = false;
	double_quote = false;
	i = -1;
	while (++i < pos)
	{
		if (str[i] == '\'' && double_quote == false)
			update_quote(&simple_quote);
		if (str[i] == '\"' && simple_quote == false)
			update_quote(&double_quote);
	}
	if (str[i] != '\"' && double_quote == true)
		return (2);
	if (str[i] != '\'' && simple_quote == true)
		return (1);
	return (0);
}
