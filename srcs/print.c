/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:38:36 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/21 19:56:13 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	ft_puterr(char *str)
{
	write(2, str, ft_strlen(str));
}

void	print_args_error(void)
{
	ft_puterr("\033[31mError: Invalid arguments\n\033[0m");
	ft_puterr("\033[1;34mUsage:\033[0m ./philo number_of_philosophers ");
	ft_puterr("time_to_die time_to_eat time_to_sleep ");
	ft_puterr("[number_of_times_each_philosopher_must_eat]\n");
	ft_puterr("Please enter a positive int number and time[milli sec]\n");
}

void	print_failed_error(void)
{
	ft_puterr("\033[31mError: malloc() failed\033[0m");
	ft_puterr(" or \033[31mpthread failed\n\033[0m");
}

void	print_state(t_philo *philo, char *state)
{
	long	time;

	time = get_milli_sec() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->print);
	pthread_mutex_lock(&philo->data->status);
	if (philo->data->is_dead == false)
	{
		printf("%ld %d %s", time, philo->id, state);
		if (philo->status == DIED)
			philo->data->is_dead = true;
	}
	pthread_mutex_unlock(&philo->data->status);
	pthread_mutex_unlock(&philo->data->print);
}
