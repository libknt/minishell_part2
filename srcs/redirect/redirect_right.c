/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_right.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu2204 <ubuntu2204@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:48:58 by kyoda             #+#    #+#             */
/*   Updated: 2023/06/23 13:19:04 by ubuntu2204       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



static t_fd	*open_file_rr(char *name)
{
	t_fd	*new;

	new = new_fd();
	new->file = open(name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	new->std_fd = 1;
	return (new);
}

static t_fd	*open_file_r(char *name)
{
	t_fd	*new;

	new = new_fd();
	new->file = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	new->std_fd = 1;
	return (new);
}

t_fd	*redirect_right(t_node *node, t_line *line)
{
	t_fd	*fd;

	fd = NULL;
	(void)node;
	while (1)
	{
		if (line->type == T_EOF_R)
			break ;
		if (line->type == REDIRECT && (!ft_strncmp(line->token->word, ">>", 2)
				|| !ft_strncmp(line->token->word, ">", 1)))
		{
			fd = close_file(fd);
			if (!ft_strncmp(line->token->word, ">>", 2))
				fd = open_file_rr(line->next->token->word);
			else
				fd = open_file_r(line->next->token->word);
			line = line->next;
		}
		else if (line->type == REDIRECT)
			line = line->next;
		line = line->next;
	}
	return (fd);
}
