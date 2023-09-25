/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 22:45:22 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/26 01:23:55 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_philos_dead(t_philo *philos)
{
	int		i;

	i = 0;
	while (i < philos->data->nbr_of_philo)
	{
		pthread_mutex_lock(&philos[i].eat);
		if (get_milli_sec() >= philos[i].next_eat)
		{
			// get_milli_sec() - philos[i].last_eat >= philos->data->time_to_die;
			pthread_mutex_unlock(&philos[i].eat);
			pthread_mutex_lock(&philos->data->dead);
			philos->data->is_dead = true;
			pthread_mutex_unlock(&philos->data->dead);
			print_state(&philos[i], STR_DIED);
			return (true);
		}
		pthread_mutex_unlock(&philos[i].eat);
		if (philos->data->nbr_of_eat > 0 && philos[i].is_full == false
			&& philos[i].nbr_of_eat >= philos->data->nbr_of_eat)
			philos[i].is_full = true;
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
	pthread_mutex_lock(&philos->data->dead);
	philos->data->is_dead = true;
	pthread_mutex_unlock(&philos->data->dead);
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
		pthread_mutex_lock(&philos->data->dead);
		if (philos->data->is_dead == true)
		{
			pthread_mutex_unlock(&philos->data->dead);
			break ;
		}
		else
		{
			pthread_mutex_unlock(&philos->data->dead);
			if (!check_philos_status(philos))
				break ;
		}
	}
	return (NULL);
}
