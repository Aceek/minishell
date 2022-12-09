/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/12/09 01:56:24 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_redir_arg(t_data *data, char *str, int *i)
{
	char	*buf;

	buf = create_buffer();
	if (!buf)
		return (free_all_exit(data, 1), NULL);
	while (ft_isspace(str[*i]))
		*i += 1;
	while (ft_isalnum(str[*i]) || str[*i] == '_' || str[*i] == '.'
		|| str[*i] == '$')
	{
		if (data->token == DLESS)
			buf = add_char(data, buf, str[*i]);
		else
			buf = convert_input(data, buf, str, i);
	*i += 1;
	}
	return (buf);
}

int	redir_handler(t_data *data, char *str, int *i)
{
	data->redir_arg = get_redir_arg(data, str, i);
	if (!data->redir_arg)
		return (1);
	if (data->token == LESS)
		data->fd_in = open(data->redir_arg, O_RDWR);
	if (data->token == GREAT)
		data->fd_out = open(data->redir_arg, O_CREAT | O_RDWR | O_TRUNC, 0664);
	if (data->token == DLESS)
	{
		data->fd_in = heredoc(data, data->redir_arg);
		free(data->path);
	}
	if (data->token == DGREAT)
		data->fd_out = open(data->redir_arg, O_CREAT | O_RDWR | O_APPEND, 0664);
	if (data->fd_in == -1 || data->fd_out == -1)
	{
		data->error = 1;
		g_exit = 1;
		write(2, "minishell : ", 12);
		write(2, data->redir_arg, ft_strlen(data->redir_arg));
		write(2, ": No such file or directory\n", 28);
		return (free(data->redir_arg), 1);
	}
	return (free(data->redir_arg), 0);
}
