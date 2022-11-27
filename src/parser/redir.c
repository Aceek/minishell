/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/11/27 02:06:11 by pbeheyt          ###   ########.fr       */
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
		ft_exit_clean(data->mini ,data->head_cmd, 1);
	}
	if (!ft_strcmp(input, end))
	{
		close(data->curr_fd_in);
		free(input);
		ft_exit_clean(data->mini ,data->head_cmd, 0);
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
	if (data->curr_fd_in < 0 )
		return (-1);
	pid = fork();
	if (pid < 0)
		return (close(data->curr_fd_in), -1);
	if (pid == 0)
	{
		signal(SIGINT, exit);
		while (1)
			get_hd_input(data, end);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		g_exit = WEXITSTATUS(status);
		if (g_exit)
		{
			printf("error here doc\n");
			close(data->curr_fd_in);
			free(end);
			return (-1);
		}
	}
	return (free(end), data->curr_fd_in);
}

char	*get_token_arg(char *str, int *i)
{
	char	*arg;
	char	*tmp;
	int 	j;

	arg = create_buffer();
	if (!arg)
		return (NULL);
	j = *i;
	while (ft_isspace(str[j]))
		j += 1;
	while (ft_isalnum(str[j]) || str[j] == '_')
	{
		tmp = ft_charjoin(arg, str[j]);
		free(arg);
		arg = tmp;
		j += 1;
	}
	if (j > *i)
		*i = j - 1;
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
	{
		data->error = 1;
		g_exit = 1;
        write(2, "minishell : ", 12);
		write(2, arg, ft_strlen(arg));
        write(2, " : No such file or directory\n", 29);
		free(arg);
		return (1);
	}
	free(arg);
	return (0);
}
