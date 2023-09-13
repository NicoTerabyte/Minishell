/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wildcard_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:23:26 by abuonomo          #+#    #+#             */
/*   Updated: 2023/09/13 17:58:21 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	mcharnum(char** matrice)
{
	int lenght = 0;
	int num_s = 0;
	int i = 0;

	while (matrice[i] != NULL) {
		lenght += strlen(matrice[i]);
		num_s++;
		i++;
	}
	lenght += 2 * (num_s - 1);
	return lenght;
}
