/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angalsty <angalsty@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:45:35 by angalsty          #+#    #+#             */
/*   Updated: 2023/03/31 20:32:11 by angalsty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*unlocker(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	return (NULL);
}

/*int	ft_check_die(t_philo *philo)
{
	long	meal_limit;

	meal_limit = philo->last_meal + philo->data->time_to_die;
	if (meal_limit < get_time())
	{
		philo->data->dead = 1;
		return (1);
	}
	//else if (philo->data->dead == 1)
		//return (1);
	else if (philo->meals > philo->data->n_meals && philo->data->n_meals != -1)
	//else if (philo->meals >= philo->data->n_meals && philo->data->n_meals != -1)
		{
			philo->data->dead = 1;
			return (1);
		}
	return (0);
}*/

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
	free(data->philo);
	free(data->forks);
	free(data->ph_threads);
	free(data->monitor);
}

void	ft_threads_init(t_data *data)
{
	int			i;
	pthread_t	*threads;
	pthread_t	*checker = NULL;

	data->start_time = get_time();
	i = 0;
	threads = malloc(sizeof(pthread_t) * (data->n_philo + 1));
	checker = malloc(sizeof(pthread_t) * 2);
	while (i < data->n_philo)
	{
		pthread_create(&threads[i], NULL, ft_routine, (void *)&data->philo[i]);
		i++;
	}
	pthread_create(checker, NULL, ft_monitor, (void *)data);
	data->ph_threads = threads;
	data->monitor = checker;
}
