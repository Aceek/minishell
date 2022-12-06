/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/12/06 06:23:33 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_all_exit(t_data *data)
{
	if (data->buf)
		free(data->buf);
	if (data->token_arg)
		free(data->token_arg);
	if (data->curr_path)
		free(data->curr_path);
	ft_exit_clean(data->mini, data->head_cmd, 1);
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
	cmd->tab = ft_split2(data->buf, " \f\n\r\t\v");
	cmd->fd_in = data->curr_fd_in;
	cmd->fd_out = data->curr_fd_out;
	cmd->builtin = get_builtin_code(cmd->tab[0]);
	cmd->head_cmd = data->head_cmd;
	cmd->env = data->env;
	ft_list_add_back(&data->head_cmd, cmd);
	return (0);
}

int	check_token(t_data *data, int *i)
{
	data->curr_token = get_token_code(data->input, i);
	if (data->curr_token && check_token_error(data->input, i))
	{
		write(2, "minishell : syntax error near unexpected token\n", 47);
		data->error = 1;
		return (0);
	}
	if (data->curr_token == PIPE && check_quote_pos(data->input, *i) == 0)
		return (1);
	if (data->curr_token > PIPE && check_quote_pos(data->input, *i) == 0)
		redir_handler(data, data->input, i);
	return (0);
}

// char	*fill_buf_str(t_data *data, char *buf, char *s1, char s2)
// {
// 	char	*tmp;
	
// 	return (buf);
// }

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
		if (!(str[*i + 1] || ft_isalnum(str[*i + 1])))
			return (fill_buf_char(data, buf, str[*i]));
		// if (!str[*i + 1])
		// 	return (buf);
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
	else if (!((str[*i] == '\'' || str[*i] == '\"') 
				&& check_quote_pos(str, *i) == 0))
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
