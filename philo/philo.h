/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalissa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:59:30 by aalissa           #+#    #+#             */
/*   Updated: 2024/08/10 17:59:36 by aalissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <pthread.h>

#define DEBUG_MODE 0

typedef struct s_table	t_table;
typedef pthread_mutex_t	t_mtx;

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}	t_fork;
typedef struct s_philo
{
	int			id;
	long		meals_counter;
	long		last_meal_time;
	bool		full;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	philo_thread;
	t_mtx		philo_mtx;
	t_table		*table;
}	t_philo;

typedef struct s_table
{
	long		philos_count;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		meals_limit_nbr;
	long		start_sim;
	long		nbr_running_threads;
	bool		end_sim;
	bool		threads_ready;
	pthread_t	monitor;
	t_mtx		table_mtx;
	t_mtx		write_mtx;
	t_philo		*philos;
	t_fork		*forks;
}	t_table;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}		t_status;
typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	CREATE,
	DESTROY,
	INIT,
	JOIN,
	DETACH,
}	t_opcode;

typedef enum e_time_code
{
	SECOND,
	MICROSECOND,
	MILLISECOND,
}		t_time_code;
///////////	utils.c
int		err_exit(const char *err);
long	get_time(t_time_code time_code);
void	ft_usleep(long usec, t_table *table);
void	clean( t_table *table);
//////////	parsing.c
void	parse_input(t_table *table, char **v);
//////////      data_init.c
void	data_init(t_table *table);
//////////      safe_funcs.c
void	*safe_malloc(size_t bytes);
void	safe_mutex_handle(t_mtx *mtx, t_opcode opcode);
void	safe_thread_handle(pthread_t *thread, void *(*func)(void *), \
		void *data, t_opcode opcode);
//////////      get_set.c
void	set_bool(t_mtx *mtx, bool *dest, bool set_to);
bool	get_bool(t_mtx *mtx, bool *value);
void	set_long(t_mtx *mtx, long *dest, long set_to);
long	get_long(t_mtx *mtx, long *value);
bool	sim_finished(t_table *table);
void	increase_long(t_mtx *mtx, long *value);
//////////      dinner.c
void	*dinner_sim(void *data);
void	dinner_start(t_table *table);
void	think(t_philo *philo, bool pre_sim);
//////////      sync.c
void	wait_all_threads(t_table *table);
bool	all_threads_running(t_mtx *mtx, long *threads, long philos_count);
void	de_sync_philos(t_philo *philo);
//////////      write_status.c
void	write_status(t_status status, t_philo *philo, bool debug);
//////////      monitor.c
void	*monitor_dinner(void *data);
