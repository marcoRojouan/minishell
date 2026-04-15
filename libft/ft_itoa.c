/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 14:27:01 by mrojouan          #+#    #+#             */
/*   Updated: 2025/10/17 15:43:19 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(long nbr)
{
	int	nbr_count;

	nbr_count = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
		nbr = -nbr;
	while (nbr > 0)
	{
		nbr = nbr / 10;
		nbr_count++;
	}
	return (nbr_count);
}

char	*ft_itoa(int nbr)
{
	char	*str_nbr;
	int		len;
	long	lnbr;
	int		is_neg;

	lnbr = nbr;
	is_neg = (lnbr < 0);
	if (lnbr < 0)
		lnbr = -lnbr;
	len = ft_nbrlen(lnbr) + is_neg;
	str_nbr = malloc(sizeof(char) * (len + 1));
	if (!str_nbr)
		return (0);
	str_nbr[len] = '\0';
	while (len > is_neg)
	{
		str_nbr[len - 1] = (lnbr % 10) + '0';
		lnbr = lnbr / 10;
		len--;
	}
	if (is_neg == 1)
		str_nbr[0] = '-';
	return (str_nbr);
}
