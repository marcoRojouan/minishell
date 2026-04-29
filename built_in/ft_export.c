/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavaud <malavaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 10:48:48 by malavaud          #+#    #+#             */
/*   Updated: 2026/04/29 15:46:57 by malavaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
export A=1 = ajoute/midifie
export = affiche env
export A = variable vide exportee
export A+=1 = concatene
*/

static int	valid_key(char *key)
{
	int	i;

	if (!key || key[0])
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
 
int	ft_export(char **args,char **env)
{
	char	*key;
	char	*value;
	char	*ptr;

	//key = 0;
	//value = 0;
	if (!args[0])
		return (0);
	
}
