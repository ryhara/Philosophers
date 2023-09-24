/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:10:56 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/24 22:47:17 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_philo_dead(t_philo *philo)
{
	bool	is_dead;

	pthread_mutex_lock(&philo->data->status);
	is_dead = philo->data->is_dead;
	pthread_mutex_unlock(&philo->data->status);
	return (is_dead);
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
	pthread_mutex_destroy(&data->status);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->eat);
	free(data->forks);
	free(data);
	free(philos);
}
