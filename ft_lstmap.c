/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohanegg <mohanegg@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 00:44:56 by mohanegg          #+#    #+#             */
/*   Updated: 2026/11/03 18:29:45 by mohanegg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *),
			void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	void	*content;

	if (!f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		content = f(lst->content);
		new_node = ft_lstnew(content);
		if (!new_node)
		{
			del(content);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}


#include <stdio.h>
#include <stdlib.h>

void *multiply_two(void *content)
{
    int *new_value;

    new_value = malloc(sizeof(int));
    if (!new_value)
        return (NULL);
    *new_value = (*(int *)content) * 2;
    return (new_value);
}

void del(void *content)
{
    free(content);
}

void print_list(t_list *lst)
{
    while (lst)
    {
        printf("%d -> ", *(int *)lst->content);
        lst = lst->next;
    }
    printf("NULL\n");
}

int main(void)
{
    t_list *lst;
    t_list *mapped;
    int *a;
    int *b;
    int *c;

    lst = NULL;
    a = malloc(sizeof(int));
    b = malloc(sizeof(int));
    c = malloc(sizeof(int));
    if (!a || !b || !c)
        return (1);
    *a = 1;
    *b = 2;
    *c = 3;
    ft_lstadd_back(&lst, ft_lstnew(a));
    ft_lstadd_back(&lst, ft_lstnew(b));
    ft_lstadd_back(&lst, ft_lstnew(c));

    printf("Original list:\n");
    print_list(lst);

    mapped = ft_lstmap(lst, multiply_two, del);

    printf("\nMapped list:\n");
    print_list(mapped);

    printf("\nOriginal list after mapping:\n");
    print_list(lst);

    ft_lstclear(&lst, del);
    ft_lstclear(&mapped, del);
    return (0);
}
