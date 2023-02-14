/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:54:10 by keys              #+#    #+#             */
/*   Updated: 2023/02/14 18:21:15 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_err(const char *e) __attribute__((noreturn));
void	_err(const char *e)
{
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", e);
	exit(1);
}

int	main(void)
{
	char	*prompt;
	bool	flag;
	t_token	*token;
	t_node	*tree;

	rl_outstream = stderr;
	while (1)
	{
		prompt = readline("minishell>");
		if (prompt == NULL)
			break ;
		if (!prompt[0])
		{
			free(prompt);
			continue ;
		}
		token = lexer(&prompt);
		flag = token_error(token);
		if (flag)
		{
			token_free(&token);
			free(prompt);
			continue ;
		}
		tree = parser(token);
		print_tree(tree);
		// flag = parse_err(tree);
		// if (flag)
		// {
		// 	tree_free(tree);
		// 	token_free(&token);
		// 	free(prompt);
		// 	continue ;
		// }
		print_tree(tree);
		// exe(token);
		if (*prompt)
			add_history(prompt);
		tree_free(tree);
		token_free(&token);
		free(prompt);
	}
	return (0);
}
