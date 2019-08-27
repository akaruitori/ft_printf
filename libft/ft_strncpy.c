/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 19:37:18 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/21 20:51:22 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (n > i)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

/*
** SYNOPSIS
**        #include <string.h>
**        char *strcpy(char *dest, const char *src);
**
**        char *strncpy(char *dest, const char *src, size_t n);
**
** DESCRIPTION
**        The  strcpy() function copies the string pointed to by src,
**        including the terminating null byte ('\0'), to  the  buffer
**        pointed  to  by dest.  The strings may not overlap, and the
**        destination string dest must be large enough to receive the
**        copy.  Beware of buffer overruns!  (See BUGS.)
**
**        The  strncpy()  function  is similar, except that at most n
**        bytes of src are copied.  Warning: If there is no null byte
**        among  the  first n bytes of src, the string placed in dest
**        will not be null-terminated.
**
**        If the length of src is less than n, strncpy() writes addi‐
**        tional null bytes to dest to ensure that a total of n bytes
**        are written.
**
**        A simple implementation of strncpy() might be:
**
**            char *
**            strncpy(char *dest, const char *src, size_t n)
**            {
**                size_t i;
**
**                for (i = 0; i < n && src[i] != '\0'; i++)
**                    dest[i] = src[i];
**                for ( ; i < n; i++)
**                    dest[i] = '\0';
**
**                return dest;
**            }
**
** RETURN VALUE
**        The strcpy() and strncpy() functions return  a  pointer  to
**        the destination string dest.
*/
