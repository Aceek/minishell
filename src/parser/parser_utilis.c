/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utilis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/12/07 18:30:34 by pbeheyt          ###   ########.fr       */
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
