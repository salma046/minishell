/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 09:49:06 by salaoui           #+#    #+#             */
/*   Updated: 2024/10/13 11:58:43 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

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
int		ft_strncmp(char *s1, const char *s2, size_t n);
int		 is_space(char *line);
void	ft_lstadd_back(t_token **lst, t_token *new);
char	*get_word(char *str, int i);
void	ft_put_token(char **line, enum e_token_type token_t, t_token **tokens_list);
int		ft_put_word_token(char **line, enum e_token_type token_t, t_token **tokens_list);
size_t	ft_strlen(const char *str); 	
t_token	*rm_qotes(t_token *tokens);
t_token	*parsing(t_minishell g_minishell);
t_token	*rmp_dollar(t_token *tokens);
int		count_pipe(t_token *tokens);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(char *src);
int		is_not_alpanum(char c);
int		cmd_count(t_token *tokens);
t_node	*mk_nodes(t_token *tokens);

// minitest in the end of prog
// cat lksdj < dalkf;> sdkfj<<sdf >>dslfj |ksdjj|osdfij|sdkfj+
# endif
