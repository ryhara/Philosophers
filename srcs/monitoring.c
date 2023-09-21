/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 22:45:22 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/21 22:58:17 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	void	unlock_status_eat(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->eat);
	pthread_mutex_unlock(&philo->data->status);
}

static bool	is_philos_dead(t_philo *philos)
{
	long	current_time;
	int		i;

	current_time = get_milli_sec();
	i = 0;
	while (i < philos->data->nbr_of_philo && philos->data->is_dead == false)
	{
		unlock_status_eat(&philos[i]);
		if (current_time - philos[i].last_eat > philos->data->time_to_die)
		{
			philos[i].status = DIED;
			philos->data->is_dead = true;
			unlock_status_eat(&philos[i]);
			print_state(&philos[i], STR_DIED);
			return (true);
		}
		if (philos->data->nbr_of_eat > 0 && philos[i].is_full == false
			&& philos[i].nbr_of_eat >= philos->data->nbr_of_eat)
			philos[i].is_full = true;
		unlock_status_eat(&philos[i]);
		i++;
	}
	return (false);
}

static bool	is_philos_full(t_philo *philos)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philos->data->status);
	while (i < philos->data->nbr_of_philo)
	{
		if (philos[i].is_full == false)
		{
			pthread_mutex_unlock(&philos->data->status);
			return (false);
		}
		i++;
	}
	philos->data->is_dead = true;
	pthread_mutex_unlock(&philos->data->status);
	return (true);
}

static bool	check_philos_status(t_philo *philos)
{
	if (is_philos_dead(philos))
		return (false);
	if (is_philos_full(philos))
		return (false);
	return (true);
}

void	monitoring(t_data *data, t_philo *philos)
{
	while (1)
	{
		pthread_mutex_lock(&data->status);
		if (data->nbr_of_eat < 0 && data->is_dead == true)
		{
			pthread_mutex_unlock(&data->status);
			break ;
		}
		if (data->is_dead == true)
		{
			pthread_mutex_unlock(&data->status);
			break ;
		}
		else
		{
			pthread_mutex_unlock(&data->status);
			if (!check_philos_status(philos))
				break ;
		}
		usleep_philo(1000);
	}
}
