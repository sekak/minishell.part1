/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekkak <asekkak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:09:44 by asekkak           #+#    #+#             */
/*   Updated: 2023/04/10 16:49:02 by asekkak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *all_cmd(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 6) == 0)
		return ("echo");
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		return ("cd");
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		return ("pwd");
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return ("export");
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return ("unset");
	else if (ft_strncmp(cmd, "env", 4) == 0)
		return ("env");
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		return ("exit");
	return (0);
}

char *all_redir(char *redir)
{
	if (ft_strncmp(redir, ">", 6) == 0)
		return ("echo");
	else if (ft_strncmp(redir, ">>", 3) == 0)
		return ("cd");
	else if (ft_strncmp(redir, "<", 4) == 0)
		return ("pwd");
	else if (ft_strncmp(redir, "<<", 7) == 0)
		return ("export");

	return (0);
}

int check_cmd(t_lexer *head)
{
	int i = 0;
	while (head->str[i])
	{
		if (all_cmd(head->str[i]))
		{
			head->cmd = all_cmd(head->str[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

int check_flag(t_lexer *head)
{
	int i = 0;
	head->flag = 0;
	while (head->str[i])
	{
		if (ft_strncmp(head->str[i], "-n", 3) == 0)
		{
			head->flag = 1;
			return (0);
		}
		i++;
	}
	return (1);
}
char *choose_red(char *red)
{
	if (ft_strncmp(red, ">", 2) == 0)
		return (">");
	else if (ft_strncmp(red, "<", 2) == 0)
		return ("<");
	else if (ft_strncmp(red, ">>", 3) == 0)
		return (">>");
	else if (ft_strncmp(red, "<<", 3) == 0)
		return ("<<");
	return (0);
}

int check_pipe(t_lexer *head)
{
	int i = 0;
	head->pipe = 0;
	while (head->str[i])
	{
		if (ft_strncmp(head->str[i], "|", 2) == 0)
		{
			head->pipe = 1;
			return (0);
		}
		i++;
	}
	return (1);
}
 
// int check_env(char *str, int count)
// {
// 	static int  i = 0;
// 	// size_t j = 0;
// 	// int ret = 0;
// 	// int ret = 0;
	
// 	while (str[i] && i < count)
// 	{
// 		if(str[i] == '$' && str[i - 1] == 39)
// 		{
// 			while(str[i] != 39)
// 				i++;
// 			i++;
// 			return(i);
// 		}
// 		i++;
// 	}
// 	 return(i);
// }

int check_dollar(t_lexer *head, char *input)
{
	 
	int i = 0;
	int j = 0;
	int count = 0;
	char *str;
	(void)input;
	while (head->str[i])
	{
		if ((str = ft_strchr(head->str[i], '$')))
			count++;
		i++;
	}
	if (!(head->env = malloc(sizeof(t_env) * (count + 1))))
		return (0);
	i = 0;
	j = 0;
	while (head->str[i])
	{
 		if ((str = ft_strchr(head->str[i], '$')))
		{
			head->env[j].dollar = str;
			head->env->i = j;
			j++;
		}
		i++;
	}
	// handle_env(head);
	return (0);
}


 

int check_redirection(t_lexer *lexer)
{
	int i = 0;
	int j = 0;
	int count = 0;

	while (lexer->str[i])
	{
		if (choose_red(lexer->str[i]))
			count++;
		i++;
	}
	i = 0;

	lexer->table = malloc(sizeof(t_table) * (count + 1));
	if (!lexer->table)
		return (0);
	while (lexer->str[i])
	{
		if (choose_red(lexer->str[i]))
		{
			int match = ft_strncmp(lexer->str[i], choose_red(lexer->str[i]), strlen(choose_red(lexer->str[i]) + 1));
			if (match == 0)
			{
				printf("SET table at %d\n", j);
				lexer->table[j].redire = 1;
				lexer->table[j].name_file = lexer->str[i + 1];
				lexer->table[j].token_redire = choose_red(lexer->str[i]);
				j++;
			}
		}
		i++;
	}
	return (1);
}

void parser(t_lexer *lst , char *input)
{

	t_lexer *head = lst;

	while (head)
	{

		if (check_cmd(head))
			head->cmd = "empty";
		check_flag(head);
		check_pipe(head);
		check_dollar(head, input);
		check_redirection(head);
		head = head->next;
	}
	t_lexer *test = lst;
	int i = 0;
	int j = 0;
	int t = 0;
	while (test)
	{
		printf("/****************************/\n");
		j = 0;
		i = 0;
		t = 0;
		printf("	String : [");
		while (test->str[i])
			printf(" {%s} ", test->str[i++]);
		printf("]\n");
		printf("	Commande: {%s}, \n", test->cmd);
		printf("	Flag: %d\n", test->flag);
		printf("	Pipe: %d\n", test->pipe);
		while (t <= test->env->i)
			printf("	ENV: %s\n", test->env[t++].dollar);
		while (test->table[j].redire == 1)
		{
			printf("	Token: %d\n", test->table[j].redire);
			printf("	Redirection token: %s\n", test->table[j].token_redire);
			printf("	Name File Redirection : %s\n", test->table[j].name_file);
			j++;
		}
		printf("/******* NEXT NODE **********/\n");
		test = test->next;
	}
}