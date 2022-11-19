/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:06:18 by rben-tkh          #+#    #+#             */
/*   Updated: 2022/11/19 05:01:25 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_ecode = 0;

char	**fuse(char *cmd, char **args)
{
	int		i;
	char	**all;

	i = 0;
	while (args && args[i])
		i++;
	all = malloc(sizeof(char *) * (i + 2));
	if (!all)
		return (NULL);
	i = 1;
	all[0] = ft_strdup(cmd);
	while (args && args[i - 1])
	{
		all[i] = ft_strdup(args[i - 1]);
		i++;
	}
	all[i] = 0;
	return (all);
}

void	shlvl(t_env *mini)
{
	int	i;

	while (mini)
	{
		if (!ft_strncmp(mini->line, "SHLVL=", 6))
		{
			i = ft_strlen(mini->line);
			mini->line[i - 1]++;
			break ;
		}
		mini = mini->next;
	}
}

t_env	*ft_env(char **env)
{
	t_env	*mini_env;
	int		i;

	i = 1;
	mini_env = malloc(sizeof(t_env));
	if (!mini_env)
		return (NULL);
	if (!env[0])
		return (mini_env->line = NULL, mini_env->next = NULL, mini_env);
	mini_env->line = ft_strdup(env[0]);
	if (!mini_env->line)
		return (free(mini_env), NULL);
	mini_env->next = NULL;
	while (env[i])
	{
		if (!lst_addback(mini_env, env[i]))
			return (lst_freeall(mini_env), NULL);
		i++;
	}
	shlvl(mini_env);
	return (mini_env);
}

static int	joseph(char **args)
{
	int	i;
	int	j;
	int	d;
	int	y;

	i = -1;
	while (args[++i])
	{
		j = 0;
		while (args[i][j])
			j++;
		d = ft_atoi(args[i], &y);
		if (y < j)
		{
			write(2, "minihlel: exit: ", 16);
			if (!i)
				return (write(2, "numeric argument required\n", 26), 2);
			else
				return (write(2, "too many arguments\n", 19), -672);
		}
		if (i > 0)
			return (write(2, "minihlel: exit: too many arguments\n", 35), -672);
	}
	return (d);
}

void	ft_exit(t_data *data, t_env *mini, t_env *origin, char **args)
{
	int	a;

	a = 0;
	if (args)
	{
		a = joseph(args);
		if (a == -672)
			return ;
		g_ecode = a;
	}
	if (data && data->exit)
		printf("exit\n");
	lst_freeall(mini);
	lst_freeall(origin);
	ft_free(0, &data);
	exit(g_ecode);
}

void	signal_int(int unused)
{
	(void)unused;
	rl_on_new_line();
	write(2, "\n", 1);
	rl_replace_line("", 0);
	if (g_ecode > 0)
		rl_redisplay();
	g_ecode = 130;
}

void	signal_quit(int unused)
{
	(void)unused;
	write(2, "Quit (code dumped)\n", 19);
	g_ecode = 131;
}

void	signal_irdouk(char *str)
{
	write(2, "minihlel: warning: ", 19);
	write(2, "ir-doukoumen delimited by end-of-file", 37);
	if (str)
	{
		write(2, " (wanted `", 10);
		write(2, str, ft_strlen(str));
		write(2, "')\n", 3);
	}
	g_ecode = 0;
}


void	minishell(char **env, t_env *mini, t_env *origin, char *str)
{
	t_input	input;
	t_data	*data;
	t_data	*tmp;
	int		i;

	if (!str)
		return ;
	i = 0;
	while (str && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str && str[i])
	{
		input.s1 = ft_strdup(str);
		input.s2 = 0;
		free(str);
		data = check_errors(&input, mini);
		init_cmdset(&data, mini, origin);
		tmp = data;
		while (tmp)
		{
			tmp->new_args = fuse(tmp->cmd, tmp->args);
			tmp->env = env;
			tmp = tmp->next;
		}
		tmp = data;

		if (data)
			ft_exe(mini, origin, data);
		// exec_loop(mini, origin, data);
		ft_free(0, &data);
	}
}

int	main(int ac, char **av, char **env)
{
	t_env	*mini;
	t_env	*origin;
	char	*str;

	origin = ft_env(env);
	mini = ft_env(env);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_int);
	while (ac > 0 && av[0])
	{
		str = readline("minishell> ");
		if (!str)
		{
			printf("exit\n");
			free(str);
			ft_exit(0, mini, origin, 0);
		}
		else if (str && str[0])
		{
			add_history(str);
			minishell(env, mini, origin, str);
		}
	}
	return (lst_freeall(origin), lst_freeall(mini), 0);
}
