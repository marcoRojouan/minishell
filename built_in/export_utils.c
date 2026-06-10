/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavaud <malavaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 11:53:20 by malavaud          #+#    #+#             */
/*   Updated: 2026/06/10 11:56:24 by malavaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

int	check_key(char *key)
{
	if (!valid_key(key))
	{
		printf("export: `%s': not a valid identifier\n", key);
		return (0);
	}
	return (1);
}
