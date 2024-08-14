/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalissa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:00:31 by aalissa           #+#    #+#             */
/*   Updated: 2024/08/10 18:00:40 by aalissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	err_exit(const char *err)
{
	printf("%s\n", err);
	return (-1);
}

long	get_time(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		err_exit("get time of day err/n");
	if (SECOND == time_code)
		return (tv.tv_sec + (tv.tv_usec) / 1e6);
	else if (MILLISECOND == time_code)
		return ((tv.tv_sec) * 1e3 + (tv.tv_usec) / 1e3);
	else if (MICROSECOND == time_code)
		return (1e6 *(tv.tv_sec) + tv.tv_usec);
	else
		err_exit("wrong time opcode/n");
	return (-1);
}

void	ft_usleep(long usec, t_table *table)
{
	long	rem;
	long	elapsed;
	long	start;

	start = get_time(MICROSECOND);
	while (get_time(MICROSECOND) - start < usec)
	{
		if (sim_finished(table))
			break ;
		elapsed = get_time(MICROSECOND) - start;
		rem = usec - elapsed;
		if (rem > 1e3)
			usleep(rem / 2);
		else
		{
			while (get_time(MICROSECOND) - start < usec)
				;
		}
	}
}

void	clean( t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->philos_count)
	{
		philo = table->philos + i;
		safe_mutex_handle(&philo->philo_mtx, DESTROY);
	}
	safe_mutex_handle(&table->table_mtx, DESTROY);
	safe_mutex_handle(&table->write_mtx, DESTROY);
	free(table->philos);
	free(table->forks);
}
