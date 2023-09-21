/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:22:39 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/21 20:45:18 by ryhara           ###   ########.fr       */
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

# define SUCCESS 0
# define ERROR 1
# define STR_FORK " has taken a fork\n"
# define STR_EAT " is eating\n"
# define STR_SLEEP " is sleeping\n"
# define STR_THINK " is thinking\n"
# define STR_DIED " died\n"

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
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_eat;
	long			start_time;
	bool			is_dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	time;
	pthread_mutex_t	eat;
	pthread_mutex_t	status;

}	t_data;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				nbr_of_eat;
	int				left_fork;
	int				right_fork;
	bool			is_full;
	t_status		status;
	t_data			*data;
	long			next_eat;
	long			last_eat;
	long			start_eat;
}	t_philo;

// check_args.c
bool	check_args(int argc, char **argv);
bool	check_data(int argc, char **argv);
int		ft_atoi(char *str);
// init.c
t_data	*data_init(int argc, char **argv);
t_philo	*philo_init(t_data *data);
bool	all_init(t_data **data, t_philo **philos, int argc, char **argv);
// main.c
// philo_action.c
void	take_fork(t_philo *philo);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);
void	*routine(t_philo *philo);
// philo.c
bool	is_phio_dead(t_philo *philo);
bool	is_philos_dead(t_philo *philos);
bool	is_philos_full(t_philo *philos);
bool	check_philos_status(t_philo *philos);
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
long	get_sec(void);
long	mili_to_micro(long ms);
void	usleep_philo(long ms);

#endif