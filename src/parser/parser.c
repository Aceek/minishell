/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/12/07 18:30:45 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_cmd(t_data *data)
{
	data->buf = create_buffer();
	if (!data->buf)
		return (free_all_exit(data), 1);
	data->curr_fd_in = 0;
	data->curr_fd_out = 1;
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
		return (free_all_exit(data), 1);
	ft_memset(cmd, 0, sizeof(t_cmd));
	cmd->tab = ft_split_parser(data->buf);
	cmd->fd_in = data->curr_fd_in;
	cmd->fd_out = data->curr_fd_out;
	cmd->builtin = get_builtin_code(cmd->tab[0]); 
	cmd->head_cmd = data->head_cmd;
	cmd->env = data->env;
	ft_list_add_back(&data->head_cmd, cmd);
	return (0);
}

char	*fill_buf_char(t_data *data, char *buf, char c)
{
	char	*tmp;
	
	tmp = ft_charjoin(buf, c);
	if(!tmp)
		return (free_all_exit(data), NULL);
	free(buf);
	buf = tmp;
	return (buf);
}

char	*convert_input(t_data *data, char *buf, char *str, int *i)
{
	char	*var;
	char	*tmp;

	if (str[*i] == '$' && check_quote_pos(str, *i) != 1)
	{
		if (!ft_isalnum(str[*i + 1]) && str[*i + 1] != '_' && str[*i + 1] != '?')
			return (fill_buf_char(data, buf, str[*i]));
		var = get_dollar(str, i, data->mini);
		if (!var)
			return (free(var), buf);
		tmp = ft_strjoin(buf, var);
		if(!tmp)
			return (free_all_exit(data), NULL);
		free(buf);
		free(var);
		buf = tmp;
	}
	else
		buf = fill_buf_char(data, buf, str[*i]);
	return (buf);
}

int	parse_input(t_data *data)
{
	int		i;

	if (check_quote_error(data->input))
	{
		write(2, "minishell : quotes not closing error\n", 37);
		return (1);
	}
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
		if (!data->input[i])
			break ;
	}
	add_cmd(data);
	free(data->buf);
	return (0);
}
