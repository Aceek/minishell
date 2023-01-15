/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_cleaning.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 06:07:26 by ilinhard          #+#    #+#             */
/*   Updated: 2023/01/15 22:36:26 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_verify_errno(t_cmd *cmd)
{
	if (cmd->tab[0][0] != '.' && cmd->tab[0][0] != '/')
		return ;
	ft_exec_err(cmd->tab[0], " : ");
	ft_exec_err(strerror(errno), "\n");
	g_exit = 126;
}

void	ft_clear_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
	if (tab)
		free(tab);
}

void	ft_clear_fd(t_cmd *cmd)
{
	if (cmd->fd_in > 0)
		close (cmd->fd_in);
	if (cmd->fd_out > 1)
		close (cmd->fd_out);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
		ptr[i++] = c;
	return (s);
}
