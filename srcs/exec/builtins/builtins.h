/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dowon <dowon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 21:36:53 by dowon             #+#    #+#             */
/*   Updated: 2023/08/13 16:25:03 by dowon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include <stdlib.h>
// 꼭 삭제하기
int			check_valid_identifier(char *str);

int			builtin_cd(char **args);
int			builtin_echo(char **args);
int			builtin_env(char **args);
int			builtin_exit(char **args);
int			builtin_export(char **args);
int			builtin_pwd(char **args);
int			builtin_unset(char **args);
size_t		count_args(char **args);

#endif