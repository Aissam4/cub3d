/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 10:44:36 by atouhami          #+#    #+#             */
/*   Updated: 2022/03/05 21:47:55 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"


void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*ps;

	ps = (char *)s;
	i = 0;
	while (n)
	{
		ps[i] = 0;
		i++;
		n--;
	}
}

size_t	ft_strlen_2d(char **s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*psrc;
	char	*pdest;

	psrc = (char *)src;
	pdest = (char *)dest;
	if (!dest || !src)
		return (NULL);
	if (dest > src)
		while (n-- > 0)
			pdest[n] = psrc[n];
	else if (dest < src)
	{
		i = 0;
		while (n--)
		{
			pdest[i] = psrc[i];
			i++;
		}
	}
	return (dest);
}


size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*s;
	size_t		s1len;
	size_t		s2len;

	s1len = ft_strlen((char *)s1);
	s2len = ft_strlen((char *)s2);
	s = malloc((s1len + s2len + 1) * sizeof(char));
	if (s == NULL)
		return (printf("Error : Failed allocation\n"), exit(1), NULL);
	ft_memmove(s, s1, s1len);
	ft_memmove(&s[s1len], s2, s2len);
	s[s1len + s2len] = '\0';
	free((void *)s1);
	return (s);
}

int	contains_newline(char const *s1)
{
	int	i;

	i = 0;
	if (!s1)
		return (0);
	while (s1[i])
	{
		if (s1[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}


static char	*first_line(char *str)
{
	int		i;
	char	*line;

	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n' && str)
		i++;
	line = malloc(i + 2);
	if (!line)
		return (printf("Error : Failed allocation\n"), exit(1), NULL);
	ft_memmove(line, str, i + 1);
	line[i + 1] = '\0';
	return (line);
}

static char	*second_part(char *str)
{
	int		i;
	char	*line;

	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (0);
	}
	line = malloc(ft_strlen(&str[i]) + 1);
	if (!line)
		return (printf("Error : Failed allocation\n"), exit(1), NULL);
	ft_memmove(line, &str[i + 1], ft_strlen(&str[i]));
	line[ft_strlen(&str[i])] = '\0';
	free (str);
	if (ft_strlen(line) == 0)
		return (free(line), NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;
	char		buff[BUFFER_SIZE + 1];
	int			readc;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	readc = 1;
	while (readc != 0 && !(contains_newline(str)))
	{
		readc = read(fd, buff, BUFFER_SIZE);
		if (readc == -1)
			return (NULL);
		buff[readc] = '\0';
		if (!readc)
			break ;
		str = ft_strjoin(str, buff);
	}
	line = first_line(str);
	str = second_part(str);
	return (line);
}
