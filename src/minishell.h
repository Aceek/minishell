/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:00:22 by pbeheyt           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/11/24 05:03:37 by pbeheyt          ###   ########.fr       */
=======
/*   Updated: 2022/11/24 05:24:21 by ilinhard         ###   ########.fr       */
>>>>>>> exec
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <stdbool.h>

enum e_token
{
	NOT_TOKEN,
	PIPE,
	LESS,
	GREAT,
	DLESS,
	DGREAT,
};

enum e_built_in
{
	NOT_BUILT_IN,
	ECH,
	PWD,
	CD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
};

typedef struct s_env
{
	char			*line;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char			**tab; // data->new_args
	char			**env; // Il faut que tu init chaque elem de la list
	int				fd_in;
	int				fd_out;
	int				builtin; // data->code
	struct s_cmd	*head_cmd; // transofemer en head_cmd
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_data
{
	char			**env;
	t_env			*mini;
	char			*input;
	int				curr_token;
	int				curr_fd_in;
	int				curr_fd_out;
	char			*hd_path;
	int				error;
	struct s_cmd	*head_cmd;
}					t_data;

/*libft1*/
size_t	ft_strlen(const char *str);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
int		ft_strchr(const char *str, int c);
char	*ft_strjoin(char *s1, char *s2);

/*libft2*/
char	*ft_charjoin(char *s1, char c);
int		ft_isalnum(int c);
int		ft_isspace(int c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, int n);

/*libft3*/
char	*ft_strnstr(const char *s1, const char *to_find, size_t n);
char	*ft_cpy(char *src, int skip);
char	*ft_strdup(char *s);
t_cmd	*ft_get_list_last(t_cmd *list);
void	ft_list_add_back(t_cmd **list, t_cmd *new);

/*libft4*/
void	ft_listclear(t_cmd **list);
void	*ft_memset(void *s, int c, size_t n);

/*libft5*/
char	**ft_split(char *s);

/*env*/
int		get_var_len(char *str, int i);
char	*get_var_val(char *var_name, int var_len, char **env);
char	*dollar_handler(char *str, int *i, char **env);

/*lexer*/
void	update_quote(bool *quote);
int		check_quote_error(char *str);
int		check_quote_pos(char *str, int pos);
int		check_token(char *str, int *i);
int		check_built_in(char *str);

/*parser*/
int		add_cmd(t_data *data, char *str);
char	*create_buffer(void);
int		parse_input(t_data *data);

/*redir*/
char	*convert_hd_input(t_data *data, char *input);
void	get_hd_input(t_data *data, char *end);
int		heredoc(t_data *data, char *end);
char	*get_token_arg(char *str, int *i);
int		redir_handler(t_data *data, char *str, int *i);

/*---------------------------------------NEW---------------------------------*/
int	ft_cmd(t_cmd *cmd, t_env *mini);
void	free_tab(char **av);
char	*ft_make_path(char *dir, char *cmd);
char	*ft_get_path(char *cmd, char **env);
char	*ft_strnstr(const char *s1, const char *to_find, size_t n);
int		ft_error(int error);
char	**ft_split2(char const *s, char c);
void	ft_exe(t_env *mini, t_cmd *cmd);
int		ft_isalnun(char c);
int		ft_isdigit(char c);
char 	**ft_make_tab_from_env(t_env *mini);
void	ft_exit_clean(t_env *mini, t_cmd *cmd);
int		ft_lst_count(t_env *env);
char	*ft_cpy(char *src, int skip);
void	ft_builtin(t_cmd *cmd, t_env *mini);
int		ft_is_valid_env(char *args);
int		ft_export_error(int error, char *args);
int		ft_is_in_env(t_env *mini, char *args);
void	ft_print_env(t_env *mini, int mod);
void	ft_export_builtin(t_cmd *cmd, t_env *mini);
void	ft_add_args_env(t_cmd *cmd, t_env *mini);
void	ft_add_list_env(t_env *mini, char *args);
char	*ft_cpy_env_name(char *args);
void	ft_sort_print_env(t_env *mini);
void	ft_echo_builtin(t_cmd *cmd);
void	ft_pwd_builtin(void);
void	ft_unset_builtin(t_cmd *cmd, t_env *mini);
void	ft_remove_list(t_env *old, t_env *tmp);
void	ft_cd_builtind(t_cmd *cmd, t_env *mini);
t_env	*ft_cpy_env(t_env *mini);
int		lst_addback(t_env *mini_env, char *env);
int		ft_isalnun_tmp(char c);
void	lst_freeall(t_env *mini_env);
void	ft_clear_cmd_list(t_cmd *cmd);
void	ft_signal_newline(int unused);

#endif