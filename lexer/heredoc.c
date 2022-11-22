/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/11/20 05:40:07 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*convert_hd_input(t_data *data, char *input)
{
	(void)data;
	return (input);
}

void	get_hd_input(t_data *data, char *end)
{
	char	*input;

	input = readline("heredoc> ");
	if (!input)
	{
		//msg derreur
		close(data->curr_fd_in);
		free(input);
		//exit clean
		return ;
	}
	if (ft_strcmp(input, end))
	{
		close(data->curr_fd_in);
		free(input);
		//exit clean
		return ;
	}
	input = convert_hd_input(data, input);
	printf("input: %s\n", input);
	ft_putstr_fd(input, data->curr_fd_in);
	ft_putchar_fd('\n', data->curr_fd_in);
	free(input);
}

 int	heredoc(t_data *data, char *end)
 {
	pid_t	pid;
	int		status;
	
	data->hd_path = "/tmp/.x";
	data->curr_fd_in = open(data->hd_path , O_CREAT | O_RDWR | O_TRUNC, 0664);
	
	pid = fork();
	if (pid < 0)
		return (close(data->curr_fd_in), - 1);
	if (pid == 0)
	{
		while (1)
		{
			signal(SIGINT, SIG_DFL);
			get_hd_input(data, end);
		}
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		close(data->curr_fd_in);
		open(data->hd_path, O_RDWR);
		return (0);
	}
	close(data->curr_fd_in);
	return (-1);
 }