/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/01/14 01:03:10 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_redir_arg(t_data *data, char *str, int *i)
{
	char	*buf;
	char	*dup;

	*i += 1;
	buf = create_buffer();
	if (!buf)
		return (free_all_exit(data, 1), NULL);
	while (str[*i] && is_del(str, *i))
		*i += 1;
	while (str[*i] && !is_del(str, *i) && !is_token(str, *i))
	{
		if (data->token == DLESS)
			buf = add_char(data, buf, str[*i]);
		else
			buf = convert_input(data, buf, str, i);
	*i += 1;
	}
	if (is_token(str, *i) || !str[*i])
		*i -= 1;
	dup = ft_strdup(buf);
	dup = cpy_no_quotes(dup, buf, 0, ft_strlen(dup));
	free(buf);
	return (dup);
}

void	print_fd_error(t_data *data)
{
	write(2, "minishell : ", 12);
	write(2, data->redir_arg, ft_strlen(data->redir_arg));
	write(2, ": No such file or directory\n", 28);
}

void	fd_error(t_data *data)
{
	data->file_error = 1;
	g_exit = 1;
	free(data->redir_arg);
	free(data->buf);
	data->buf = create_buffer();
	if (!data->buf)
		free_all_exit(data, 1);
}

int	redir_handler(t_data *data, char *str, int *i)
{
	data->buf = add_char(data, data->buf, ' ');
	data->redir_arg = get_redir_arg(data, str, i);
	if (!data->redir_arg)
		return (1);
	if (data->fd_in > 0)
		close(data->fd_in);
	if (data->fd_out > 1)
		close(data->fd_out);
	if (data->token == LESS)
		data->fd_in = open(data->redir_arg, O_RDWR);
	else if (data->token == GREAT)
		data->fd_out = open(data->redir_arg, O_CREAT | O_RDWR | O_TRUNC, 0664);
	else if (data->token == DLESS)
	{
		data->fd_in = heredoc(data, data->redir_arg);
		free(data->path);
		if (data->fd_in == -1)
			return (fd_error(data), 1);
	}
	else if (data->token == DGREAT)
		data->fd_out = open(data->redir_arg, O_CREAT | O_RDWR | O_APPEND, 0664);
	if (data->fd_in == -1 || data->fd_out == -1)
		return (print_fd_error(data), fd_error(data), 1);
	return (free(data->redir_arg), 0);
}
