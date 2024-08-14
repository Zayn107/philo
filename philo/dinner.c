/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalissa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 16:44:38 by aalissa           #+#    #+#             */
/*   Updated: 2024/08/10 16:50:16 by aalissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *philo, bool pre_sim)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!pre_sim)
		write_status(THINKING, philo, DEBUG_MODE);
	if (philo->table->philos_count % 2 == 0)
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = t_eat * 2 - t_sleep;
	if (t_think < 0)
		t_think = 0;
	ft_usleep(t_think * 0.36, philo->table);
}

void	*lone_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mtx, &philo->last_meal_time, get_time(MILLISECOND));
	increase_long(&philo->table->table_mtx, &philo->table->nbr_running_threads);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	while (!sim_finished(philo->table))
		usleep(200);
	return (NULL);
}

static void	eat(t_philo *philo)
{
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
	set_long(&philo->philo_mtx, &philo->last_meal_time, \
			get_time(MILLISECOND));
	philo->meals_counter++;
	write_status(EATING, philo, DEBUG_MODE);
	ft_usleep(philo->table->time_to_eat, philo->table);
	if ((philo->table->meals_limit_nbr > 0) \
		&& (philo->meals_counter == philo->table->meals_limit_nbr))
		set_bool(&philo->philo_mtx, &philo->full, true);
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}

void	*dinner_sim(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mtx, &philo->last_meal_time, \
			philo->table->start_sim);
	increase_long(&philo->table->table_mtx, \
			&philo->table->nbr_running_threads);
	de_sync_philos(philo);
	while (!sim_finished(philo->table))
	{
		if (true == get_bool(&philo->philo_mtx, &philo->full))
			break ;
		eat(philo);
		write_status(SLEEPING, philo, DEBUG_MODE);
		ft_usleep(philo->table->time_to_sleep, philo->table);
		think(philo, false);
	}
	return (NULL);
}

void	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (0 == table->meals_limit_nbr)
		return ;
	else if (1 == table->philos_count)
		safe_thread_handle(&table->philos[0].philo_thread, \
				lone_philo, &table->philos[0], CREATE);
	else
	{
		while (++i < table->philos_count)
		{
			safe_thread_handle(&table->philos[i].philo_thread, dinner_sim,
				&table->philos[i], CREATE);
		}
	}
	safe_thread_handle(&table->monitor, monitor_dinner, table, CREATE);
	table->start_sim = get_time(MILLISECOND);
	set_bool(&table->table_mtx, &table->threads_ready, true);
	i = -1;
	while (++i < table->philos_count)
		safe_thread_handle(&table->philos[i].philo_thread, NULL, NULL, JOIN);
	set_bool(&table->table_mtx, &table->end_sim, true);
	safe_thread_handle(&table->monitor, NULL, NULL, JOIN);
}
