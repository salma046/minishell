/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 09:49:06 by salaoui           #+#    #+#             */
/*   Updated: 2024/09/06 15:55:09 by salaoui          ###   ########.fr       */
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
}					t_minishell;

extern t_minishell	minishell;

int	ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_lstadd_back(t_token **lst, t_token *new);
char	*ft_str_until(const char *s, int c);
// t_token *ft_tokenize(char *line);

# endif
