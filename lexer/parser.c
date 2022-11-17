/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/11/18 00:35:19 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	check_built_in(char *str)
{
	if (!str)
		return (NOT_BUILT_IN);
	if (ft_strncmp(str, "echo", ft_strlen("echo")))
		return (ECH);
	if (ft_strncmp(str, "cd", ft_strlen("cd")))
		return (CD);
	if (ft_strncmp(str, "export", ft_strlen("export")))
		return (EXPORT);
	if (ft_strncmp(str, "unset", ft_strlen("unset")))
		return (UNSET);
	if (ft_strncmp(str, "env", ft_strlen("env")))
		return (ENV);
	if (ft_strncmp(str, "exit", ft_strlen("exit")))
		return (EXIT);
	return (NOT_BUILT_IN);
}

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
	cmd->built_in = check_built_in(cmd->tab[0]);
	cmd->token = data->curr_token;
	cmd->list_cmd = data->list_cmd;
	ft_list_add_back(&data->list_cmd, cmd);
	return (0);
}

char *create_buffer(t_data *data)
{
	char *buffer;
	
	buffer = malloc(sizeof(char));
	if (!buffer)
	{
		data->error = 1;
		return (NULL);
	}
	buffer[0] = 0;
	return (buffer);
}

void	parse_input(t_data *data)
{
	int		i;
	char	*buffer;
	
	buffer = create_buffer(data);
	i = -1;
	while (data->input[++i])
	{
		data->curr_token = check_token(data->input, &i);	
		if (data->curr_token)
		{
			add_cmd(data, buffer);
			buffer = create_buffer(data);
		}
		else if (data->input[i] == '$' && check_quote_pos(data->input, i) != 1)
			buffer = ft_strjoin(buffer, dollar_handler(data->input, &i, data->env));
		else
			buffer = ft_charjoin(buffer, data->input[i]);
	}
	add_cmd(data, buffer);
}