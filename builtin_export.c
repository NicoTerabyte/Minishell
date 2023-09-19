/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:48:20 by lnicoter          #+#    #+#             */
/*   Updated: 2023/09/18 12:54:29 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(char **export_matrix)
{
	int	i;

	i = -1;
	while (export_matrix[++i])
		printf("declare -x %s\n", export_matrix[i]);
}

char	**setting_the_matrix(t_data *shell_data)
{
	char	**the_export_copy;
	int		size;
	int		i;

	size = env_rows(shell_data);
	the_export_copy = (char **)malloc((size + 1) * sizeof(char *));
	if (!the_export_copy)
		printf("Errore nell'allocazione della memoria\n");
	i = -1;
	while (++i < size)
		the_export_copy[i] = shell_data->copy_env[i];
	the_export_copy[size] = NULL;  // Terminatore dell'array
	return (the_export_copy);
}

void	sort_and_print_export(t_data *shell_data)
{
	int		i;
	int		j;
	char	*tmp;
	char	**export_matrix;
	int		size;

	size = env_rows(shell_data);
	export_matrix = setting_the_matrix(shell_data);
	i = -1;
	while (++i < size - 1)
	{
		j = -1;
		while (++j < size - i - 1)
		{
			if (ft_strcmp(export_matrix[j], export_matrix[j + 1]) > 0)
			{
				tmp = export_matrix[j];
				export_matrix[j] = export_matrix[j + 1];
				export_matrix[j + 1] = tmp;
			}
		}
	}
	print_export(export_matrix);
	free(export_matrix);  // Ricordati di liberare la memoria allocata
}


//le casistiche di export con argomenti
//+= stampo errore con +=
//lo stesso con =
//nomevar= NULL risultato su env nomevar="" in uqesto caso cambia con il risultato spiegato
//nomevar (senza uguale ne niente) diventa nomevar="" però se esiste già la varia la variabile
//12nomevar= ecc è un errore stampa nomevar errore se hai la concatenazione attiva (+=) stampi
//nomevar+=12 non valida, altrimenti
//esempio: export 1a, 2 value, concatenzazione attiva (+=), = 1a+=2 errore
//altrimenti può uscire 1a errore o 1a=value errore
//se inizia con una lettera e dopo ci sono valori non alfanumerici errore
//ex: a123 va bene a@ non va bene
//devo fare chiarezza e capire come poter definire gli argomenti uno ad uno
void	ft_export(char **command_line, t_data *shell_data, t_declaration **identity)
{
	int		conc;

	conc = 0;
	if (!command_line[1])
		sort_and_print_export(shell_data);
	else
	{
		arguments_separation(command_line, conc, identity);
		//print_list(*identity);
		if (check_doubles(shell_data, *identity) == 0 && check_arguments_validation((*identity)->name))
			add_env(shell_data,identity);
		if (*identity)
			puppamelo(*identity);
		//puppamelo(identity);
	}
}
