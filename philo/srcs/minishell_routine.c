/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_routine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaufil <cbeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:00:53 by cbeaufil          #+#    #+#             */
/*   Updated: 2025/02/04 17:03:00 by cbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_global	init_global(char **envp)
{
	t_global	global;

	global.env = init_env(envp);
	global.builtins = init_builtins();
	global.last_ret = 0;
	global.current_pipe = 0;
	return (global);
}

void	*minishell_routine(char *line, t_global *global)
{
	t_command	*pipeline;

	pipeline = get_pipeline(line, global);
	if (!pipeline || pipeline == (t_command *)STOP_HEREDOC)
		return (NULL);
	if (!pipeline)
		return (NULL);
	if (!pipeline->next && get_builtin(pipeline->name, global->builtins))
		global->last_ret = alone_builtin_exec(global, pipeline);
	else
		fork_and_pipe(global, pipeline);
	gc_free(line);
	return (NULL);
}
