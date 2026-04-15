/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 14:04:30 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/08/15 14:04:31 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_queue(t_queue *q, int w, int h)
{
	q->capacity = w * h;
	q->data = (t_point *)malloc(sizeof(t_point) * q->capacity);
	q->front = 0;
	q ->rear = 0;
}

int	is_empty(t_queue *q)
{
	return (q->front == q->rear);
}

void	enqueue(t_queue *q, int x, int y)
{
	if (q->rear >= q->capacity)
	{
		ft_printf("queue overflow\n");
		exit(1);
	}
	q->data[q->rear].x = x;
	q->data[q->rear].y = y;
	q->rear++;
}

t_point	dequeue(t_queue *q)
{
	if (q->front == q->rear)
	{
		ft_printf("queue underflow\n");
		exit(1);
	}
	return (q->data[q->front++]);
}
