/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 01:02:11 by ilinhard          #+#    #+#             */
/*   Updated: 2022/12/09 23:08:41 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signal_newline(int unused)
{
	(void)unused;
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit = 130;
}

void	ft_signal_quit(int unused)
{
	(void)unused;
	write(2, "Quit (core dumped)\n", 19);
	g_exit = 131;
}

void	ft_signal_newline2(int unused)
{
	(void)unused;
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	g_exit = 130;
}
