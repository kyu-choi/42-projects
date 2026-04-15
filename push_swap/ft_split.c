/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyu-choi <kyu-choi@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:18:39 by kyu-choi          #+#    #+#             */
/*   Updated: 2025/04/07 20:16:05 by kyu-choi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static	void	free_res(char **res, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(res[i]);
		i++;
	}
	free(res);
}

static	int	puttstr(char **res, char *s, int i, int count)
{
	int	j;

	res[i] = (char *)malloc(sizeof(char) * (count + 1));
	if (!res[i])
	{
		free_res(res, i);
		return (1);
	}
	j = 0;
	while (j < count)
	{
		res[i][j] = s[j];
		j++;
	}
	res[i][j] = '\0';
	return (0);
}

static	void	makearr(char **res, char const *s, char c, int *unbal)
{
	char	*start;
	int		count;
	int		i;

	i = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			start = (char *)s;
			count = 0;
			while ((*s != c) && *s)
			{
				count++;
				s++;
			}
			if (puttstr(res, start, i++, count) == 1)
			{
				*unbal = 1;
				return ;
			}
		}
	}
}

static	int	countnum(char const *s, char c)
{
	int	inchr;
	int	count;

	inchr = 0;
	count = 0;
	while (*s)
	{
		if (*s == c)
			inchr = 0;
		else
		{
			if (inchr == 0)
			{
				inchr = 1;
				count++;
			}
		}
		s++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	int		chrnum;
	int		unbal;
	char	**res;

	if (!s)
		return (NULL);
	chrnum = countnum(s, c);
	res = (char **)malloc(sizeof(char *) * (chrnum + 1));
	if (!res)
		return (NULL);
	unbal = 0;
	makearr(res, s, c, &unbal);
	if (unbal == 1)
		return (NULL);
	res[chrnum] = NULL;
	return (res);
}
/*
int	main(void)
{
	char	*s1 = "restaurant";
	char	s = 'a';
	char	**res;
	int		i;
	
	i = 0;
	res = ft_split(s1,s);
	while (res[i])
	{
		printf("%s\n",res[i]);
		i++;
	}
	return (0);
}*/
