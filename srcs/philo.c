/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:10:56 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/21 14:30:53 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(t_philo *philo)
{
	(void)philo;
	return (NULL);
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
