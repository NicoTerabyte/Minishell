/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_env_add.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 23:38:43 by lnicoter          #+#    #+#             */
/*   Updated: 2023/10/01 17:52:45 by lnicoter         ###   ########.fr       */
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

void	env_adding(char *final_string, t_data *shell_data)
{
	size_t	new_size;
	size_t	i;

	new_size = env_rows(shell_data) + 1;
	shell_data->export_env = realloc(shell_data->export_env, (new_size + 1) * sizeof(char *));
	shell_data->export_env[new_size - 1] = ft_strdup(final_string);  // Assicurati che final_string sia allocato
	shell_data->export_env[new_size] = 0;
}

char *super_strjoin(t_data *shell_data)
{
	char	*final_string;

	final_string = ft_strdup(shell_data->identity->name);

	if (shell_data->identity->value)
	{
		if (shell_data->identity->concatenation != 0)
			final_string = ft_strjoin_damn_you_leaks(final_string, "=");
		if (!ft_strchr(shell_data->identity->value, '\"') && !ft_strchr(shell_data->identity->value, '\''))
		{
			final_string = ft_strjoin_damn_you_leaks(final_string, "\""); //fare funzione per liberare e rifare
			final_string = ft_strjoin_damn_you_leaks(final_string, shell_data->identity->value); //non liberi la stringa precedente
			final_string = ft_strjoin_damn_you_leaks(final_string, "\"");
		}
		else if (ft_strchr(shell_data->identity->value, '\''))
		{
			char *support_str = i_hate_this_strcpy_for_apix(NULL, shell_data->identity->value);
			final_string = ft_strjoin_damn_you_leaks(final_string, support_str);
			free(support_str);
		}
		else
			final_string = ft_strjoin_damn_you_leaks(final_string, shell_data->identity->value);
	}
	else if (shell_data->identity->concatenation)
	{
		final_string = ft_strjoin_damn_you_leaks(final_string, "=");
		final_string = ft_strjoin_damn_you_leaks(final_string, "\"");
		final_string = ft_strjoin_damn_you_leaks(final_string, "\"");
	}

	return final_string;
}

void	add_export_env(t_data *shell_data)
{
	char			*final_string;

	final_string = super_strjoin(shell_data);
	env_adding(final_string, shell_data);
	free(final_string);
	// *shell_data->identity = (*shell_data->identity)->next;
	// *shell_data->identity = head;
}
