/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:34:07 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/21 20:46:25 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	print_state(philo, STR_FORK);
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	print_state(philo, STR_FORK);
	pthread_mutex_lock(&philo->data->status);
	philo->status = EATING;
	pthread_mutex_unlock(&philo->data->status);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->time);
	philo->last_eat = get_milli_sec();
	pthread_mutex_unlock(&philo->data->time);
	pthread_mutex_lock(&philo->data->eat);
	philo->nbr_of_eat++;
	pthread_mutex_unlock(&philo->data->eat);
	print_state(philo, STR_EAT);
	usleep_philo(philo->data->time_to_eat * (long)1000);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_lock(&philo->data->status);
	philo->status = SLEEPING;
	pthread_mutex_unlock(&philo->data->status);
}

void	sleeping(t_philo *philo)
{
	print_state(philo, STR_SLEEP);
	usleep_philo(philo->data->time_to_sleep * (long)1000);
	pthread_mutex_lock(&philo->data->status);
	philo->status = THINKING;
	pthread_mutex_unlock(&philo->data->status);
}

void	thinking(t_philo *philo)
{
	print_state(philo, STR_THINK);
}

void	*routine(t_philo *philo)
{
	if (philo->id % 2 == 1)
		usleep_philo((long)200);
	while (1)
	{
		thinking(philo);
		take_fork(philo);
		eating(philo);
		if (is_phio_dead(philo))
			break ;
		sleeping(philo);
		if (is_phio_dead(philo))
			break ;
	}
	return (NULL);
}
