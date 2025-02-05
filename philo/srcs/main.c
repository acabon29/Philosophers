/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaufil <cbeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:58:12 by cbeaufil          #+#    #+#             */
/*   Updated: 2025/02/04 17:00:38 by cbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_signal_received = 0;

char	*read_prompt(void)
{
	char	*line;

	if (g_signal_received != SIGINT)
	{
		rl_redisplay();
		line = gc_readline(PROMPT);
	}
	else
		line = gc_readline("");
	g_signal_received = 0;
	return (line);
}

int	main(int argc __attribute__((unused)), char **argv __attribute__((unused)),
char **envp)
{
	char			*line;
	t_global		global;	

	global = init_global(envp);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, main_handle_sigint);
	line = read_prompt();
	while (line)
	{
		minishell_routine(line, &global);
		signal(SIGINT, main_handle_sigint);
		line = read_prompt();
	}
	gc_exit(*get_exit_code());
}
