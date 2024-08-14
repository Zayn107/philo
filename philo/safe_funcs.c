/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalissa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:59:52 by aalissa           #+#    #+#             */
/*   Updated: 2024/08/10 18:01:22 by aalissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (!ret)
		err_exit("malloc error\n ");
	return (ret);
}

static void	handle_mutex_err(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (EINVAL == status && (opcode == LOCK
			|| opcode == UNLOCK
			|| opcode == DESTROY))
		err_exit("The value in mutex is invalid\n");
	else if (EINVAL == status && INIT == opcode)
		err_exit("The value in attr is invalid\n");
	else if (EDEADLK == status)
		err_exit("A deadlock will occur if the \
				thread blocked waiting for mutex\n");
	else if (EPERM == status)
		err_exit("The current thread doesn't hold a lock on mutex\n");
	else if (ENOMEM == status)
		err_exit("The proccess can't allocate enough \
				memory to creat another mutex\n");
	else if (EBUSY == status)
		err_exit("Mutex is locked\n ");
}

void	safe_mutex_handle(t_mtx *mtx, t_opcode opcode)
{
	if (LOCK == opcode)
		handle_mutex_err(pthread_mutex_lock(mtx), opcode);
	else if (UNLOCK == opcode)
		handle_mutex_err(pthread_mutex_unlock(mtx), opcode);
	else if (INIT == opcode)
		handle_mutex_err(pthread_mutex_init(mtx, NULL), opcode);
	else if (DESTROY == opcode)
		handle_mutex_err(pthread_mutex_destroy(mtx), opcode);
	else
		err_exit("wrong mutex opcode \n");
}

static void	handle_thread_err(int status, t_opcode opcode)
{
	if (0 == status)
		return ;
	else if (EAGAIN == status)
		err_exit("No resources to creat another thread \n ");
	else if (EPERM == status)
		err_exit("The caller doesn't have permission\n");
	else if (EINVAL == status && CREATE == opcode)
		err_exit("The value specified by attr is invalid\n");
	else if (EINVAL == status && (JOIN == opcode || DETACH == opcode))
		err_exit("The value specified by thread isn't joinable\n");
	else if (ESRCH == status)
		err_exit("No thread could be found corresponding \
				to that specified thread ID \n");
	else if (EDEADLK == status)
		err_exit(" A deadlock was detected \n");
}

void	safe_thread_handle(pthread_t *thread, void *(*func)(void *), \
		void *data, t_opcode opcode)
{
	if (CREATE == opcode)
		handle_thread_err(pthread_create(thread, NULL, func, data), opcode);
	else if (JOIN == opcode)
		handle_thread_err(pthread_join(*thread, NULL), opcode);
	else if (DETACH == opcode)
		handle_thread_err(pthread_detach(*thread), opcode);
	else
		err_exit("wrong opcode for thread handle\n use:\
			       	CREAT, JOIN, DETACH, \n");
}
