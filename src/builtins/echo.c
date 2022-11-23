/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 22:49:44 by ilinhard          #+#    #+#             */
/*   Updated: 2022/11/23 01:51:17 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo_builtin(t_cmd *cmd)
{
	int	n_option;
	int	i;

	n_option = 0;
	if (cmd->tab[1] && !ft_strcmp(cmd->tab[1], "-n"))
		n_option = 1;
	i = 1 + n_option;
	while (cmd->tab && cmd->tab[i])
	{
		printf("%s", cmd->tab[i]);
		if (cmd->tab[i + 1] && cmd->tab[i][0] != '\0')
			printf(" ");
		i++;
	}
	if (!n_option)
		printf("\n");
}
