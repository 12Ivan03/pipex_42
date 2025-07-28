/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:18:54 by ipavlov           #+#    #+#             */
/*   Updated: 2025/02/15 11:22:07 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include "../libft/libft.h"

void	ft_error(int c);
void	prepare_execution(char argv[], char **envp);
void	ft_free(char *search_which_path);
void	ft_free_array(char **arr);
void	ft_b_free_exit(char **find_envp_path);
void	ft_s_free_exit(char *ptr);

#endif
