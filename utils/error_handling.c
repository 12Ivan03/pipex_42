/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:31:33 by ipavlov           #+#    #+#             */
/*   Updated: 2025/02/15 11:45:17 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_error(int c)
{
	if (c == 5)
		perror("Pipe failed");
	else if (c == 6)
		perror("Fork failed");
	else if (c == 7)
	{
		ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
		perror("Not currect arguments");
	}
	else if (c == 8)
		perror("Open failed");
	else if (c == 127)
		perror("Command not found");
	else if (c == 10)
		perror("Execve error");
	else if (c == 11)
		perror("Child process failed");
	else if (c == 12)
		perror("Malloc failed");
	else if (c == 13)
		perror("envp failed");
	exit(c);
}

void	ft_b_free_exit(char **find_envp_path)
{
	ft_free_array(find_envp_path);
	ft_error(12);
}

void	ft_s_free_exit(char *ptr)
{
	ft_free(ptr);
	ft_error(12);
}
