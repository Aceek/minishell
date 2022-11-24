/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/11/24 06:53:01 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*convert_hd_input(t_data *data, char *input)
{
	char	*buf;
	int		i;

	buf = create_buffer();
	if (!buf)
		return (NULL);
	i = -1;
	while (input[++i])
		buf = convert_input(data, input, buf, &i);
	return (buf);
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
		ft_exit_clean(data->mini ,data->head_cmd);
		return ;
	}
	if (!ft_strcmp(input, end))
	{
		close(data->curr_fd_in);
		free(input);
		ft_exit_clean(data->mini ,data->head_cmd);
		return ;
	}
	input = convert_hd_input(data, input);
	ft_putstr_fd(input, data->curr_fd_in);
	ft_putchar_fd('\n', data->curr_fd_in);
	free(input);
}

int	heredoc(t_data *data, char *end)
{
	pid_t	pid;
	int		status;

	data->hd_path = "/tmp/.x";
	data->curr_fd_in = open(data->hd_path, O_CREAT | O_RDWR | O_TRUNC, 0664);
	pid = fork();
	if (pid < 0)
		return (close(data->curr_fd_in), -1);
	if (pid == 0)
	{
		while (1)
		{
			signal(SIGINT, SIG_DFL);
			get_hd_input(data, end);
		}
		ft_exit_clean(data->mini, data->head_cmd);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		close(data->curr_fd_in);
		return (open(data->hd_path, O_RDWR));
	}
	close(data->curr_fd_in);
	return (-1);
}

char	*get_token_arg(char *str, int *i)
{
	char	*arg;
	char	*tmp;

	arg = create_buffer();
	if (!arg)
		return (NULL);
	while (ft_isspace(str[*i]))
		*i += 1;
	while (ft_isalnum(str[*i]) || str[*i] == '_')
	{
		tmp = ft_charjoin(arg, str[*i]);
		free(arg);
		arg = tmp;
		*i += 1;
	}
	return (arg);
}

int	redir_handler(t_data *data, char *str, int *i)
{
	char	*arg;

	arg = get_token_arg(str, i);
	if (!arg)
		return (1);
	if (data->curr_token == LESS && arg)
		data->curr_fd_in = open(arg, O_RDWR);
	if (data->curr_token == GREAT && arg)
		data->curr_fd_out = open(arg, O_CREAT | O_RDWR | O_TRUNC, 0664);
	if (data->curr_token == DLESS && arg)
		data->curr_fd_in = heredoc(data, arg);
	if (data->curr_token == DGREAT && arg)
		data->curr_fd_out = open(arg, O_CREAT | O_RDWR | O_APPEND, 0664);
	if (data->curr_fd_in == -1 || data->curr_fd_out == -1)
		return (1);
	return (0);
}
