/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 05:31:37 by ilinhard          #+#    #+#             */
/*   Updated: 2023/01/14 01:53:34 by ilinhard         ###   ########.fr       */
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
# include <errno.h>
# include <string.h>

enum e_token
{
	NOT_TOKEN,
	LESS,
	GREAT,
	DLESS,
	DGREAT,
	PIPE,
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
	int				cpy_in;
	int				cpy_out;
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
	char			*redir_arg;
	char			*path;
	int				token;
	int				fd_in;
	int				fd_out;
	int				nb_hd;
	int				file_error;
	struct s_cmd	*head_cmd;
}					t_data;

/*--------------------------------PARSING--------------------------------*/
//CLEAR.C//
void	free_tab(char **tab);
void	free_all_exit(t_data *data, int exit);

//DOLLAR.C//
char	*get_var_env_name(t_data *data, char *str, int *i);
char	*get_var_env_val(char *var_env, int len, t_env *mini);
char	*get_dollar(t_data *data, char *str, int *i, t_env *mini);

//ERROR.C//
int		check_quote_error(char *str);
int		check_around_token(char *str, int pos, int token);
int		check_token_error(char *str);
void	print_token(int error);
int		check_error(char *input);

//HEREDOC.C//
char	*convert_hd_input(t_data *data, char *input);
void	get_hd_input(t_data *data, int fd, char *end);
char	*get_hd_path(t_data *data);
int		heredoc(t_data *data, char *end);

//PARSER_UTILS.C//
t_env	*ft_create_env(char **env);
char	*create_buffer(void);
char	*add_char(t_data *data, char *buf, char c);
char	*convert_input(t_data *data, char *buf, char *str, int *i);

//PARSER.C//
int		init_cmd(t_data *data);
int		add_cmd(t_data *data);
int		parse_input(t_data *data);

//QUOTE.C//
void	update_quote(bool *quote);
int		check_quote_pos(char *str, int pos);
int		is_quote(char *str, int i);

//REDIR.C//
char	*get_redir_arg(t_data *data, char *str, int *i);
void	fd_in_error(t_data *data);
int		redir_handler(t_data *data, char *str, int *i);

//TOKEN.C//
int		get_builtin_code(char *str);
int		get_token_code(char *str, int *i);
int		is_token(char *str, int i);

/*---------------------------------EXEC----------------------------------*/
//EXEC.C//
int		ft_cmd(t_cmd *cmd, t_env *mini);
int		ft_fork(t_env *mini, t_cmd *cmd);
int		ft_last_child(t_cmd *cmd, t_env *mini);
int		ft_exe_last_child(t_cmd *cmd, t_cmd *tmp, t_env *mini);
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
void	ft_close_and_reset_exec(t_cmd *cmd, int error);
void	ft_exec_err(const char *str, char *var);
char	**ft_make_tab_from_env(t_env *mini);
char	*ft_make_path(char *dir, char *cmd);
// char	*ft_get_path(char *cmd, char **env);
char	*ft_get_path(char *cmd, t_env *mini);

/*---------------------------------BUILTINS------------------------------*/
//CD.C//
char	*ft_get_env_path(char *env_path, t_env *mini);
char	*ft_update_pwd(t_env *mini, char *join, int mod);
int		ft_go_path(int location, t_env *mini);
char	*ft_handle_tild(char *str, t_env *mini);
int		ft_cd_builtind(t_cmd *cmd, t_env *mini);

//ECHO.C//
void	ft_echo_builtin(t_cmd *cmd);

//EXPORT.C//
void	ft_sort_print_env(t_env *mini);
char	*ft_cpy_env_name(char *args);
void	ft_add_list_env(t_env *mini, char *args);
void	ft_add_args_env(t_cmd *cmd, t_env *mini);
int		ft_export_builtin(t_cmd *cmd, t_env *mini);

//EXPORT_UTILS.C//
int		ft_builtin(t_cmd *cmd, t_env *mini);
int		ft_is_valid_env(char *args);
int		ft_is_in_env(t_env *mini, char *args);
t_env	*ft_cpy_env(t_env *mini);
void	ft_print_export_env(t_env *mini);

//PWD.C//
int		ft_pwd_builtin(void);

//UNSET.C//
void	ft_print_env(t_env *mini);
void	ft_remove_list(t_env *old, t_env *tmp);
void	ft_remove_if_in_env(t_env *mini, char *args);
int		ft_unset_builtin(t_cmd *cmd, t_env *mini);

//EXIT.C//
void	ft_exit_clean(t_env *mini, t_cmd *cmd, int error);
void	ft_exit_minishell(t_env *mini, t_cmd *cmd);

/*---------------------------------SIGNAL--------------------------------*/
void	ft_signal_newline(int unused);
void	ft_signal_quit(int unused);
void	ft_signal_newline2(int unused);

/*---------------------------------LIBFT---------------------------------*/
void	ft_verify_errno(t_cmd *cmd);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *str);
int		ft_strchr(const char *str, int c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, int n);
int		lst_addback(t_env *mini_env, char *env);
int		ft_atoi(const char *str, int *error);
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
int		is_del(char *str, int i);
int		count_args(char *str);
char	*cpy_no_quotes(char *cpy, char *str, int pos, int len);
int		fill_tab(char **tab, char *str, int args);
char	**ft_split_parser(char *str);

#endif