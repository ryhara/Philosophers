/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 22:45:22 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/25 20:08:20 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_philos_dead(t_philo *philos)
{
	int		i;

	i = 0;
	while (i < philos->data->nbr_of_philo)
	{
		pthread_mutex_lock(&philos->data->eat);
		if (get_milli_sec() - philos[i].last_eat >= philos->data->time_to_die)
		{
			philos[i].status = DIED;
			philos->data->is_dead = true;
			pthread_mutex_unlock(&philos->data->eat);
			print_state(&philos[i], STR_DIED,
				get_milli_sec() - philos->data->start_time);
			return (true);
		}
		if (philos->data->nbr_of_eat > 0 && philos[i].is_full == false
			&& philos[i].nbr_of_eat >= philos->data->nbr_of_eat)
			philos[i].is_full = true;
		pthread_mutex_unlock(&philos->data->eat);
		i++;
	}
	return (false);
}

static bool	is_philos_full(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->data->nbr_of_philo)
	{
		if (philos[i].is_full == false)
			return (false);
		i++;
	}
	pthread_mutex_lock(&philos->data->eat);
	philos->data->is_dead = true;
	pthread_mutex_unlock(&philos->data->eat);
	return (true);
}

static bool	check_philos_status(t_philo *philos)
{
	if (is_philos_dead(philos))
		return (false);
	if (philos->data->nbr_of_eat > 0 && is_philos_full(philos))
		return (false);
	return (true);
}

void	*monitoring(t_philo *philos)
{
	while (1)
	{
		pthread_mutex_lock(&philos->data->eat);
		if (philos->data->is_dead == true)
		{
			pthread_mutex_unlock(&philos->data->eat);
			break ;
		}
		else
		{
			pthread_mutex_unlock(&philos->data->eat);
			if (!check_philos_status(philos))
				break ;
		}
	}
	return (NULL);
}
