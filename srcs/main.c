/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:24:16 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/19 17:25:31 by ryhara           ###   ########.fr       */
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

void	main_argc5(t_data *data)
{
	(void)data;
	printf("argc == 5\n");
}

void	main_argc6(t_data *data)
{
	(void)data;
	printf("argc == 6\n");
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	printf("time.tv_sec: %ld\n", time.tv_sec);
	printf("time.tv_usec: %d\n", time.tv_usec);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	get_current_time();
	if (argc == 5 || argc == 6)
	{
		if (!check_data(argc, argv))
			return (print_args_error(), 1);
		data = data_init(argc, argv);
		print_data(data);
		if (argc == 5)
			main_argc5(data);
		else if (argc == 6)
			main_argc6(data);
		get_current_time();
		return (0);
	}
	else
		return (print_args_error(), 1);
}
