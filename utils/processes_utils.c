/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipavlov <ipavlov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:37:46 by ipavlov           #+#    #+#             */
/*   Updated: 2025/02/15 13:30:22 by ipavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	check_access(char *path, char **find_envp_path)
{
	if (access(path, F_OK) == 0)
	{
		ft_free_array(find_envp_path);
		return (1);
	}
	return (0);
}

char	*path_determine(char **find_envp_path, char *cmd)
{
	char	*true_path;
	char	*path;
	int		i;

	i = 0;
	while (find_envp_path[i])
	{
		true_path = ft_strjoin(find_envp_path[i], "/");
		if (true_path == NULL)
			ft_s_free_exit(true_path);
		path = ft_strjoin(true_path, &cmd[0]);
		ft_free(true_path);
		if (path == NULL)
			ft_s_free_exit(path);
		if (check_access(path, find_envp_path) == 1)
			return (path);
		ft_free(path);
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, char **envp)
{
	char	**find_envp_path;
	char	*path;
	int		i;

	find_envp_path = NULL;
	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (!envp[i])
		ft_error(13);
	find_envp_path = ft_split(envp[i] + 5, ':');
	if (find_envp_path == NULL)
		ft_b_free_exit(find_envp_path);
	path = path_determine(find_envp_path, cmd);
	if (path)
		return (path);
	ft_free_array(find_envp_path);
	return (NULL);
}

void	prepare_execution(char argv[], char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	if (cmd == NULL)
	{
		ft_free_array(cmd);
		ft_error(12);
	}
	if (cmd[0] && cmd[0][0] == '/')
		path = cmd[0];
	else
		path = find_path(cmd[0], envp);
	if (path == 0)
	{
		ft_free_array(cmd);
		ft_error(127);
	}
	if (execve(path, cmd, envp) == -1)
	{
		ft_free_array(cmd);
		ft_error(10);
	}
}
