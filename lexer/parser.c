/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/11/20 05:31:07 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	check_built_in(char *str)
{
	if (!str)
		return (NOT_BUILT_IN);
	if (ft_strncmp(str, "echo", ft_strlen("echo")))
		return (ECH);
	if (ft_strncmp(str, "cd", ft_strlen("cd")))
		return (CD);
	if (ft_strncmp(str, "export", ft_strlen("export")))
		return (EXPORT);
	if (ft_strncmp(str, "unset", ft_strlen("unset")))
		return (UNSET);
	if (ft_strncmp(str, "env", ft_strlen("env")))
		return (ENV);
	if (ft_strncmp(str, "exit", ft_strlen("exit")))
		return (EXIT);
	return (NOT_BUILT_IN);
}

int	add_cmd(t_data *data, char *buffer)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (1);
	ft_memset(cmd, 0, sizeof(t_cmd));
	cmd->tab = ft_split(buffer);
	free(buffer);
	cmd->fd_in = data->curr_fd_in;
	cmd->fd_out = data->curr_fd_out;
	cmd->built_in = check_built_in(cmd->tab[0]);
	cmd->token = data->curr_token;
	cmd->list_cmd = data->list_cmd;
	ft_list_add_back(&data->list_cmd, cmd);
	return (0);
}

char *create_buffer(t_data *data)
{
	char *buffer;
	
	buffer = malloc(sizeof(char));
	if (!buffer)
	{
		data->error = 1;
		return (NULL);
	}
	buffer[0] = 0;
	return (buffer);
}

char *get_token_arg(t_data *data, char *str, int *i)
{
	char *arg;
	
	arg = create_buffer(data);
	while (ft_isspace(str[*i]))
		*i += 1;
	while (ft_isalnum(str[*i]) || str[*i] == '_')
	{
		arg = ft_charjoin(arg, str[*i]);
		*i += 1;
	}
	return (arg);
}

int	redir_handler(t_data *data, char *str, int *i)
{
	char	*arg;

	arg = get_token_arg(data, str, i);
	printf("arg : %s\n", arg);
	if (data->curr_token == LESS && arg)
	{
		data->curr_fd_in = open(arg, O_RDWR);
		if (data->curr_fd_in == -1)
			return (1);
	}
	if (data->curr_token == GREAT && arg)
		data->curr_fd_out = open(arg, O_CREAT | O_RDWR | O_TRUNC, 0664);
	if (data->curr_token == DLESS && arg)
		data->curr_fd_in = heredoc(data, arg);
	if (data->curr_token == DGREAT && arg)
		data->curr_fd_out = open(arg, O_CREAT | O_RDWR | O_APPEND, 0664);
	return (0);
}

void	parse_input(t_data *data)
{
	int		i;
	char	*buffer;
	
	buffer = create_buffer(data);
	i = -1;
	while (data->input[++i])
	{
		data->curr_token = check_token(data->input, &i);	
		if (data->curr_token == PIPE)
		{
			add_cmd(data, buffer);
			buffer = create_buffer(data);
		}
		else if (data->curr_token > PIPE)
			redir_handler(data, data->input, &i);
		else if (data->input[i] == '$' && check_quote_pos(data->input, i) != 1)
			buffer = ft_strjoin(buffer, dollar_handler(data->input, &i, data->env));
		else
			buffer = ft_charjoin(buffer, data->input[i]);
	}
	add_cmd(data, buffer);
}


