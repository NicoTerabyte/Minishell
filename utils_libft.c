#include "minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_islower(int c)
{
	return (c >= 'a' && c <= 'z');
}

int	ft_isupper(int c)
{
	return (c >= 'A' && c <= 'Z');
}

int	ft_isalpha(int c)
{
	if (ft_isupper(c) || ft_islower(c))
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	s;
	int	res;

	i = 0;
	s = 1;
	res = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res * s);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (s1[i] == '\0' && s2[i] == '\0')
		return (0);
	else if (s1[i] == '\0')
		return (-1);
	else if (s2[i] == '\0')
		return (1);
	else
		return (s1[i] - s2[i]);
}

char	*ft_strchr(const char *s, int c)
{
	char	*r;
	char	x;

	x = (char) c;
	r = (char *) s;
	while (*r && *r != x)
		r++;
	if (*r == x)
		return (r);
	return (0);
}

int	free_matrix(char **s)
{
	int i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
	return (0);
}

static size_t	get_word(const char *s, char c)
{
	size_t	words;

	words = 0;
	while (*s)
	{
		if (*s != c)
		{
			++words;
			while (*s && *s != c)
				++s;
		}
		else
			++s;
	}
	return (words);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	//con questo separiamo i pezzi della split
	//CON QUESTO occhio
	char	*str;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	str = (char *)malloc(sizeof(*s) * (len + 1));
	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (s[i])
	{
		if (i >= start && j < len)
			str[j++] = s[i];
		i++;
	}
	str[j] = '\0';
	return (str);
}

//funzione d'appoggio con la quale controllo le quotes per ft_split
static char	*quotes(char *quoted)
{
	//il problema si presenta qua
	int	i;

	i = 1;
	printf("test del valore %s\n", quoted);
	while (quoted[i] == '"' && quoted[i] != '\0')
		i++;
	return (quoted);
}
//la split va fixata in modo tale che riesca a riconoscere le virgolette e
//che non le splitti finchè non ne trovi altre le quali completeranno la stringa
//cosicché nel fix_syntax le quotes che hanno gli spazi non vengano eliminate
//dando sostituendo lo spazio con il \0
//quindi adesso c'è il bisogno di fare un controllo nella split, dove appena incontra
//" o ' continua ad andare avanti finché non trova la coppia diciamo così non separa nulla
//modificare la funzione per dividere le parole da dentro
//la funzione split
char	**ft_split(char *s, char c)
{
	printf("SPLIT FUNCTION\n\n\n");
	char	**str;
	size_t	i;
	size_t	len;

	if (!s)
		return (0);
	i = 0;
	str = malloc(sizeof(char *) * (get_word(s, c) + 1));
	if (!str)
		return (0);
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (*s && *s != c && ++len)
				++s;
			str[i++] = ft_substr(s - len, 0, len);
		}
		else
			++s;
	}
	str[i] = 0;
	int	printer;
	printer = 0;
	while (str[printer])
	{
		printf("String value: %s\n",str[printer]);
		printer++;
	}
	return (str);
}

// static int	line_len(char *s)
// {
// 	int	i;

// 	i = 0;
// 	if (!s)
// 		return (0);
// 	while (s[i] && s[i] != '\n')
// 		i++;
// 	if (s[i] == '\n')
// 		i++;
// 	return (i);
// }

static int	ft_cleanbuff(char *buff)
{
	int	i;
	int	j;
	int	newline;

	i = 0;
	j = 0;
	newline = 0;
	while (buff[i])
	{
		if (newline)
			buff[j++] = buff[i];
		if (buff[i] == '\n')
			newline = 1;
		buff[i++] = '\0';
	}
	return (newline);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	res = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (res == NULL)
		return (NULL);
	i = 0;
	res[ft_strlen(s1) + ft_strlen(s2)] = 0;
	while (i < ft_strlen(s1))
	{
		res[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < ft_strlen(s2))
	{
		res[ft_strlen(s1) + i] = s2[i];
		i++;
	}
	return (res);
// 	int		i;
// 	char	*s3;

// 	i = 0;
// 	s3 = malloc(line_len(s1) + line_len(s2) + 1);
// 	if (!s3)
// 		return (NULL);
// 	while (s1 && s1[i])
// 	{
// 		s3[i] = s1[i];
// 		i++;
// 	}
// 	free(s1);
// 	while (*s2)
// 	{
// 		s3[i++] = *s2;
// 		if (*s2++ == '\n')
// 			break ;
// 	}
// 	s3[i] = '\0';
// 	return (s3);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	char		*readline;
	int			i;

	i = 0;
	if (BUFFER_SIZE < 1 || read(fd, buff, 0) < 0)
	{
		while (buff[i])
			buff[i++] = 0;
		return (NULL);
	}
	readline = NULL;
	while (*buff || read(fd, buff, BUFFER_SIZE) > 0)
	{
		readline = ft_strjoin(readline, buff);
		if (ft_cleanbuff(buff))
			break ;
	}
	return (readline);
}





