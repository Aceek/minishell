/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/12/11 10:49:13 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_cmd(t_data *data)
{
	data->buf = create_buffer();
	if (!data->buf)
		return (free_all_exit(data, 1), 1);
	data->fd_in = 0;
	data->fd_out = 1;
	data->error = 0;
	return (0);
}

int	add_cmd(t_data *data)
{
	t_cmd	*cmd;
	
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (free_all_exit(data, 1), 1);
	ft_memset(cmd, 0, sizeof(t_cmd));
	cmd->tab = ft_split_parser(data->buf);
	if (!cmd->tab || !cmd->tab[0])
		return (free_tab(cmd->tab), free(cmd), ft_clear_cmd_list(data->head_cmd), 1);
	cmd->fd_in = data->fd_in;
	cmd->fd_out = data->fd_out;
	cmd->builtin = get_builtin_code(cmd->tab[0]);
	cmd->head_cmd = data->head_cmd;
	cmd->env = data->env;
	ft_list_add_back(&data->head_cmd, cmd);
	return (0);
}

int	parse_input(t_data *data)
{
	int		i;

	if (check_error(data->input))
		return (1);
	init_cmd(data);
	data->nb_hd = 0;
	i = -1;
	while (data->input[++i])
	{
		data->token = get_token_code(data->input, &i);
		if (data->token == PIPE)
		{
			if (!data->error)
			{
				if (add_cmd(data))
					return (free(data->buf), 1);
			}
			free(data->buf);
			init_cmd(data);
		}
		else if (data->token)
			redir_handler(data, data->input, &i);
		else if (data->token == NOT_TOKEN)
			data->buf = convert_input(data, data->buf, data->input, &i);
	}
	add_cmd(data);
	free(data->buf);
	return (0);
}
