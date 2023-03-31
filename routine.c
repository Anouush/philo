/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angalsty <angalsty@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 21:57:56 by angalsty          #+#    #+#             */
/*   Updated: 2023/03/31 22:55:01 by angalsty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_get_fork(t_philo *philo)
{
	if ((philo->index + 1) % 2 == 0)
	{
		//printf("My index is %d and im waiting for %d\n", philo->index, philo->left_fork);
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		if (philo->counted == 1 || philo->data->run != 1 || ft_check_die(philo) == 1)
			return (1);
		ft_print_action(philo, "has taken a fork\n");
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		if (philo->counted == 1 || philo->data->run != 1 || ft_check_die(philo) == 1)
			return (1);
		ft_print_action(philo, "has taken a fork\n");
	}
	else
	{
		//printf("My index is %d and im waiting for %d\n", philo->index, philo->right_fork);
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		if (philo->counted == 1 || philo->data->run != 1 || ft_check_die(philo) == 1)
			return (1);
		ft_print_action(philo, "has taken a fork\n");
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		if (philo->counted == 1 || philo->data->run != 1 || ft_check_die(philo) == 1)
			return (1);
		ft_print_action(philo, "has taken a fork\n");
	}
	return (0);
}

void	ft_eat(t_philo *philo)
{
	if (ft_get_fork(philo) == 1)
		return ;
	if (philo->counted == 1 || philo->data->run != 1 || ft_check_die(philo) == 1)
		return ;
	ft_print_action(philo, "is eating\n");
	philo->meals += 1;
	philo->last_meal = get_time();
	ft_usleep(philo, philo->data->time_to_eat);
	if (philo->counted == 1 || philo->data->run != 1 || ft_check_die(philo) == 1)
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
		if (philo->counted == 1 || philo->data->run != 1 || ft_check_die(philo) == 1)
			break ;
		ft_eat(philo);
		if (philo->counted == 1 || philo->data->run != 1 || ft_check_die(philo) == 1)
			break ;
		ft_sleep(philo);
		if (philo->counted == 1 || philo->data->run != 1 || ft_check_die(philo) == 1)
			break ;
		ft_think(philo);
	}
	return (unlocker(philo));
}
