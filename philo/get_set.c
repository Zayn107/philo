/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalissa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 16:50:27 by aalissa           #+#    #+#             */
/*   Updated: 2024/08/10 16:52:22 by aalissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(t_mtx *mtx, bool *dest, bool set_to)
{
	safe_mutex_handle(mtx, LOCK);
	*dest = set_to;
	safe_mutex_handle(mtx, UNLOCK);
}

bool	get_bool(t_mtx *mtx, bool *value)
{
	bool	ret;

	safe_mutex_handle(mtx, LOCK);
	ret = *value;
	safe_mutex_handle(mtx, UNLOCK);
	return (ret);
}

void	set_long(t_mtx *mtx, long *dest, long set_to)
{
	safe_mutex_handle(mtx, LOCK);
	*dest = set_to;
	safe_mutex_handle(mtx, UNLOCK);
}

long	get_long(t_mtx *mtx, long *value)
{
	long	ret;

	safe_mutex_handle(mtx, LOCK);
	ret = *value;
	safe_mutex_handle(mtx, UNLOCK);
	return (ret);
}

bool	sim_finished(t_table *table)
{
	return (get_bool(&table->table_mtx, &table->end_sim));
}
