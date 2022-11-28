/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/11/28 10:12:34 by pbeheyt          ###   ########.fr       */
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

void	get_hd_input(t_data *data, int fd, char *end)
{
	char	*input;

	input = readline("heredoc> ");
	if (!input)
	{
		//msg derreur
		close(fd);
		free(input);
		free(end);
		free(data->curr_path);
		ft_exit_clean(data->mini ,data->head_cmd, 1);
	}
	if (!ft_strcmp(input, end))
	{
		close(fd);
		free(input);
		free(end);
		free(data->curr_path);
		ft_exit_clean(data->mini ,data->head_cmd, 0);
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
		return (free_all_exit(data), NULL);
	path = ft_strjoin("/tmp/.hd", nb_hd);
	free(nb_hd);
	if (!path)
		return (free_all_exit(data), NULL);
	return (path);
}

int	heredoc(t_data *data, char *end)
{
	pid_t	pid;
	int		status;
	int		fd;
	
	data->curr_path = get_hd_path(data);
	fd = open(data->curr_path, O_CREAT | O_RDWR | O_TRUNC, 0664);
	if (data->curr_fd_in < 0 )
		return (-1);
	pid = fork();
	if (pid < 0)
		return (close(fd), -1);
	if (pid == 0)
	{
		signal(SIGINT, exit);
		free(data->buf);
		while (1)
			get_hd_input(data, fd, end);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		close(fd);
		return (open(data->curr_path, O_RDWR));
	}
	return (close(fd), -1);
	// if (WIFEXITED(status))
	// {
	// 	g_exit = WEXITSTATUS(status);
	// 	if (g_exit)
	// 	{
	// 		printf("error here doc\n");
	// 		close(fd);
	// 		return (-1);
	// 	}
	// }
	// return (fd);
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
	data->token_arg = get_token_arg(str, i);
	if (!data->token_arg)
		return (1);
	if (data->curr_token == LESS && data->token_arg)
		data->curr_fd_in = open(data->token_arg, O_RDWR);
	if (data->curr_token == GREAT && data->token_arg)
		data->curr_fd_out = open(data->token_arg, O_CREAT | O_RDWR | O_TRUNC, 0664);
	if (data->curr_token == DLESS && data->token_arg)
		data->curr_fd_in = heredoc(data, data->token_arg);
	if (data->curr_token == DGREAT && data->token_arg)
		data->curr_fd_out = open(data->token_arg, O_CREAT | O_RDWR | O_APPEND, 0664);
	if (data->curr_fd_in == -1 || data->curr_fd_out == -1)
	{
		data->error = 1;
		g_exit = 1;
        write(2, "minishell : ", 12);
		write(2, data->token_arg, ft_strlen(data->token_arg));
        write(2, ": No such file or directory\n", 28);
		free(data->token_arg);
		return (1);
	}
	free(data->curr_path);
	free(data->token_arg);
	return (0);
}
