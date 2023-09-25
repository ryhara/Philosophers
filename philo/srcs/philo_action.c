/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:34:07 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/25 15:47:23 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	print_state(philo, STR_FORK, get_milli_sec() - philo->data->start_time);
	if (philo->data->nbr_of_philo == 1)
		return (usleep_philo(philo->data->time_to_die * (long)1000));
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	print_state(philo, STR_FORK, get_milli_sec() - philo->data->start_time);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->status);
	philo->nbr_of_eat++;
	philo->last_eat = get_milli_sec();
	pthread_mutex_unlock(&philo->data->status);
	print_state(philo, STR_EAT, get_milli_sec() - philo->data->start_time);
	usleep_philo(philo->data->time_to_eat * (long)1000);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
}

void	sleeping(t_philo *philo)
{
	print_state(philo, STR_SLEEP, get_milli_sec() - philo->data->start_time);
	usleep_philo(philo->data->time_to_sleep * (long)1000);
}

void	thinking(t_philo *philo)
{
	print_state(philo, STR_THINK, get_milli_sec() - philo->data->start_time);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	until_start(philo->data->start_time);
	if (philo->id % 2 == 1)
		usleep_philo(philo->data->nbr_of_philo * (long)200);
	while (1)
	{
		thinking(philo);
		if (is_philo_dead(philo))
			break ;
		take_fork(philo);
		eating(philo);
		sleeping(philo);
	}
	return (NULL);
}
