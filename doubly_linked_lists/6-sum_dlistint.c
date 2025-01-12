#include "lists.h"
/**
* sum_dlistint - function
* @head: pointer to first node in double linked list
*
* Description: function to return sum of all dat (n) in double list
* Return: sum of data or 0
*/
int sum_dlistint(dlistint_t *head)
{
	dlistint_t *temph;
	int sum = 0;

	if (head == NULL)
		return (0);

	temph = head;
	while (temph != NULL)
	{
		sum += temph->n;
		temph = temph->next;
	}
	return (sum);
}
