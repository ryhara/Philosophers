/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:24:16 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/19 16:43:34 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

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
	printf("argc == 5\n");
}

void	main_argc6(t_data *data)
{
	printf("argc == 6\n");
}

int	main(int argc, char **argv)
{
	t_data	*data;

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
		return (0);
	}
	else
		return (print_args_error(), 1);
}
