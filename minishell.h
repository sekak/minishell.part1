/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekkak <asekkak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:29:14 by asekkak           #+#    #+#             */
/*   Updated: 2023/04/08 13:25:25 by asekkak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include "./libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

 
 
typedef struct s_table
{
 	char *name_file;
	char *token_redire;
 	int redire;
} t_table;

typedef struct s_env
{
 	char *dollar;
	int i;
} t_env;

typedef struct s_lexer
{
	char **str;
	struct s_lexer *next;
	char *cmd;
	int flag;
	int pipe;
	t_table *table;
	t_env *env;
 	int i;
 } t_lexer;

//* *********parser****************
void  parser(t_lexer *head);
//******************************** 
t_lexer *add_node(char **content, int start, int end);
void ft_add_back(t_lexer **lst, t_lexer *new);
void ft_sringcpy(char **str, char *content);
void function();

#endif 
