/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angalsty <angalsty@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:17:28 by angalsty          #+#    #+#             */
/*   Updated: 2023/04/02 20:40:14 by angalsty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_philos_init(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * (data->n_philo + 1));
	while (i < data->n_philo)
	{
		data->philo[i].left_fork = i;
		data->philo[i].right_fork = i + 1;
		data->philo[i].meals = 0;
		data->philo[i].index = i;
		data->philo[i].data = data;
		data->philo[i].last_meal = data->start_time;
		i++;
	}
	data->philo[data->n_philo - 1].right_fork = 0;
}

void	ft_mutex_init(t_data *data)
{
	int	i;

	i = -1;
	data->forks = calloc(sizeof(pthread_mutex_t), (data->n_philo + 1));
	while (++i < data->n_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	pthread_mutex_init(&data->writing, NULL);
	pthread_mutex_init(&data->checking, NULL);
}

void	ft_init_args(t_data *data, int argc, char **argv)
{
	data->run = 1;
	data->n_philo = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	data->n_meals = -1;
	if (argc == 6)
		data->n_meals = ft_atol(argv[5]);
}
