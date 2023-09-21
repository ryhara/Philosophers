/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 10:45:49 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/21 11:50:28 by ryhara           ###   ########.fr       */
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

size_t	get_sec(struct timeval *time)
{
	return (time->tv_sec + time->tv_usec / 1000000);
}

void	get_current_time(struct timeval *time)
{
	if (gettimeofday(time, NULL) == -1)
	{
		ft_puterr("gettimeofday() error\n");
		exit(ERROR);
	}
}
