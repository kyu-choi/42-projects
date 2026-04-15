/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_linux_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 10:46:16 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include <stdio.h>
#include <readline/readline.h>

/**
 * @brief Replaces the current readline line buffer (Linux implementation)
 * @param text New text to replace current line
 * @param clear If non-zero, clear undo list
 * @details Wrapper for readline's rl_replace_line function
 */
void	ft_replace_line(const char *text, int clear)
{
	rl_replace_line(text, clear);
}
