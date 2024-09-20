/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saait-si <saait-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 09:49:06 by salaoui           #+#    #+#             */
/*   Updated: 2024/09/20 06:47:04 by saait-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

//--->Sajida: new header Declarations
# include <string.h>
#include <signal.h>

//--->Sajida: 

typedef enum e_token_type
{
	WORD,
	PIPE,
	HER_DOC,
	OUT_REDIR,
	APPEND,
	INP_REDIR
}					token_type;

typedef struct s_tcomp
{
	char	*cmd;
	char	**cmd_args;
	char	*out_file;
	char	*in_file;
}	t_tcomp;

typedef struct s_token
{
	char			*data;
	token_type		data_type;
	struct s_token	*next_token;
	struct s_token	*prev_token;
	struct s_tcomp	*tok_comp;
}	t_token;

typedef struct s_minishell
{
	char			**envirement;
	char			*command;
	t_token			*tokens;
	int				lenght_command;
}					t_minishell;

extern t_minishell	minishell;

t_token *ft_tokenize(t_minishell g_minishell);
int		ft_strncmp( const char *s1, const char *s2, size_t n);
int		 is_space(char *line);
void	ft_lstadd_back(t_token **lst, t_token *new);
char	*get_word(char *str, int i);
void	ft_put_token(char **line, enum e_token_type token_t, t_token **tokens_list);
int		ft_put_word_token(char **line, enum e_token_type token_t, t_token **tokens_list);
size_t	ft_strlen(const char *str); 	
t_token	*rm_qotes(t_token *tokens);
t_token	*parsing(t_minishell g_minishell);
char	*ft_strjoin(char const *s1, char const *s2);

//Sajida
int ft_cd(t_minishell data);
int ft_strcmp(char *s1, char *s2);
void ft_sigint(int num);
int ft_echo(int ac, t_minishell cmd);

# endif
