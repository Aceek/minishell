/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/11/16 03:30:37 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	add_cmd(t_data *data, char *buffer)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (1);
	ft_memset(cmd, 0, sizeof(t_cmd));
	cmd->tab = ft_split(buffer);
	free(buffer);
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->list_cmd = data->list_cmd;
	ft_list_add_back(&data->list_cmd, cmd);
	return (0);
}

void	parse_input(t_data *data)
{
	int		i;
	int		token;
	char	*buffer;
	
	buffer = malloc(sizeof(char));
	buffer[0] = 0;
	i = -1;
	while (data->input[++i])
	{
		token = check_token(data->input, &i);	
		if (token)
		{
			add_cmd(data, buffer);
			buffer = malloc(sizeof(char));
			buffer[0] = 0;
		}
		else if (data->input[i] == '$' && check_quote_pos(data->input, i) != 1)
			buffer = ft_strjoin(buffer, dollar_handler(data->input, &i, data->env));
		else
			buffer = ft_charjoin(buffer, data->input[i]);
	}
	add_cmd(data, buffer);
}