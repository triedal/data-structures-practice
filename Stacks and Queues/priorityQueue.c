/*  
 *  Write declarations and functiosn to implement
 *  a priority queue. Each item in the queue has a job
 *  number (integer) and a priority number. Implement
 *  the following functions:
 *
 *    a) initialize an empty queue
 *    b) add a job in its appropri.ate place in the queue
 *    c) delete and dispose of the job at the head of the
 *       queue
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
  int jobNum;
} QueueData;

typedef struct node 
{
  QueueData data;
  int priority;
  struct node *next;
} Node;

typedef struct 
{
  Node *head, *tail;
} Queue;

Queue* initQueue()
{
  Queue *qp = (Queue *) malloc(sizeof(Queue));
  qp->head = qp->tail = NULL;
  return qp;
}

int empty(Queue *q)
{
  return (q->head == NULL);
}

void enqueue(Queue *q, QueueData d, int priority)
{
  Node *np = (Node *) malloc(sizeof(Node));
  np->data = d;
  np->priority = priority;
  np->next = NULL;
  if (empty(q))
  {
    q->head = q->tail = np;
  }
  else
  {
    if (np->priority > q->head->priority) // np is higher than all others
    {
      np->next = q->head;
      q->head = np;
    }
    else
    {
      Node *tmp = q->head;
      while (tmp->next != NULL && np->priority <= tmp->next->priority)
      {
        tmp = tmp->next;
      }
      np->next = tmp->next;
      tmp->next = np;
    }
  }
}

QueueData dequeue(Queue *q)
{
  if (empty(q))
  {
    printf("Cannot dequeue. Queue is already empty.\n");
    exit(1);
  }
  QueueData hold = q->head->data;
  Node *tmp = q->head;
  q->head = q->head->next;
  if (q->head == NULL) q->tail = NULL;
  free(tmp);
  return hold;
}

void printQueue(Queue *q)
{
  Node *tmp = q->head;
  while (tmp != NULL)
  {
    printf("Job #: %d (%d)\n", tmp->data.jobNum, tmp->priority);
    tmp = tmp->next;
  }
}

int main()
{
  QueueData tmp;
  Queue *Q = initQueue();

  srand((unsigned)time(NULL));
    
  for (int i=0; i<20; ++i)
  {
    tmp.jobNum = rand() % 10000;
    enqueue(Q, tmp, rand() % 10);
  }

  tmp = dequeue(Q);
  printf("%d\n", tmp.jobNum);

  return 0;
}