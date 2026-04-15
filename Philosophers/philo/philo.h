/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 16:07:16 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/09/05 16:07:17 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_inform
{
	int	number_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must;
	int	number_of_must;
}	t_inform;

typedef struct s_philo
{
	int				id;
	int				left;
	int				right;
	long long		last_meal;
	int				eaten;
	pthread_mutex_t	meal_mx;
	pthread_t		thread;
}	t_philo;

typedef struct s_share
{
	int				n;
	long long		start_ms;
	int				stop;
	int				i;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mx;
	pthread_mutex_t	state_mx;
}	t_share;

typedef struct s_pack
{
	t_share		*share;
	t_inform	*inform;
	t_philo		*philo;
}	t_pack;

typedef struct s_var
{
	int			i;
	long long	last;
	long long	gap;
}	t_var;

int			argv_check(int argc, char **argv, t_inform *inform);
int			one_check(char *argv, t_inform *inform);
int			two_check(char *argv, t_inform *inform);
int			three_check(char *argv, t_inform *inform);
int			four_check(char *argv, t_inform *inform);
int			five_check(char *argv, t_inform *inform);

int			non_must(char **argv, t_inform *inform);
int			must_exit(char **argv, t_inform *inform);

int			ft_atoi(const char *nptr);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

void		one_philo(t_inform *inform);

int			make_philo(t_inform *inform, t_philo **philo, \
			t_share *share, t_pack **pack);

int			init_share(t_inform *inform, t_share *share);
void		init_philo(t_philo **philo, t_share *share);

long long	now_ms(void);

int			create_pthread(t_inform *inform, \
			t_philo **philo, t_share *share, t_pack **pack);

void		free_destroy(t_philo *philo, t_share *share, t_pack *pack);

void		philo_action(long long ms, t_share *share);
void		print_action(t_share *share, int id, char *msg, int is_dead);
void		*philo_routine(void *arg);
void		*monitor_routine(void *arg);

void		take_forks(t_philo *philo, t_share *share);
void		put_forks(t_philo *philo, t_share *share);

#endif
