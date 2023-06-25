/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoda <kyoda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:44:10 by keys              #+#    #+#             */
/*   Updated: 2023/06/25 13:04:30 by kyoda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

void	set_signal(void)
{
	struct sigaction	sig_int;
	struct sigaction	sig_quit;
	extern int			_rl_echo_control_chars;

	_rl_echo_control_chars = 0;
	sigemptyset(&sig_int.sa_mask);
	sig_int.sa_handler = sig_handler;
	sig_int.sa_flags = 0;
	sigaction(SIGINT, &sig_int, NULL);
	sigemptyset(&sig_quit.sa_mask);
	sig_quit.sa_handler = sig_handler;
	sig_int.sa_flags = 0;
	sigaction(SIGQUIT, &sig_quit, NULL);
}

void	block_signal(void)
{
	struct sigaction	sig_int;
	struct sigaction	sig_quit;

	sigemptyset(&sig_int.sa_mask);
	sig_int.sa_handler = SIG_IGN;
	sig_int.sa_flags = 0;
	sigaction(SIGINT, &sig_int, NULL);
	sigemptyset(&sig_quit.sa_mask);
	sig_quit.sa_handler = SIG_IGN;
	sig_int.sa_flags = 0;
	sigaction(SIGQUIT, &sig_quit, NULL);
}

void	reset_signal(void)
{
	struct sigaction	sig_int;
	struct sigaction	sig_quit;

	sigemptyset(&sig_int.sa_mask);
	sig_int.sa_handler = SIG_DFL;
	sig_int.sa_flags = 0;
	sigaction(SIGINT, &sig_int, NULL);
	sigemptyset(&sig_quit.sa_mask);
	sig_quit.sa_handler = SIG_DFL;
	sig_int.sa_flags = 0;
	sigaction(SIGQUIT, &sig_quit, NULL);
}
