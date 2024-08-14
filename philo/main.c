/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalissa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:58:30 by aalissa           #+#    #+#             */
/*   Updated: 2024/08/10 17:58:35 by aalissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int c, char **v)
{
	t_table	table;

	if (5 == c || 6 == c)
	{
		parse_input(&table, v);
		data_init(&table);
		dinner_start(&table);
		clean(&table);
	}
	else
	{
		printf("wrong input\n");
		err_exit("correct input is: \n \t./philo 5 800 200 200 [5]");
	}
	return (0);
}
