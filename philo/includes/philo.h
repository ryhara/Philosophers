/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:22:39 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/25 23:59:14 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>
# include <pthread.h>

# define STR_FORK "has taken a fork"
# define STR_EAT "is eating"
# define STR_SLEEP "is sleeping"
# define STR_THINK "is thinking"
# define STR_DIED "died"

typedef enum e_status
{
	THINKING,
	EATING,
	SLEEPING,
	FORK,
	DIED
}	t_status;

typedef struct s_data
{
	int				nbr_of_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nbr_of_eat;
	long			start_time;
	bool			is_dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	dead;
}	t_data;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				nbr_of_eat;
	int				left_fork;
	int				right_fork;
	bool			is_full;
	t_data			*data;
	long			last_eat;
	long			next_eat;
	pthread_mutex_t	eat;
}	t_philo;

// check_args.c
bool	check_args(int argc, char **argv);
bool	check_data(int argc, char **argv);
int		ft_atoi(char *str);
int		ft_strcmp(const char *s1, const char *s2);
// init.c
t_data	*data_init(int argc, char **argv);
t_philo	*philo_init(t_data *data);
bool	all_init(t_data **data, t_philo **philos, int argc, char **argv);
// monitoring.c
void	*monitoring(t_philo *philos);
// philo_action.c
void	take_fork(t_philo *philo);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);
void	*routine(void *arg);
// philo.c
bool	is_philo_dead(t_philo *philo);
void	destroy_all(t_data *data, t_philo *philos);
// print,c
size_t	ft_strlen(char *str);
void	ft_puterr(char *str);
void	print_args_error(void);
void	print_failed_error(void);
void	print_state(t_philo *philo, char *state);
// time.c
long	get_micro_sec(void);
long	get_milli_sec(void);
long	milli_to_micro(long ms);
void	usleep_philo(long us);
void	until_start(long ms);

#endif