/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu2204 <ubuntu2204@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:44:10 by keys              #+#    #+#             */
/*   Updated: 2023/06/21 15:58:04 by ubuntu2204       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

void	sig_handler(int sig)
{
	g_global.sig = sig;
}

int	exec_action(void)
{
	if (g_global.sig == SIGINT)
	{
		printf("\n");
		ft_putstr_fd("\n", STDERR_FILENO);
		g_global.exit_status = 130;
	}
	else if (g_global.sig == SIGQUIT)
	{
		ft_putstr_fd("Quit(core dump)\n", STDERR_FILENO);
		g_global.exit_status = 131;
	}
	g_global.sig = 0;
	return (0);
}

int	check_state(void)
{
	if (g_global.sig == 0)
		return (0);
	else if (g_global.sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_done = 1;
		g_global.interrupt = true;
		g_global.exit_status = 130;
	}
	else if (g_global.sig == SIGQUIT)
	{
		rl_done = 1;
	}
	g_global.sig = 0;
	return (0);
}