/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:22:39 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/21 11:45:59 by ryhara           ###   ########.fr       */
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
	struct timeval	*start_time;

}	t_data;

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	lock;
	int				id;
	int				nbr_of_eat;
	t_status		status;
	t_data			*data;
	struct timeval	last_eat;
	struct timeval	start_eat;
}	t_philo;

// check_args.c
bool	check_args(int argc, char **argv);
bool	check_data(int argc, char **argv);
int		ft_atoi(char *str);
// init.c
t_data	*data_init(int argc, char **argv);
t_philo	*philo_init(t_data *data);
// main.c
// time.c
size_t	get_micro_sec(struct timeval *time);
size_t	get_milli_sec(struct timeval *time);
size_t	get_sec(struct timeval *time);
void	get_current_time(struct timeval *time);
// utils.c
size_t	ft_strlen(char *str);
void	ft_puterr(char *str);
void	print_args_error(void);
void	print_failed_error(void);

#endif