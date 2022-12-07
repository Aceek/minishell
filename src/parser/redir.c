/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/12/07 18:33:38 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_token_arg(t_data *data, char *str, int *i)
{
	char	*arg;

	arg = create_buffer();
	if (!arg)
		return (NULL);
	while (ft_isspace(str[*i]))
		*i += 1;
	while (ft_isalnum(str[*i]) || str[*i] == '_' || str[*i] == '.')
	{
		arg = convert_input(data, arg, str, i);
		*i += 1;
	}
	return (arg);
}

int	redir_handler(t_data *data, char *str, int *i)
{
	data->token_arg = get_token_arg(data, str, i);
	if (!data->token_arg)
		return (1);
	if (data->curr_token == LESS && data->token_arg)
		data->curr_fd_in = open(data->token_arg, O_RDWR);
	if (data->curr_token == GREAT && data->token_arg)
		data->curr_fd_out = open(data->token_arg, O_CREAT | O_RDWR | O_TRUNC, 0664);
	if (data->curr_token == DLESS && data->token_arg)
		data->curr_fd_in = heredoc(data, data->token_arg);
	if (data->curr_token == DGREAT && data->token_arg)
		data->curr_fd_out = open(data->token_arg, O_CREAT | O_RDWR | O_APPEND, 0664);
	if (data->curr_fd_in == -1 || data->curr_fd_out == -1)
	{
		data->error = 1;
		g_exit = 1;
        write(2, "minishell : ", 12);
		write(2, data->token_arg, ft_strlen(data->token_arg));
        write(2, ": No such file or directory\n", 28);
		free(data->token_arg);
		return (1);
	}
	free(data->curr_path);
	free(data->token_arg);
	return (0);
}
