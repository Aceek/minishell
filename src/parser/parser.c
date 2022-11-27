/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/11/27 03:25:55 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_cmd(t_data *data)
{
	t_cmd	*cmd;

	if (data->error)
		return (1);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (1);
	ft_memset(cmd, 0, sizeof(t_cmd));
	cmd->tab = ft_split(data->buf);
	cmd->fd_in = data->curr_fd_in;
	cmd->fd_out = data->curr_fd_out;
	cmd->builtin = get_builtin_code(cmd->tab[0]);
	cmd->head_cmd = data->head_cmd;
	cmd->env = data->env;
	ft_list_add_back(&data->head_cmd, cmd);
	free(data->buf);
	return (0);
}

char	*create_buffer(void)
{
	char	*buf;

	buf = malloc(sizeof(char));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	return (buf);
}

int	check_token(t_data *data, int *i)
{
	data->curr_token = get_token_code(data->input, i);
	// if (check_token_error)
	// 	return (write(2, "minishell : syntax error near unexpected token\n", 47) , 1);
	if (data->curr_token > PIPE)
		redir_handler(data, data->input, i);
	if (data->curr_token == PIPE)
	{
		add_cmd(data);
		return (1);
	}
	return (0);
}
char	*convert_input(t_data *data, char *input, char *buf, int *i)
{
	char	*var;
	char	*tmp;

	if (input[*i] == '$' && check_quote_pos(input, *i) != 1)
	{	
		var = get_dollar(input, i, data->mini);
		tmp = ft_strjoin(buf, var);
		free(buf);
		free(var);
		buf = tmp;
	}
	else
	{
		tmp = ft_charjoin(buf, data->input[*i]);
		free(buf);
		buf = tmp;
	}
	return (buf);
}

int	parse_input(t_data *data)
{
	int		i;

	if (check_quote_error(data->input))
		return (write(2, "minishell : quotes not closing error\n", 37) , 1);
	data->buf = create_buffer();
	if (!data->buf)
		return (1);
	data->curr_fd_in = 0;
	data->curr_fd_out = 1;
	data->error = 0;
	i = -1;
	while (data->input[++i])
	{
		if (check_token(data, &i))
		{
			data->buf = create_buffer();
			if (!data->buf)
				return (1);
			data->curr_fd_in = 0;
			data->curr_fd_out = 1;
			data->error = 0;
		}
		data->buf = convert_input(data, data->input, data->buf, &i);
		if (!data->input[i])
			break;
	}
	add_cmd(data);
	return (0);
}
