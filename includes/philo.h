/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:22:39 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/19 17:24:08 by ryhara           ###   ########.fr       */
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

# define STR_FORK " has taken a fork\n"
# define STR_EAT " is eating\n"
# define STR_SLEEP " is sleeping\n"
# define STR_THINK " is thinking\n"
# define STR_DIED " died\n"

typedef struct s_data
{
	int				nbr_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_eat;
}	t_data;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	// struct timeval	last_eat;
	// struct timeval	start_time;
}	t_philo;

// check_args.c
bool	check_args(int argc, char **argv);
bool	check_data(int argc, char **argv);
int		ft_atoi(char *str);
// init.c
t_data	*data_init(int argc, char **argv);
t_philo	*philo_init(t_data *data);
// main.c
// utils.c
void	print_args_error(void);

#endif