/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_order.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:34:58 by abuonomo          #+#    #+#             */
/*   Updated: 2023/09/21 15:36:00 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void swap_strings(char **a, char **b)
{
	char *temp = *a;
	*a = *b;
	*b = temp;
}

void recursive_sort(char **matrix, int rows, int i, int j)
{
	if (i == rows - 1)
		return;
	if (j < rows - 1 - i)
	{
		if (strcmp(matrix[j], matrix[j + 1]) > 0)
			swap_strings(&matrix[j], &matrix[j + 1]);
		recursive_sort(matrix, rows, i, j + 1);
	}
	else
		recursive_sort(matrix, rows, i + 1, 0);
}

void sort_string_matrix(char **matrix, int rows)
{
	recursive_sort(matrix, rows, 0, 0);
}
