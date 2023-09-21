/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:24:16 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/21 13:33:32 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	main_exe(t_data *data, t_philo *philos)
{
	printf("main_exe\n");
	if (data->nbr_of_eat == -1 && philos != NULL)
		printf("argc == 5\n");
	else
		printf("argc == 6\n");
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
		main_exe(data, philos);
		return (EXIT_SUCCESS);
	}
	else
		return (print_args_error(), EXIT_FAILURE);
}
