#include <stdio.h>
#include "../incs/minishell.h"

t_list  *ft_sort(t_list *ev, int n_array);
void    print(void *ptr);
int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

t_list	*sort(t_list *ev,int n_array)
{
	int i;
	int j;
	char *temp;
	void (*test)(void *);
	
	test = &print;
	i = 0;
	while (i < n_array)
	{
		j = 0;
		ft_sort(ev, n_array-1-i);
		i++;
	}
	ft_lstiter(ev, test);
	return (ev);
}

t_list	*ft_sort(t_list *ev, int n_array)
{
	int	j;
	char *temp;
	void (*test)(void *);

	test = &print;
	j = 0;
    	while(j < n_array)
	{
      		if(ft_strcmp(ev->content, ev->next->content) > 0)
		{
			temp = ft_strdup(ev->content);
        		ev->content = ft_strdup(ev->next->content);
        		ev->next->content = ft_strdup(temp);
		}
		ev = ev->next;
		j++;
	}
	return (ev);
}

void    print(void *ptr)
{
	char *str = ptr;

	printf("declare -x %s\n",ptr);
}
int	ft_export(char **cmd, t_shell *shell)
{
	unsigned int i;
	t_list *nenv;
	void (*test)(void *) = &print;

	i = ft_lstsize(shell->ev);
	if (cmd[1] == NULL)
		shell->ev = sort(shell->ev,i);
	else
	{
		nenv = ft_lstnew(cmd[1]);
		ft_lstadd_back(&shell->ev,nenv);
	}
	return (1);
}
