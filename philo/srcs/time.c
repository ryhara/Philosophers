/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 10:45:49 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/26 00:07:01 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_micro_sec(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		ft_puterr("gettimeofday() error\n");
	return (time.tv_sec * (long)1000000 + time.tv_usec);
}

long	get_milli_sec(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		ft_puterr("gettimeofday() error\n");
	return (time.tv_sec * (long)1000 + time.tv_usec / (long)1000);
}

long	milli_to_micro(long ms)
{
	return (ms * (long)1000);
}

void	usleep_philo(long us)
{
	long	start_time;
	long	current_time;

	start_time = get_micro_sec();
	while (1)
	{
		current_time = get_micro_sec();
		if (current_time - start_time >= us)
			break ;
		usleep(100);
	}
}

void	until_start(long ms)
{
	long	time;

	while (1)
	{
		time = get_milli_sec();
		if (time >= ms)
			break ;
		usleep(100);
	}
}
