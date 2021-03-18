/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 09:18:21 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/18 11:22:04 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_UTILS_H
# define MINI_RT_UTILS_H

# include <stdio.h>
# include <stdlib.h>

typedef struct		s_next
{
	struct s_next	*next;
}					t_next;

double	ft_atof(const char *str);
int		ft_atoi(const char *str);
char	*ft_itoa(int nbr);
void	*ft_lstadd_front(void **lst, void* const new);
void	ft_lstfree(void *lst);
int		ft_lstsize(void* const lst);
void	*ft_memcpy(void *dest, const void *src, size_t len);
void	*ft_memset(void *dest, int chr, size_t len);
int		ft_nbrlen(int nbr);
char	**ft_split(const char *str, const char *sep);
int		ft_strarrlen(char* const *arr);
char	*ft_strchr(const char *str, int chr);
int		ft_strcmp(const char *str1, const char *str2);
char	*ft_strcrdup(const char *str, int chr);
char	*ft_strjoin(const char *str1, const char *str2);
int		ft_strlen(const char *str);
char	*ft_strrchr(const char *str, int chr);
char	*ft_strsepdup(const char *str, const char *sep);
int		ft_wordcount(const char *str, const char *sep);

#endif
