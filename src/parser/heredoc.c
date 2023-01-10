/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/01/10 22:32:56 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*convert_hd_input(t_data *data, char *input)
{
	char	*buf;
	int		i;

	buf = create_buffer();
	if (!buf)
		return (free_all_exit(data, 1), NULL);
	i = -1;
	while (input[++i])
			buf = convert_input(data, buf, input, &i);
	free(input);
	return (buf);
}

void	get_hd_input(t_data *data, int fd, char *end)
{
	char	*input;

	input = readline("heredoc> ");
	if (!input)
	{
		write(2, "minishell : warning : heredoc delimited by end-of-file\n", 55);
		close(fd);
		free(input);
		free(end);
		free(data->path);
		ft_exit_clean(data->mini, data->head_cmd, 1);
	}
	if (!ft_strcmp(input, end))
	{
		close(fd);
		free(input);
		free(end);
		free(data->path);
		ft_exit_clean(data->mini, data->head_cmd, 0);
	}
	input = convert_hd_input(data, input);
	ft_putstr_fd(input, fd);
	ft_putchar_fd('\n', fd);
	free(input);
}

char	*get_hd_path(t_data *data)
{
	char	*nb_hd;
	char	*path;

	nb_hd = ft_itoa(++data->nb_hd);
	if (!nb_hd)
		return (free_all_exit(data, 1), NULL);
	path = ft_strjoin("/tmp/.hd", nb_hd);
	free(nb_hd);
	if (!path)
		return (free_all_exit(data, 1), NULL);
	return (path);
}

int	heredoc(t_data *data, char *end)
{
	pid_t	pid;
	int		status;
	int		fd;

	data->path = get_hd_path(data);
	fd = open(data->path, O_CREAT | O_RDWR | O_TRUNC, 0664);
	if (data->fd_in < 0)
		return (-1);
	pid = fork();
	if (pid < 0)
		return (close(fd), -1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		free(data->buf);
		while (1)
			get_hd_input(data, fd, end);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		close(fd);
		return (open(data->path, O_RDWR));
	}
	return (close(fd), -1);
}
