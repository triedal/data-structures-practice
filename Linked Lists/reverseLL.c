/*
 *	Write code to reverse the nodes of a nexted list 
 *  by manipulating pointer fields only. No new nodes must be 
 *  created.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node
{
	int value;
	struct node *next;
} Node;

void printList(Node* head)
{
	while (head != NULL)
  {
		printf("%d ", head->value);
		head = head->next;
	}
	printf("\n");
}

void freeList(Node *head)
{
  while (head != NULL)
  {
    Node *victim = head;
    head = head->next;
    free(victim);
  }
}

Node* reverseList(Node *head)
{
  if(head == NULL) return NULL;
  if(head->next == NULL) return head;
  Node* rest = reverseList(head->next);
  head->next->next = head;
  head->next = NULL;
  return rest;
}

int main()
{
  Node *head = NULL, *tmp;
    
  srand((unsigned)time(NULL));
    
  for (int i=1; i<11; ++i)
  {
    tmp = malloc(sizeof(Node));
    tmp->value = i;
    tmp->next = head;
    head = tmp;
  }
    
  printList(head);
  head = reverseList(head);
  printList(head);
  freeList(head);
}