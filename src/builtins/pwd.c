/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 23:45:23 by ilinhard          #+#    #+#             */
/*   Updated: 2023/01/14 02:18:43 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd_builtin(t_cmd *cmd)
{
	char	buff[2048];

	if (cmd->tab[1] && cmd->tab[1][0] == '-')
	{
		printf("%s : invalid option\n", cmd->tab[1]);
		return (g_exit = 1, 1);
	}
	if (getcwd(buff, 2048) != NULL)
		printf("%s\n", buff);
	else
		g_exit = 1;
	return (g_exit);
}
