/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
/*   Updated: 2022/11/19 03:36:05 by pbeheyt          ###   ########.fr       */
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

int	get_file_len(char *str, int i)
{
	int var_len;
	
	var_len = 0;
	while ((ft_isalnum(str[i]) || str[i] == '_' || str[i] == '.'))
	{	
		var_len += 1;
		i++;
	}
	return (var_len);
}


int	redir_handler(t_data *data, char *str, int *i)
{
	int		file_len;
	char	*file_name;

	file_len = get_file_len(str, *i);
	file_name = ft_strncpy_from(str, *i ,file_len);
	*i += file_len;
	if (data->curr_token == LESS && file_name)
	{
		data->curr_fd_in = open(file_name, O_RDWR);
		if (data->curr_fd_in == -1)
			return (1);
	}
	if (data->curr_token == GREAT && file_name)
		data->curr_fd_out = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0664);
	// if (data->curr_token == DLESS && file_name)
	// 	cmd->fd_in = heredoc();
	if (data->curr_token == DGREAT && file_name)
		data->curr_fd_out = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0664);
	
}

