/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavaud <malavaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 10:48:48 by malavaud          #+#    #+#             */
/*   Updated: 2026/05/05 11:27:52 by malavaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
export A=1 = ajoute/midifie
export = affiche env
export A = variable vide exportee
export A+=1 = concatene
*/

int	valid_key(char *key)
{
	int	i;

	if (!key || !key[0])
		return (0);
	if (!(ft_isalpha(key[0]) || key[0] == '_'))
		return (0);
	i = 1;
	while (key[i])
	{
		if (!(ft_isalnum(key[i]) || key[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}
 
static int	handle_plus(char **args, char ***env)
{
	char	*ptr;
	char	*key;
	char	*value;
	char	*old;
	char	*tmp;

	ptr = ft_strnstr(args[1], "+=", ft_strlen(args[1]));
	if (!ptr)
		return (0);
	key = ft_substr(args[1], 0, ptr - args[1]);
	value = ptr + 2;
	value = ptr + 2;
	if (!valid_key(key))
		return (printf("export: `%s': not a valid identifier\n", key), 1);
	old = get_env(*env, key);
	if (old)
	{
		tmp = ft_strjoin(old, value);
		set_env(env, key, tmp);
		free(tmp);
	}
	else
		set_env(env, key, value);
	return (1);
}

int	ft_export(char **args, char ***env)
{
	char	*ptr;
	char	*key;
	char	*value;

	if (!args[1])
	{
		ft_env(*env);
		return (0);
	}
	if (handle_plus(args, env))
		return (0);
	ptr = ft_strchr(args[1], '=');
	if (ptr)
	{
		key = ft_substr(args[1], 0, ptr - args[1]);
		value = ptr + 2;
		value = ptr + 1;
		if (!valid_key(key))
			return (printf("export: `%s': not a valid identifier\n", key), 1);
		set_env(env, key, value);
		return (0);
	}
	key = args[1];
	if (!valid_key(key))
		return (printf("export: `%s': not a valid identifier\n", key), 1);
	set_env(env, key, "");
	return (0);
}