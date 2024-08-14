/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalissa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 16:53:24 by aalissa           #+#    #+#             */
/*   Updated: 2024/08/14 17:30:15 by aalissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	time_to_die;

	if (get_bool(&philo->philo_mtx, &philo->full))
		return (false);
	elapsed = (get_time(MILLISECOND) - \
			get_long(&philo->philo_mtx, &philo->last_meal_time));
	time_to_die = philo->table->time_to_die / 1e3;
	if (elapsed > time_to_die)
		return (true);
	return (false);
}

void	*monitor_dinner(void *data)
{
	int		i;
	t_table	*table;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mtx, \
			&table->nbr_running_threads, table->philos_count))
		usleep(1);
	while (!sim_finished(table))
	{
		i = -1;
		while (++i < table->philos_count && !sim_finished(table))
		{
			if (philo_died(table->philos + i))
			{
				set_bool(&table->table_mtx, &table->end_sim, true);
				write_status(DIED, table->philos + i, DEBUG_MODE);
			}
			usleep(1);
		}
	}
	return (NULL);
}
