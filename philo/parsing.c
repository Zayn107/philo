/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalissa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:58:57 by aalissa           #+#    #+#             */
/*   Updated: 2024/08/10 18:01:08 by aalissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static inline bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || 32 == c);
}

static char	*valid_input(char *str)
{
	int		t;
	int		len;
	char	*nbr;

	len = 0;
	t = 1;
	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		t = err_exit("only positives allowed");
	if (!is_digit(*str))
		t = err_exit("only positive numbers allowed");
	nbr = str;
	while (is_digit(*str++))
		++len;
	if (len > 10)
		t = err_exit("values must not be bigger than INT_MAX");
	if (t != -1)
		return (nbr);
	return (NULL);
}

static long	ft_atol(char *str)
{
	long	nbr;

	nbr = 0;
	if (valid_input(str))
		str = valid_input(str);
	while (is_digit(*str))
		nbr = nbr * 10 + *str++ - '0';
	if (nbr > INT_MAX)
	{
		err_exit("values must not be bigger than INT_MAX \n");
		return (-1);
	}
	return (nbr);
}

void	parse_input(t_table *table, char **v)
{
	table->philos_count = ft_atol(v[1]);
	table->time_to_die = ft_atol(v[2]) * 1e3;
	table->time_to_eat = ft_atol(v[3]) * 1e3;
	table->time_to_sleep = ft_atol(v[4]) * 1e3;
	if (table->time_to_sleep < 6e4
		|| table->time_to_eat < 6e4
		|| table->time_to_die < 6e4)
	{
		err_exit("times must be more than 60ms");
		return ;
	}
	else if (0 >= table->philos_count)
	{
		err_exit("At least 1 philo");
		return ;
	}
	if (v[5])
		table->meals_limit_nbr = ft_atol(v[5]);
	else
		table->meals_limit_nbr = -1;
}
