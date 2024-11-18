#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

//--->Sajida: new header Declarations
# include <string.h>
# include <signal.h>
# include "libft/libft.h"
#include <stdio.h>
#include <errno.h>
typedef struct s_env
{
	char			*value;
	char			*test;
	char			*key;
	char			equal;
	struct s_env 	*next;
}	t_env;


typedef struct s_senv
{
	char *svalue;
	char *skey;
	char sequal;
	struct s_senv *next;
} t_senv;
/// Sajida


typedef enum e_token_type
{
	WORD,
	PIPE,
	HER_DOC,
	OUT_REDIR,
	APPEND,
	INP_REDIR
}					token_type;

typedef struct s_token
{
	char			*data;
	token_type		data_type;
	struct s_token	*next_token;
	struct s_token	*prev_token;
}	t_token;

typedef struct s_redir
{
	token_type		red_type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_node
{
	char				**cmd;
	t_redir				*redir;
	struct s_node	*next_node;
	struct s_node	*prev_node;
}	t_node;

typedef struct s_minishell
{
	char	**envirement;
	char	*command;
	t_token	*tokens;
	t_node	*nodes;
}					t_minishell;

extern t_minishell	minishell;

t_token *ft_tokenize(t_minishell g_minishell);
int		 is_space(char *line);
void	ft_lstadd_back_token(t_token **lst, t_token *new);
char	*get_word(char *str, int i);
void	ft_put_token(char **line, enum e_token_type token_t, t_token **tokens_list);
int		ft_put_word_token(char **line, enum e_token_type token_t, t_token **tokens_list, int heredoc);
t_token	*rm_qotes(t_token *tokens);
t_token	*parsing(t_minishell g_minishell);
char	*rmp_dollar(char *tokens_word, t_token **tokens_list);
int		count_pipe(t_token *tokens);
int		is_not_alpanum(char c);
int		cmd_count(t_token *tokens);
t_node	*mk_nodes(t_token *tokens);
int		check_4_space(char *env_var);
char *token_edi_env(char *str, char *env_var, t_token **tokens_list);
void	token_new_word(char *word, enum e_token_type token_t,
		t_token **tokens_list, int heredoc);
char *after_dol_word(char *str, int l, int str_len);
int count_dollar_lenth(char *str);
int is_not_valid_expend(char *str, int i);;
int	main_heredoc(t_token *tokens);

//  🥳 EXECUTION PART:

// functionts utils:
int ft_strcmp(char *s1, char *s2);
void ft_sigint(int x);

//commands:
void ft_echo(t_token *data);
int ft_cd(t_token *data);
void ft_pwd(t_token *data);
void check_command(t_token *data);
void ft_env(t_minishell data);
void ft_exit(t_token *data);
void ft_unset(t_env *env_list,t_minishell data);
void ft_backup(t_env *original, t_minishell data);
void ft_env_unset(t_minishell data);
void sort_env(t_senv *node);
void ft_env_export_once(t_minishell data, int active);
void ft_add_to_export_arg(t_minishell data);
void ft_export(t_minishell data);

// executr commands:
void ft_execute(t_minishell *data);

//redirectios:
int ft_output(t_token *tokens);
int ft_input(t_token *tokens);


# endif
