/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angalsty <angalsty@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 19:22:35 by angalsty          #+#    #+#             */
/*   Updated: 2023/04/02 20:39:48 by angalsty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define MAX_PHILO 200

typedef struct s_philo
{
	int				meals;
	int				index;
	time_t			last_meal;
	int				left_fork;
	int				right_fork;
	pthread_t		threads;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				n_philo;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				n_meals;
	int				run;
	time_t			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	writing;
	pthread_mutex_t	checking;
	pthread_t		*ph_threads;
	pthread_t		*monitor;
	t_philo			*philo;

}					t_data;

time_t				get_time(void);
int					ft_check_arg(t_data *data, int argc, char **argv);
int					ft_is_digit_str(char *str);
int					ft_atol(const char *str);
void				ft_init_args(t_data *data, int argc, char **argv);
void				ft_philos_init(t_data *data);
void				ft_mutex_init(t_data *data);
void				ft_threads_init(t_data *data);
void				*ft_routine(void *param);
int					ft_check_die(t_philo *philo);
void				ft_is_full(t_philo *philo);
void				ft_join_threads(t_data *data);
void				*ft_monitor(void *param);

void				ft_print_action(t_philo *philo, char *str);
void				ft_usleep(t_philo *philo, long time);
int					ft_get_fork(t_philo *philo);
void				ft_eat(t_philo *philo);
void				ft_sleep(t_philo *philo);
void				ft_think(t_philo *philo);
void				*unlocker(t_philo *philo);
int					ft_continue_condition(t_philo *philo);

#endif