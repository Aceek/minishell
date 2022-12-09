/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 23:45:23 by ilinhard          #+#    #+#             */
/*   Updated: 2022/11/26 02:13:40 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd_builtin(void)
{
	char	buff[2048];

	if (getcwd(buff, 2048) != NULL)
		printf("%s\n", buff);
	else
		g_exit = 1;
	return (g_exit);
}
