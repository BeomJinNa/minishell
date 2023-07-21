/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 22:00:37 by dowon             #+#    #+#             */
/*   Updated: 2023/07/21 23:00:03 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include <stdlib.h>

int		builtin_echo(char **args);
int		builtin_cd(char **args);
int		builtin_pwd(char **args);
int		builtin_export(char **args);
int		builtin_unset(char **args);
int		builtin_env(char **args);
int		builtin_exit(char **args);
size_t	count_args(char **args);

#endif