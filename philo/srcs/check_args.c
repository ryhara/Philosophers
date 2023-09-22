/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:49:20 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/22 23:41:37 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_number(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '\0')
		return (false);
	while (str[i])
	{
		if (('0' <= str[i] && str[i] <= '9'))
			i++;
		else
			return (false);
	}
	return (true);
}

bool	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_number(argv[i]))
			return (false);
		i++;
	}
	return (true);
}

int	ft_atoi(char *str)
{
	int		i;
	long	num;

	i = 0;
	num = 0;
	if (str == NULL)
		return (-1);
	while (str[i])
	{
		if (('0' <= str[i] && str[i] <= '9'))
		{
			num = num * 10 + (str[i] - '0');
			i++;
		}
		else
			return (-1);
		if (num > INT_MAX)
			return (-1);
	}
	return ((int)num);
}

bool	check_data(int argc, char **argv)
{
	int	i;
	int	num;

	i = 1;
	if (!check_args(argc, argv))
		return (false);
	while (i < argc)
	{
		num = ft_atoi(argv[i]);
		if (num <= 0)
			return (false);
		i++;
	}
	return (true);
}
