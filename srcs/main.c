/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:24:16 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/21 11:47:12 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_data(t_data *data)
{
	printf("nbr_of_philo: %d\n", data->nbr_of_philo);
	printf("time_to_die: %d\n", data->time_to_die);
	printf("time_to_eat: %d\n", data->time_to_eat);
	printf("time_to_sleep: %d\n", data->time_to_sleep);
	printf("nbr_of_eat: %d\n", data->nbr_of_eat);
}

void	print_philos(t_philo *philos, int nbr_of_philo)
{
	int	i;

	i = 0;
	while (i < nbr_of_philo)
	{
		printf("philos[%d].id: %d\n", i, philos[i].id);
		printf("philos[%d].nbr_of_eat: %d\n", i, philos[i].nbr_of_eat);
		printf("philos[%d].status: %d\n", i, philos[i].status);
		i++;
	}
}

void	main_argc5(t_data *data)
{
	struct timeval	time;
	t_philo			*philos;

	printf("argc == 5\n");
	get_current_time(&time);
	data->start_time = &time;
	philos = philo_init(data);
	if (philos == NULL)
		return (print_failed_error());
	print_philos(philos, data->nbr_of_philo);
}

void	main_argc6(t_data *data)
{
	struct timeval	time;

	get_current_time(&time);
	data->start_time = &time;
	printf("argc == 6\n");
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc == 5 || argc == 6)
	{
		if (!check_data(argc, argv))
			return (print_args_error(), EXIT_FAILURE);
		data = data_init(argc, argv);
		print_data(data);
		if (argc == 5)
			main_argc5(data);
		else if (argc == 6)
			main_argc6(data);
		return (EXIT_SUCCESS);
	}
	else
		return (print_args_error(), EXIT_FAILURE);
}
