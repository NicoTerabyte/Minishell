/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:21:34 by alessiolong       #+#    #+#             */
/*   Updated: 2023/11/06 18:14:21 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



/*
	prima verifico che ci sia almeno una wildcard
	a se non c'è nessuna wildcard ritorno l'input espanso
	se c'è almeno una wildcard inizia la filterchain
	si inizia andando a cercare la wildcard, se prima c'è scritto qualcosa e non si becca un'altra wildcard
	si espande quel qualcosa e lo si usa come parametro di filtraggio per l'inizio dei nomi dei file o directory tendendo il segno
	per tenere il segno si intende che per esempio per trovare la lettera "d" siamo arrivati alla quarta lettera del file
	successivamente per trovare la stringa successiva si dovrà ripartire dalla quinta lettera
	se non si ha nessun match si ritorna l'input originale espanso
	se si ha almeno un match si va avanti fino alla prossima wildcard e se la si trova prima
	c'è scritto qualcosa e si becca un altra wildcard si espande quel qualcosa e lo si usa come parametro di filtraggio per dove siamo
	arrivati con il segno
	se non si ha nessun match si ritorna l'input originale espanso
	se si ha almeno un match a questo punto si va avanti con il solito discorso fino a che non becchiamo un caso in cui non si trova
	nessuna wildcard avanti e quindi ci troviamo alla fine, a questo punto se si ha qualcosa prima della fine quindi dopo l'ultima
	wildcard si espande quel qualcosa e lo si usa come parametro di filtraggio per la fine dei nomi dei file o directory dove si torna indietro
	a ritroso fino a dove si era arrivati con il segno
	conviene fare questo loop per singoli file e aggiungerli alla stringa finale, se non si ha nessun file alla fine si ritorna la stringa
	originale espansa, facendo così non si ha bisogno di ritornare subito la stringa espansa come scritto sopra se non si ha nessun match
	in quanto questo può verificarsi solo alla fine
*/
// char *ft_wildcard(char *input)

#include "minishell.h"



int	check_wildcard_before(char *input, int i)
{
	while (i != -1)
	{
		if (input[i] == '*')
			return 1;
		i--;
	}
	return 0;
}

int	is_wildcard_present(char *input)
{
	int		i;
	char	quote;

	i = 0;
	while (input[i])
	{
		if (input[i] == '*')
			return 1;
		else if (input[i] == '"' || input[i] == '\'')
		{
			quote = input[i];
			while (input[i] && input[i] != quote)
				i++;
		}
		if (input[i])
			i++;
	}
	return 0;
}

int	move_to_wildcard(char *input)
{
	int		i;
	char	quote;

	i = 0;

	while (input[i])
	{
		if (input[i] == '*')
			return i;
		else if (input[i] == '"' || input[i] == '\'')
		{
			quote = input[i];
			while (input[i] && input[i] != quote)
				i++;
		}
		if (input[i])
			i++;
	}
	return i;
}

char	*expand_strbefore(char *input, int i, t_data *mini)
{
	int		len;
	int		start;
	char	*filter_to_expand;

	len = 0;
	start = i;
	while (start != -1 && input[start] != '*')
	{
		start--;
		len++;
	}
	filter_to_expand = malloc(len + 1);
	filter_to_expand[len] = 0;
	len--;
	start = i;
	while (len != -1 && input[i] != '*')
	{
		filter_to_expand[len] = input[i];
		len--;
		i--;
	}
	return (expander(mini, filter_to_expand));
}

int	word_end_filter(char *filter, char *filename, int *i)
{
	int	filename_index;
	int	filter_index;

	filename_index = ft_strlen(filename) - 1;
	filter_index = ft_strlen(filter) - 1;
	while (filename_index != -1 && filter_index != -1 && filename_index >= *i)
	{
		if (filename[filename_index] != filter[filter_index])
			return 0;
		filename_index--;
		filter_index--;
	}
	if (filename_index >= *i || filename_index == -1 || filter_index == -1)
		return 1;
	else
		return 0;
}

int	word_start_filter(char *filter, char *filename, int *i)
{
	int	filename_index;
	int	filter_index;

	filename_index = 0;
	filter_index = 0;
	while (filename[filename_index] && filter[filter_index])
	{
		if (filename[filename_index] != filter[filter_index])
			return 0;
		filename_index++;
		filter_index++;
	}
	if ((!filename[filename_index] && !filter[filter_index]) || (filename[filename_index] && !filter[filter_index]))
	{
		*i = filename_index;
		return 1;
	}
	else
		return 0;
}

int	word_middle_filter(char *filter, char *filename, int *i)
{
	int	filename_index;
	int	filter_index;

	filename_index = *i;
	filter_index = 0;
	while (filename[filename_index] && filter[filter_index])
	{
		while ((filename[filename_index] && filter[filter_index]) && filename[filename_index] == filter[filter_index])
		{
			filter_index++;
			filename_index++;
		}
		if (!filter[filter_index])
			break ;
		else
			filter_index = 0;
		filename_index++;
	}
	if ((!filename[filename_index] && !filter[filter_index]) || (filename[filename_index] && !filter[filter_index]))
	{
		*i = filename_index;
		return 1;
	}
	else
		return 0;
}

int	filter_word(char *input, char *filename, t_data *mini)
{
	int i;
	int y;
	char *filter;

	i = 0;
	y = -1;
	while (input[i])
	{
		i += move_to_wildcard(&input[i]);
		if (i != 0 && input[i - 1] != '*')
			filter = expand_strbefore(input, i - 1, mini);
		else
		{
			i++;
			continue ;
		}
		if (!input[i])
		{
			if (!word_end_filter(filter, filename, &y))
				return 0;
		}
		else if (i != 0 && !check_wildcard_before(input, i - 1))
		{
			if (!word_start_filter(filter, filename, &y))
				return 0;
		}
		else
		{
			if (!word_middle_filter(filter, filename, &y))
				return 0;
		}
		if (input[i] == '*')
			i++;
	}
	return 1;
}


/*CASI CHE NON FUNGONO
$*
.*
*/
char *ft_wildcard(char *input, t_data *mini)
{
	struct dirent	*entry;
	char			*dirname;
	char			*result;
	DIR				*dir;

	if (!is_wildcard_present(input))
		return (expander(mini, input));

	result = NULL;
	dirname = getcwd(0, 0);
	dir = opendir(dirname);
	entry = readdir(dir);
	//qui fare lo strjoin per ogni filename accettato da filerword
	//chiaramente se a fine ciclo non si ha nessun filenamen strjoinato si ritorna la parola originale espansa
	while ((entry))
	{
		if((input[0] == '.' || entry->d_name[0] != '.') && filter_word(input, entry->d_name, mini))
		{
			result = ft_strjoin(result, entry->d_name);
			result = ft_strjoin(result, " ");
		}
		entry = readdir(dir);
	}
	if (result == NULL)
		return (expander(mini, input));
	else
		return result;
}
