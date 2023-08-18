/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_env_add.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 23:38:43 by lnicoter          #+#    #+#             */
/*   Updated: 2023/08/18 15:47:14 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*cosa fare
1. io voglio ottenere una stringa nuova inserita ll'interno del mio env
vorrei manipolare le stringhe in modo tale che io possa unirle tutte insieme
in unica stringa
2. allora come posso unire più stringhe insieme?
la mia idea base era di usare strjoin però aveva causato una sorta di malloc error
l'altra volta quindi di mio non saprei bene come fare
3. un'idea molto basica che mi è passata per la testa giusto ora è di sviluppare una
funzione che prende struct declaration e in parole povere unisce i tre valori nel caso ci fossero tutti
ovviamente nel peggiore dei casi all'interno dell'export si mette solo il nome della stringa
però in questa funzione bisogna anche tenere conto delle "" attorno al value della nostra variabile
export
4. non ha senso
5. bisognerebbe fare nel caso l'elemento value all'interno di t_declaration ci fosse, una funzione che lo modifichi
e che gli aggiunga le "" all'inizio e alla fine
6. la super_strjoin potrebbe prendere la lista e scorrerla pian piano unendo ogni parte in una stringa
7. testing delle funzioni
8. il codice come sempre dev'essere semplice ed efficace piuttosto lo suddivido in più funzioni
9. stiamo molto attenti con la malloc
10. commmentare se necessario
*/

// void	insert_in_env(t_data *shell_data, char *final_string, t_declaration *values)
// {
// 	//ft_strjoin
// }

void	super_strjoin(t_data *shell_data, t_declaration *values)
{
	char			*final_string;
	int				i;
	t_declaration	*current;

	final_string = malloc(ft_strlen(values->name) * sizeof(char));
	ft_strlcpy(final_string, values->name, ft_strlen(values->name) + 1);
	current = values;
	i = 0;
	if (values->value)
	{
		if (values->concatenation == 1)
			final_string = ft_strjoin(final_string, "+=");
		else
			final_string = ft_strjoin(final_string, "=");
		final_string = ft_strjoin(final_string, "\"");
		final_string = ft_strjoin(final_string, values->value);
		final_string = ft_strjoin(final_string, "\"");
	}
	current = values;
	printf("test %s\n", final_string);
}

void	add_env(t_data *shell_data, t_declaration **values)
{
	super_strjoin(shell_data, *values);
	printf("test %s\n", final_string);
}
