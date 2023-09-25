/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:24:16 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/26 00:03:32 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	main_exe(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	data->start_time = get_milli_sec() + (long)1000;
	while (i < data->nbr_of_philo)
	{
		philos[i].next_eat = data->start_time + data->time_to_die;
		if (pthread_create(&philos[i].thread, NULL,
				(void *)routine, (void *)&philos[i]) != 0)
			return (print_failed_error(), false);
		i++;
	}
	monitoring(philos);
	i = 0;
	while (i < data->nbr_of_philo)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			return (print_failed_error(), false);
		i++;
	}
	destroy_all(data, philos);
	return (true);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	*philos;

	if (argc == 5 || argc == 6)
	{
		if (!check_data(argc, argv))
			return (print_args_error(), EXIT_FAILURE);
		if (!all_init(&data, &philos, argc, argv))
			return (EXIT_FAILURE);
		if (!main_exe(data, philos))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	else
		return (print_args_error(), EXIT_FAILURE);
}
