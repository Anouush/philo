/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angalsty <angalsty@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:45:35 by angalsty          #+#    #+#             */
/*   Updated: 2023/04/03 17:52:40 by angalsty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*unlocker(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	return (NULL);
}

void	ft_join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_join(data->ph_threads[i], NULL);
		i++;
	}
	pthread_join(*data->monitor, NULL);
	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->writing);
	pthread_mutex_destroy(&data->checking);
	free(data->philo);
	free(data->forks);
	free(data->ph_threads);
	free(data->monitor);
}

void	ft_threads_init(t_data *data)
{
	int			i;
	pthread_t	*threads;
	pthread_t	*checker;

	checker = NULL;
	data->start_time = get_time();
	i = 0;
	threads = malloc(sizeof(pthread_t) * (data->n_philo + 1));
	checker = malloc(sizeof(pthread_t) * 2);
	pthread_create(checker, NULL, ft_monitor, (void *)data);
	while (i < data->n_philo)
	{
		pthread_create(&threads[i], NULL, ft_routine, (void *)&data->philo[i]);
		i++;
	}
	data->ph_threads = threads;
	data->monitor = checker;
}
