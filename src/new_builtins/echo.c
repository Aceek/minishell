/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 22:49:44 by ilinhard          #+#    #+#             */
/*   Updated: 2022/11/16 06:48:26 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo_builtin(t_data *data)
{
	int	n_option;
	int	i;

	n_option = 0;
	if (data->new_args[1] && !ft_strcmp(data->new_args[1], "-n"))
		n_option = 1;
	i = 1 + n_option;
	while (data->new_args && data->new_args[i])
	{
		printf("%s", data->new_args[i]);
		if (data->new_args[i + 1] && data->new_args[i][0] != '\0')
			printf(" ");
		i++;
	}
	if (!n_option)
		printf("\n");
}
