/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:19:19 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/21 11:49:24 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*data_init(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
	data->nbr_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->nbr_of_eat = ft_atoi(argv[5]);
	else
		data->nbr_of_eat = -1;
	return (data);
}

t_philo	*philo_init(t_data *data)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = (t_philo *)malloc(sizeof(t_philo) * data->nbr_of_philo);
	if (philos == NULL)
		return (NULL);
	while (i < data->nbr_of_philo)
	{
		philos[i].id = i + 1;
		philos[i].nbr_of_eat = 0;
		philos[i].status = THINKING;
		philos[i].data = data;
		// thread
		if (pthread_mutex_init(&philos[i].lock, NULL) != 0)
		{
			free(philos);
			return (NULL);
		}
		i++;
	}
	return (philos);
}
