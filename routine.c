/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angalsty <angalsty@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 21:57:56 by angalsty          #+#    #+#             */
/*   Updated: 2023/04/03 18:06:29 by angalsty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_continue_condition(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->checking);
	if ((philo->meals >= philo->data->n_meals && philo->data->n_meals != -1)
		|| philo->data->run == 0)
	{
		pthread_mutex_unlock(&philo->data->checking);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->checking);
	return (0);
}

int	ft_get_fork(t_philo *philo)
{
	if ((philo->index + 1) % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		if (ft_continue_condition(philo))
			return (1);
		ft_print_action(philo, "has taken a fork\n");
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		if (ft_continue_condition(philo))
			return (1);
		ft_print_action(philo, "has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		if (ft_continue_condition(philo))
			return (1);
		ft_print_action(philo, "has taken a fork\n");
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		if (ft_continue_condition(philo))
			return (1);
		ft_print_action(philo, "has taken a fork\n");
	}
	return (0);
}

void	ft_eat(t_philo *philo)
{
	if (ft_get_fork(philo) == 1)
		return ;
	if (ft_continue_condition(philo))
		return ;
	ft_print_action(philo, "is eating\n");
	pthread_mutex_lock(&philo->data->checking);
	philo->meals += 1;
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->checking);
	ft_usleep(philo, philo->data->time_to_eat);
	if (ft_continue_condition(philo))
		return ;
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

void	ft_think(t_philo *philo)
{
	ft_print_action(philo, "is thinking\n");
}

void	*ft_routine(void *param)
{
	t_philo	*philo;

	philo = param;
	while (1)
	{
		if (ft_continue_condition(philo))
			break ;
		ft_eat(philo);
		if (ft_continue_condition(philo))
			break ;
		ft_sleep(philo);
		if (ft_continue_condition(philo))
			break ;
		ft_think(philo);
	}
	return (unlocker(philo));
}
