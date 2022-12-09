/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/12/09 02:55:02 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tab(char **tab)
{	
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free (tab);
}

void	free_all_exit(t_data *data, int exit)
{
	if (data->buf)
		free(data->buf);
	if (data->redir_arg)
		free(data->redir_arg);
	if (data->path)
		free(data->path);
	ft_exit_clean(data->mini, data->head_cmd, exit);
}
