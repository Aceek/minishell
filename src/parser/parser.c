/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/12/09 03:10:05 by pbeheyt          ###   ########.fr       */
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

	if (data->error)
		return (1);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (free_all_exit(data, 1), 1);
	ft_memset(cmd, 0, sizeof(t_cmd));
	cmd->tab = ft_split_parser(data->buf);
	if (!cmd->tab || !cmd->tab[0])
		return (free_tab(cmd->tab), free(cmd), free_all_exit(data, 1), 1);
	cmd->fd_in = data->fd_in;
	cmd->fd_out = data->fd_out;
	cmd->builtin = get_builtin_code(cmd->tab[0]);
	cmd->head_cmd = data->head_cmd;
	cmd->env = data->env;
	ft_list_add_back(&data->head_cmd, cmd);
	return (0);
}

int	check_error(char *input)
{
	if (check_quote_error(input))
		return (g_exit = 2,
			write(2, "minishell : quotes not closing error\n", 37), 1);
	if (check_token_error(input))
		return (g_exit = 2,
			write(2, "minishell : syntax error near unexpected token\n", 47), 1);
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
		if (check_token(data, &i))
		{
			add_cmd(data);
			free(data->buf);
			init_cmd(data);
		}
		if (!data->error)
			data->buf = convert_input(data, data->buf, data->input, &i);
		if (data->input[i] == '\0')
			break ;
	}
	add_cmd(data);
	free(data->buf);
	return (0);
}
