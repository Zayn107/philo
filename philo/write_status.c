/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalissa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:13:29 by aalissa           #+#    #+#             */
/*   Updated: 2024/08/10 17:18:57 by aalissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	write_status_debug(t_status status, t_philo *philo, long elapsed)
{
	if ((TAKE_FIRST_FORK == status) && (!sim_finished(philo->table)))
		printf("%-6ld		%d has taken first fork\t%d\t\n",
			elapsed, philo->id, philo->first_fork->fork_id);
	else if ((TAKE_SECOND_FORK == status) && (!sim_finished(philo->table)))
		printf("%-6ld		%d has taken second fork\t%d\t\n",
			elapsed, philo->id, philo->second_fork->fork_id);
	else if ((EATING == status) && (!sim_finished(philo->table)))
		printf("%-6ld		%d is eating\t%ld\t\n",
			elapsed, philo->id, philo->meals_counter);
	else if ((SLEEPING == status) && (!sim_finished(philo->table)))
		printf("%-6ld		%d is sleeping\n", elapsed, philo->id);
	else if ((THINKING == status) && (!sim_finished(philo->table)))
		printf("%-6ld		%d is thinking\n", elapsed, philo->id);
	else if (DIED == status)
		printf("%-6ld		%d is dead\n", elapsed, philo->id);
}

void	write_status(t_status status, t_philo *philo, bool debug)
{
	long	elapsed;

	elapsed = get_time(MILLISECOND) - philo->table->start_sim;
	if (philo->full)
		return ;
	safe_mutex_handle(&philo->table->write_mtx, LOCK);
	if (debug)
		write_status_debug(status, philo, elapsed);
	else
	{
		if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
			&& (!sim_finished(philo->table)))
			printf("%-6ld		%d has taken a fork\n", elapsed, philo->id);
		else if ((EATING == status) && (!sim_finished(philo->table)))
			printf("%-6ld		%d is eating\n", elapsed, philo->id);
		else if ((SLEEPING == status) && (!sim_finished(philo->table)))
			printf("%-6ld		%d is sleeping\n", elapsed, philo->id);
		else if ((THINKING == status) && (!sim_finished(philo->table)))
			printf("%-6ld		%d is thinking\n", elapsed, philo->id);
		else if (DIED == status)
			printf("%-6ld		%d is dead\n", \
					elapsed, philo->id);
	}
	safe_mutex_handle(&philo->table->write_mtx, UNLOCK);
}
