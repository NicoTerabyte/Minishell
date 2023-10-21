/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:48:20 by lnicoter          #+#    #+#             */
/*   Updated: 2023/10/21 19:40:04 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int		find_equal(char *env)
{
	int	i;

	i = -1;
	while (env[++i] && env[i] != '=')
		;
	return (i);
}

void	print_export(char **export_matrix)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	while (export_matrix[++i])
	{
		len = find_equal(export_matrix[i]);
		j = -1;
		printf("declare -x ");
		while (++j < len)
			printf("%c", export_matrix[i][j]);
		if (len < ft_strlen(export_matrix[i]));
			printf("=\"%s\"", export_matrix[i] + len + 1);
		printf("\n");
	}

}

char	**setting_the_matrix(char **env)
{
	char	**the_export_copy;
	int		size;
	int		i;

	size = env_rows(env);
	the_export_copy = (char **)malloc((size + 1) * sizeof(char *));
	if (!the_export_copy)
		printf("Errore nell'allocazione della memoria\n");
	i = -1;
	while (++i < size)
		the_export_copy[i] = ft_strdup(env[i]);
	the_export_copy[size] = NULL;  // Terminatore dell'array
	return (the_export_copy);
}

void	sort_and_print_export(char **env)
{
	int		i;
	int		j;
	char	*tmp;
	char	**export_matrix;
	int		size;

	size = env_rows(env);
	export_matrix = setting_the_matrix(env);
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
	free_matrix(export_matrix);
}


/*
	export secono manu:
	allora bisogna cambiare leggermente export
	per inquadrare in maniera corretta come funziona secondo
	la logica di manu in maniera che io possa applicare meglio anche la
	mia ecco cosa bisogna tenere in considerazione:
	1) export lavora con la lista già pronta di conseguenza sai di avere:
		nome, concatenazione valore di conseguenza alcune cose sono semplificate
	2) manu tratta la concatenazione con 0 e 1 che non va bene da un certo punto di vista perché se
		vogliamo differenziare come si deve la concatenazione verificando la casistica del
		c= che diventa c="" dobbiamo
		la domanda è: come gli dico di inserire il valore se non so che concatenazione c'è?
	3) ci saranno meno controlli da fare nel codice di conseguenza conviene riadattare export
		E forse come dice Mlongo va bene nel senso io la cosa dell'= lo usavo per la matrice
		dell'environment di conseguenza se io procedo a stamparla correttamente non penso ci sia
		un problema quindi se lavoro bene nella stampa ci saranno 100% in meno di controlli da fare
*/
void	ft_export(t_declaration *node)
{
	int		conc;
	char	**env;

	env = env_container(7, env);
	conc = 0;
	if (!node)
		sort_and_print_export(env);
	else
	{
		// arguments_separation(shell_data, command_line, conc); //segfault gestire casi con nomevalue = "="
		while (node)
		{
			if (check_doubles(node, env) == 0 && check_arguments_validation(node->name))
			{
				//add_export_env(env);
				// if (node->concatenation != 0)
				add_to_the_real_env(node, env);
			}
			node = node->next;
		}
		// shell_data->identity = shell_data->head;
		// if (node)
		// 	puppamelo(node); //in teoria lo libera Manuele
		printf("daje\n");
	}

}
/*
bug da sistemare
1)l'aggiunta di più elementi comporta
l'inserimento dell'= in maniera automatica (fixato)
2)sembra che non riesca a reggere due test di fila
i test sono: daje=roma pesce=noncane (le due variabili dovrebbero essere sovrascritte) (fixato)
3)se una variabile è dichiarata senza = e poi si fa la concatenazione si rompe un po' (fixato)
4) leaks sembra non ci siano altre pecche
5) //segfault gestire casi con nomevalue = "=" (fixato)
6) Sistemare la split in modo che dopo l'= si fa mantenendo i valori
	è come se dovessi splittare una volta sola.... mantenendo quello che c'è dopo
*/
