/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalissa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:05:42 by aalissa           #+#    #+#             */
/*   Updated: 2024/08/14 17:31:09 by aalissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mtx, &table->threads_ready))
		usleep(1);
}

bool	all_threads_running(t_mtx *mtx, long *threads, long philos_count)
{
	bool	ret;

	ret = false;
	safe_mutex_handle(mtx, LOCK);
	if (*threads == philos_count)
		ret = true;
	safe_mutex_handle(mtx, UNLOCK);
	return (ret);
}

void	de_sync_philos(t_philo *philo)
{
	if (philo->table->philos_count % 2 == 0)
	{
		if (philo->id % 2 == 0)
			ft_usleep(3e4, philo->table);
	}
	else
	{
		if (philo->id % 2)
			think(philo, true);
	}
}

void	increase_long(t_mtx *mtx, long *value)
{
	safe_mutex_handle(mtx, LOCK);
	(*value)++;
	safe_mutex_handle(mtx, UNLOCK);
}
