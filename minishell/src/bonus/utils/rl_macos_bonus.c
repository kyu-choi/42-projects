/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_macos_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwki <hyeonwki@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 00:00:00 by hyeonwki          #+#    #+#             */
/*   Updated: 2025/11/22 10:46:16 by hyeonwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

/**
 * @brief Replaces the current readline line buffer (macOS stub)
 * @param text New text to replace current line (unused)
 * @param clear If non-zero, clear undo list (unused)
 * @details macOS stub - rl_replace_line not available on macOS readline
 */
void	ft_replace_line(const char *text, int clear)
{
	(void)text;
	(void)clear;
}
