/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angalsty <angalsty@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 22:01:58 by angalsty          #+#    #+#             */
/*   Updated: 2023/04/03 18:41:23 by angalsty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->checking);
	if (get_time() - philo->last_meal > philo->data->time_to_die)
	{
		if (philo->data->n_meals != -1 && philo->meals >= philo->data->n_meals)
		{
			return (0);
		}
		pthread_mutex_unlock(&philo->data->checking);
		ft_print_action(philo, "died\n");
		pthread_mutex_lock(&philo->data->checking);
		philo->data->run = 0;
		pthread_mutex_unlock(&philo->data->checking);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->checking);
	return (0);
}

void	*ft_super_unlocker(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
		unlocker(&data->philo[i++]);
	return (NULL);
}

int	ft_has_eat_n(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->checking);
	if (philo->meals < philo->data->n_meals)
	{
		pthread_mutex_unlock(&philo->data->checking);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->checking);
	return (0);
}

void	*ft_monitor(void *param)
{
	t_data	*data;
	int		i;
	int		one_not_finish;

	data = param;
	while (1)
	{
		one_not_finish = 0;
		i = 0;
		while (i < data->n_philo)
		{
			if (data->n_meals != -1 && one_not_finish == 0)
				one_not_finish = ft_has_eat_n(&data->philo[i]);
			if (ft_check_die(&data->philo[i]))
				return (ft_super_unlocker(data));
			i++;
		}
		if (data->n_meals != -1 && one_not_finish == 0)
			return (NULL);
	}
	return (NULL);
}
