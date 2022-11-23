/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/11/23 03:46:29 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_cmd(t_data *data, char *buffer)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (1);
	ft_memset(cmd, 0, sizeof(t_cmd));
	cmd->tab = ft_split(buffer);
	free(buffer);
	cmd->fd_in = data->curr_fd_in;
	cmd->fd_out = data->curr_fd_out;
	cmd->builtin = check_built_in(cmd->tab[0]);
	cmd->head_cmd = data->head_cmd;
	cmd->env = data->env;
	ft_list_add_back(&data->head_cmd, cmd);
	return (0);
}

char	*create_buffer(void)
{
	char	*buffer;

	buffer = malloc(sizeof(char));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	return (buffer);
}

int	parse_input(t_data *data)
{
	int		i;
	char	*buf;

	if (check_quote_error(data->input))
		return (printf("quote error\n"), 1);
	buf = create_buffer();
	if (!buf)
		return (1);
	i = -1;
	while (data->input[++i])
	{
		data->curr_token = check_token(data->input, &i);
		if (data->curr_token == PIPE)
		{
			add_cmd(data, buf);
			buf = create_buffer();
			if (!buf)
				return (1);
		}
		else if (data->curr_token > PIPE)
			redir_handler(data, data->input, &i);
		else if (data->input[i] == '$' && check_quote_pos(data->input, i) != 1)
			buf = ft_strjoin(buf, dollar_handler(data->input, &i, data->env));
		else
			buf = ft_charjoin(buf, data->input[i]);
	}
	add_cmd(data, buf);
	return (0);
}
