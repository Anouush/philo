/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angalsty <angalsty@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 22:01:58 by angalsty          #+#    #+#             */
/*   Updated: 2023/03/31 23:01:08 by angalsty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_die(t_philo *philo)
{
	if (get_time() - philo->last_meal > philo->data->time_to_die)
	{
		ft_print_action(philo, "died\n");
		philo->data->run = 0;
       // philo->data->dead = 1;
		return(1);
	}
	return(0);
}

void	ft_is_full(t_philo *philo)
{
	if (philo->meals >= philo->data->n_meals && philo->data->n_meals != -1 && philo->counted == 0)
	{
		philo->data->finished++;
		philo->counted = 1;
	}
}

void ft_super_unlocker(t_data *data)
{
	int i = 0;
	while(i < data->n_philo)
		unlocker(&data->philo[i++]);
}

int ft_all_full(t_data *data)
{
	int i = 0;

	while(i < data->n_philo)
	{
		if(data->philo[i].counted == 0)
			return(0);
		i++;
	}
	return(1);
}

void	*ft_monitor(void *param)
{
	t_data *data;
	int	i;

	data = param;
	while (1)
	{
		i = 0;
		while (i < data->n_philo)
		{
			ft_is_full(&data->philo[i]);
			if(ft_all_full(data))
            {
				write(1, "here\n", 5);
				data->run = 0;
				//ft_super_unlocker(data);
				return (NULL);
			}
			if (ft_check_die(&data->philo[i]))
			{
				printf("\nFINISHED = %d\n\n", data->finished);
				ft_super_unlocker(data);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}
