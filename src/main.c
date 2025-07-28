/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:20:07 by ipavlov           #+#    #+#             */
/*   Updated: 2025/02/15 12:48:51 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child_process(char *argv[], char **envp, int *fd)
{
	int	file_one;

	file_one = open(argv[1], O_RDONLY);
	if (file_one == -1)
		ft_error(8);
	if (dup2(fd[1], 1) < 0)
		perror("dup2 error");
	if (dup2(file_one, 0) < 0)
		perror("dup2 error");
	close(fd[0]);
	close(fd[1]);
	close(file_one);
	prepare_execution(argv[2], envp);
}

void	parent_process(char *argv[], char **envp, int *fd)
{
	int	file_two;

	file_two = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_two == -1)
		ft_error(8);
	if (dup2(fd[0], 0) < 0)
		perror("dup2 error");
	if (dup2(file_two, 1) < 0)
		perror("dup2 error");
	close(fd[1]);
	close(fd[0]);
	close(file_two);
	prepare_execution(argv[3], envp);
}

int	check_cmd(char *argv[])
{
	int	i;

	i = 1;
	while (i < 5)
	{
		if (argv[i][0] == '\0')
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char *argv[], char **envp)
{
	int		fd[2];
	pid_t	pid;
	int		check;
	int		status;

	if (argc == 5)
	{
		check = check_cmd(argv);
		if (check)
			ft_error(127);
		if (pipe(fd) == -1)
			ft_error(5);
		pid = fork();
		if (pid == -1)
			ft_error(6);
		if (pid == 0)
			child_process(argv, envp, fd);
		waitpid(pid, &status, WNOHANG);
		if (status < -1)
			ft_error(6);
		parent_process(argv, envp, fd);
	}
	else
		ft_error(7);
	return (0);
}
