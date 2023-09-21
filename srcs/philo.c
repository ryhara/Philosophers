/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:10:56 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/21 20:43:19 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_phio_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->status);
	if (philo->status == DIED)
	{
		pthread_mutex_unlock(&philo->data->status);
		return (true);
	}
	pthread_mutex_unlock(&philo->data->status);
	return (false);
}

bool	is_philos_dead(t_philo *philos)
{
	long	current_time;
	int		i;

	current_time = get_milli_sec();
	i = 0;
	while (i < philos->data->nbr_of_philo && philos->data->is_dead == false)
	{
		pthread_mutex_lock(&philos->data->status);
		pthread_mutex_lock(&philos->data->time);
		if (current_time - philos[i].last_eat > philos->data->time_to_die)
		{
			philos[i].status = DIED;
			philos->data->is_dead = true;
			pthread_mutex_unlock(&philos->data->time);
			pthread_mutex_unlock(&philos->data->status);
			return (true);
		}
		if (philos->data->nbr_of_eat > 0 && philos[i].is_full == false
			&& philos[i].nbr_of_eat >= philos->data->nbr_of_eat)
			philos[i].is_full = true;
		pthread_mutex_unlock(&philos->data->time);
		pthread_mutex_unlock(&philos->data->status);
		i++;
	}
	return (false);
}

bool	is_philos_full(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->data->nbr_of_philo)
	{
		if (philos[i].is_full == false)
			return (false);
		i++;
	}
	return (true);
}

bool	check_philos_status(t_philo *philos)
{
	if (is_philos_dead(philos))
		return (false);
	if (is_philos_full(philos))
		return (false);
	return (true);
}

void	destroy_all(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	free(data);
	free(philos);
}
