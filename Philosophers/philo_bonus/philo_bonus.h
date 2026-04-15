/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 14:42:06 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/09/27 14:42:07 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>

typedef struct s_sems
{
	sem_t	*forks;
	sem_t	*gate;
	sem_t	*print;
	sem_t	*dead;
	sem_t	*full;
	sem_t	*start;
}	t_sems;

typedef struct s_inform
{
	int	number_of_philo;
	int	n;
	int	time_to_eat;
	int	time_to_die;
	int	time_to_sleep;
	int	must;
	int	number_of_must;
}	t_inform;

typedef struct s_child
{
	int			id;
	t_inform	*inform;
	t_sems		*sems;
	long long	start_ms;
	long long	last_meal;
}	t_child;

typedef struct s_full
{
	int		n;
	sem_t	*full;
	sem_t	*dead;
}	t_full;

int			argv_check(int argc, char **argv, t_inform *inform);
int			one_check(char *argv, t_inform *inform);
int			two_check(char *argv, t_inform *inform);
int			three_check(char *argv, t_inform *inform);
int			four_check(char *argv, t_inform *inform);
int			five_check(char *argv, t_inform *inform);

int			non_must(char **argv, t_inform *inform);
int			must_exit(char **argv, t_inform *inform);

int			ft_atoi(const char *nptr);

void		one_philo(t_inform *inform);

int			sema_init(t_sems *sems, t_inform *inform, pid_t **pids);
int			init_check(t_sems *sems);

void		start_child(t_sems *sems, int n);

void		full_monitor_start(t_inform *inform, t_sems *sems);
void		*full_main(void *arg);

int			make_child(int n, pid_t *pids, t_inform *inform, t_sems *sems);
void		child_main(t_child *child);
long long	now_ms(void);
void		print_died(sem_t *print, int id, long long time, sem_t *dead);
void		print_action(sem_t *print, int id, char *msg, long long time);
void		philo_action(int time);

void		*monitor_main(void *arg);

void		kill_all(pid_t	*pids, int n, int signal);
void		wait_all(pid_t *pids, int n);

void		close_unlink_free(pid_t *pids, t_sems *sems);
void		close_unlink_free2(void);

#endif
