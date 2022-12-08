/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 22:49:44 by ilinhard          #+#    #+#             */
/*   Updated: 2022/12/09 00:54:44 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_strcmp_n(char *s1)
{
	int	i;

	i = 1;
	if (s1[0] != '-')
		return (1);
	while (s1 && s1[i])
	{
		if (s1[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	ft_echo_builtin(t_cmd *cmd)
{
	int	n_option;
	int	i;

	n_option = 0;
	while (cmd->tab[n_option + 1] && !ft_strcmp_n(cmd->tab[n_option + 1]))
		n_option++;
	i = 1 + n_option;
	while (cmd->tab && cmd->tab[i])
	{
		write(1, cmd->tab[i], ft_strlen(cmd->tab[i]));
		if (cmd->tab[i + 1] && cmd->tab[i][0] != '\0')
			write(1, " ", 1);
		i++;
	}
	if (!n_option)
		write(1, "\n", 1);
}
