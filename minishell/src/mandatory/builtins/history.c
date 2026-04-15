/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/23 00:11:18 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <readline/history.h>

/**
 * @brief Displays command history (history)
 * @param args Command arguments (unused)
 * @return Always 0
 * @details Uses readline's history_list() to display command history
 */
int	builtin_history(char **args)
{
	HIST_ENTRY	**history;
	int			i;

	(void)args;
	history = history_list();
	if (!history)
		return (0);
	i = 0;
	while (history[i])
	{
		ft_putstr_fd("  ", STDOUT_FILENO);
		ft_putnbr_fd(i + 1, STDOUT_FILENO);
		ft_putstr_fd("  ", STDOUT_FILENO);
		ft_putendl_fd(history[i]->line, STDOUT_FILENO);
		i++;
	}
	return (0);
}
