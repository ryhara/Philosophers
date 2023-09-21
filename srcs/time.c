/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 10:45:49 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/21 11:05:00 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_micro_sec(struct timeval *time)
{
	return (time->tv_sec * 1000000 + time->tv_usec);
}

size_t	get_milli_sec(struct timeval *time)
{
	return (time->tv_sec * 1000 + time->tv_usec / 1000);
}

size_t get_sec(struct timeval *time)
{
	return (time->tv_sec + time->tv_usec / 1000000);
}

void	get_current_time(struct timeval *time)
{

	if (gettimeofday(time, NULL) == -1)
	{
		write(2, "gettimeofday() error\n", 22);
		exit(ERROR);
	}
	printf("time.tv_sec: %ld\n", (*time).tv_sec);
	printf("time.tv_usec: %d\n", (*time).tv_usec);
	// return (time.tv_sec * 1000 + time.tv_usec / 1000);
}