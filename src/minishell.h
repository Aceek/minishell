/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 05:31:37 by ilinhard          #+#    #+#             */
/*   Updated: 2022/11/27 06:25:42 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

extern int	g_exit;

typedef struct s_env
{
	char			*line;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char			**tab;
	char			**env;
	int				fd_in;
	int				fd_out;
	int				builtin;
	struct s_cmd	*head_cmd;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_data
{
	char			**env;
	t_env			*mini;
	char			*input;
	char			*buf;
	int				curr_token;
	int				curr_fd_in;
	int				curr_fd_out;
	char			*hd_path;
	int				error;
	struct s_cmd	*head_cmd;
}					t_data;

/*--------------------------------PARSING--------------------------------*/
//DOLLAR.C//
char	*get_var_env_name(char *str, int *i);
char	*get_var_env_val(char *var_env, int len, t_env *mini);
char	*get_dollar(char *str, int *i, t_env *mini);

//LEXER.C//
void	update_quote(bool *quote);
int		check_quote_error(char *str);
int		check_quote_pos(char *str, int pos);
int		get_token_code(char *str, int *i);
int		get_builtin_code(char *str);

//PARSER.C//
int		add_cmd(t_data *data);
char	*create_buffer(void);
int		check_token(t_data *data, int *i);
char	*convert_input(t_data *data, char *input, char *buf, int *i);
int		parse_input(t_data *data);

//REDIR.C//
char	*convert_hd_input(t_data *data, char *input);
void	get_hd_input(t_data *data, char *end);
int		heredoc(t_data *data, char *end);
char	*get_token_arg(char *str, int *i);
int		redir_handler(t_data *data, char *str, int *i);

/*---------------------------------EXEC----------------------------------*/
//EXEC.C//
int		ft_cmd(t_cmd *cmd, t_env *mini);
int		ft_fork(t_env *mini, t_cmd *cmd);
int		ft_last_child(t_cmd *cmd, t_env *mini);
void	ft_close_and_reset_exec(t_cmd *cmd, int out, int in, int error);
int		ft_exe(t_env *mini, t_cmd *cmd, int error);

//FT_SPLIT.C//
// int		ft_charset(char const s, char c);
// int		ft_count_words(char const *s, char c);
// void	ft_add_words(char *dest, const char *src, char c);
// void	ft_add_to_tab(char **tab, const char *s, char c);
// char	**ft_split2(char const *s, char c);
int		ft_charset(char const s, char *charset);
int		ft_count_words(char const *s, char *charset);
void	ft_add_words(char *dest, const char *src, char *charset);
void	ft_add_to_tab(char **tab, const char *s, char *charset);
char	**ft_split2(char const *s, char *charset);

//FT_UTILS.C//
void	ft_exec_err(const char *str, char *var);
char	**ft_make_tab_from_env(t_env *mini);
void	ft_exit_clean(t_env *mini, t_cmd *cmd, int error);
char	*ft_make_path(char *dir, char *cmd);
char	*ft_get_path(char *cmd, char **env);

/*---------------------------------BUILTINS------------------------------*/
//CD.C//
char	*ft_get_env_path(char *env_path, t_env *mini);
char	*ft_update_pwd(t_env *mini, char *join, int mod);
int		ft_go_path(int location, t_env *mini);
char	*ft_handle_tild(char *str, t_env *mini);
void	ft_cd_builtind(t_cmd *cmd, t_env *mini);

//ECHO.C//
void	ft_echo_builtin(t_cmd *cmd);

//EXPORT.C//
void	ft_sort_print_env(t_env *mini);
char	*ft_cpy_env_name(char *args);
void	ft_add_list_env(t_env *mini, char *args);
void	ft_add_args_env(t_cmd *cmd, t_env *mini);
void	ft_export_builtin(t_cmd *cmd, t_env *mini);

//EXPORT_UTILS.C//
void	ft_builtin(t_cmd *cmd, t_env *mini);
int		ft_is_valid_env(char *args);
int		ft_is_in_env(t_env *mini, char *args);
t_env	*ft_cpy_env(t_env *mini);
void	ft_print_export_env(t_env *mini);

//PWD.C//
void	ft_pwd_builtin(void);

//UNSET.C//
void	ft_print_env(t_env *mini);
void	ft_remove_list(t_env *old, t_env *tmp);
void	ft_remove_if_in_env(t_env *mini, char *args);
void	ft_unset_builtin(t_cmd *cmd, t_env *mini);

/*---------------------------------SIGNAL--------------------------------*/
void	ft_signal_newline(int unused);
void	ft_signal_quit(int unused);
void	ft_signal_newline2(int unused);

/*---------------------------------LIBFT---------------------------------*/
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *str);
int		ft_strchr(const char *str, int c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, int n);
int		lst_addback(t_env *mini_env, char *env);
int		ft_atoi(char *str, int *e);
void	lst_freeall(t_env *mini_env);
int		ft_isdigit(char c);
int		ft_isalnun_tmp(char c);
int		ft_lst_count(t_env *env);
void	ft_clear_tab(char **tab);
void	ft_clear_fd(t_cmd *cmd);
void	ft_clear_cmd_list(t_cmd *cmd);
char	*ft_charjoin(char *s1, char c);
int		ft_isalnum(int c);
int		ft_isspace(int c);
char	*ft_strnstr(const char *s1, const char *to_find, size_t n);
char	*ft_cpy(char *src, int skip);
char	*ft_strdup(char *s);
t_cmd	*ft_get_list_last(t_cmd *list);
void	ft_list_add_back(t_cmd **list, t_cmd *new);
void	*ft_memset(void *s, int c, size_t n);
char	*ft_itoa(int n);
int		nb_len(int n);

#endif