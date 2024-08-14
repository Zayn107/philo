/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalissa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 16:42:44 by aalissa           #+#    #+#             */
/*   Updated: 2024/08/14 17:32:34 by aalissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int philo_pos)
{
	int	philo_nbr;

	philo_nbr = philo->table->philos_count;
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_pos];
		philo->second_fork = &forks[(philo_pos + 1) % philo_nbr];
	}
	else
	{
		philo->first_fork = &forks[(philo_pos + 1) % philo_nbr];
		philo->second_fork = &forks[philo_pos];
	}
}

static void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->philos_count)
	{
		philo = table->philos + i;
		philo->last_meal_time = 0;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		philo->table = table;
		safe_mutex_handle(&philo->philo_mtx, INIT);
		assign_forks(philo, table->forks, i);
	}
}

void	data_init(t_table *table)
{
	int	i;

	i = -1;
	table->start_sim = get_time(MILLISECOND);
	table->nbr_running_threads = 0;
	table->end_sim = false;
	table->threads_ready = false;
	safe_mutex_handle(&table->table_mtx, INIT);
	safe_mutex_handle(&table->write_mtx, INIT);
	table->philos = safe_malloc(sizeof(t_philo) * table->philos_count);
	table->forks = safe_malloc(sizeof(t_fork) * table->philos_count);
	while (++i < table->philos_count)
	{
		safe_mutex_handle(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
	}
	philo_init(table);
}
