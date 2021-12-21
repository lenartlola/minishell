#include "../incs/minishell.h"

t_list	*enviroinit(char **ev)
{
	int	i;
	t_list *lst;
	t_list *tmp;

	i = 0;
	lst = ft_lstnew(ev[i]);
	while(ev[i])
	{
		tmp = ft_lstnew(ev[i]);
		ft_lstadd_back(&lst,tmp);
		i++;
	}
	tmp = ft_lstnew("OLDPWD");
	ft_lstadd_back(&lst,tmp);
	return (lst);
}
		
