/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:19:19 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/25 20:08:49 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*data_init(int argc, char **argv)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
	data->nbr_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->is_dead = false;
	if (argc == 6)
		data->nbr_of_eat = ft_atoi(argv[5]);
	else
		data->nbr_of_eat = -1;
	if (pthread_mutex_init(&data->status, NULL) != 0)
		return (NULL);
	if (pthread_mutex_init(&data->print, NULL) != 0)
		return (NULL);
	if (pthread_mutex_init(&data->eat, NULL) != 0)
		return (NULL);
	return (data);
}

pthread_mutex_t	*mutex_init(t_data *data)
{
	int				i;
	pthread_mutex_t	*forks;

	i = 0;
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* (data->nbr_of_philo));
	if (forks == NULL)
		return (NULL);
	while (i < data->nbr_of_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			free(forks);
			return (NULL);
		}
		i++;
	}
	return (forks);
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
		philos[i].right_fork = i;
		philos[i].left_fork = i + 1;
		if (i == data->nbr_of_philo - 1)
			philos[i].right_fork = 0;
		philos[i].last_eat = 0;
		philos[i].nbr_of_eat = 0;
		philos[i].is_full = false;
		i++;
	}
	return (philos);
}

void	print_all_data(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philo)
	{
		printf("philos[%d].id: %d\n", i, philos[i].id);
		printf("left_fork: %d\n", philos[i].left_fork);
		printf("right_fork: %d\n", philos[i].right_fork);
		i++;
	}
	printf("nbr_of_philo: %d\n", data->nbr_of_philo);
	printf("time_to_die: %d\n", data->time_to_die);
	printf("time_to_eat: %d\n", data->time_to_eat);
	printf("time_to_sleep: %d\n", data->time_to_sleep);
	printf("nbr_of_eat: %d\n", data->nbr_of_eat);
}

bool	all_init(t_data **data, t_philo **philos, int argc, char **argv)
{
	*data = data_init(argc, argv);
	if (data == NULL)
		return (print_failed_error(), false);
	(*data)->forks = mutex_init(*data);
	if ((*data)->forks == NULL)
		return (print_failed_error(), false);
	*philos = philo_init(*data);
	if (*philos == NULL)
		return (print_failed_error(), false);
	return (true);
}
