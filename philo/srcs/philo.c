/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:10:56 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/22 21:17:06 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_phio_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->status);
	if (philo->status == DIED || philo->data->is_dead == true)
	{
		pthread_mutex_unlock(&philo->data->status);
		return (true);
	}
	pthread_mutex_unlock(&philo->data->status);
	return (false);
}

void	destroy_all(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philo + 1)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->status);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->eat);
	free(data->forks);
	free(data);
	free(philos);
}
