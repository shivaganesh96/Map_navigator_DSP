#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<math.h>
//////////////////////////////////////////////////////
typedef struct  link //FOR adj list
{
  int val;
  struct link * next;
}list;

typedef struct  link2 // For PQ
{
  int val;
  int dist;
  struct link2 * next;
}lnode;

typedef struct ad //Keeping track of coordinates
{
  int vertice;
  int x;
  int y;
  // heap_struct * node;
}vertice;
///////////////////////////////////////POP FUNCTION///////////////
lnode * pop(lnode ** head)
{
  lnode * p;
  p = *head;
  *head = (*head)->next;
  return p;
}
////////////////////////////COMPARISION FUNCTION////////////////////////////
int compare(int a,int b)
{
  if(a>b)
    return 1;
  else
    return -1;
}
///////////////////////////INSERTION INTO PRIORITY QUEUE/////////////////////////////////
lnode *PQ_enqueue(lnode **pq, const int vertice,int hash[])
{
  lnode *node = (lnode *)malloc(sizeof(lnode));
  if(node == NULL)
    {
      return NULL;
    }
  node->val = vertice;
  node->dist = hash[vertice];
  node->next = NULL;

  lnode wall;
  wall.next = *pq;
  lnode * cur = *pq;
  lnode * prev = &wall;
  while(cur!=NULL)
    {
      if((compare(cur->dist,hash[vertice])>0))
	break;
      else
	{
	  prev = cur;
	  cur = cur->next;
	}
    }
  prev->next=node;
  node->next = cur;
  *pq = wall.next;
  return node;
}
/////////////////////STORING PATH/////////////////////////////
lnode * store_path(lnode * front ,lnode * rear, lnode * node)
{ 
if(front == NULL && rear == NULL)
{
front = node;
rear = node;
}
else
{
rear->next = node;
rear = node;
}
return rear;
}
///////////////////TO PRINT PATH///////////////////////////////
void print_path(int prev[],int destination,int source)
{

 
  int temp = destination;
list * head = NULL;
while(temp != source)
{
list * p = (list *)malloc(sizeof(list));
p->val = temp;
p->next = head;
head = p;
temp = prev[temp];
}
printf("%d ",source);
while(head!=NULL)
{
list * k = head;
head = head->next;
printf("%d ",k->val);
free(k);
}
printf("\n");
}
/////////////////////////CALCULATING THE DISTANCE///////////////////////////////////////
int calculate_dist(int current,vertice * start,vertice * end)
{
  int result = current + sqrt(pow(end->x - start->x,2) + pow (end->y - start->y,2));
  return result;
}
///////////////////////////INSERTING INTO ADJACENCY LIST///////////////////////////////////
void insert_adjacent(int tempa,int tempb,list * adlist[])
{
  list * p;
  if(adlist[tempa]!=NULL)
    {p = adlist[tempa];
      while(p->next!=NULL)
	{
	  p = p->next;
	}
      p->next = (list *)malloc(sizeof(list));
      p->next->val = tempb;
      p->next->next = NULL;
    }
  else
    {
      adlist[tempa] = (list *)malloc(sizeof(list));
      adlist[tempa]->next = NULL;
      adlist[tempa]->val = tempb;
    }

}
//////////////////////////MAIN//////////////////////////////
int main(int argc, char ** argv)
{
  FILE * fptr = fopen(argv[1],"r");
  FILE * query = fopen(argv[2],"r");

  int num_vertice,num_edge,queries,source,destination;
  int j;

  fscanf(fptr,"%d",&num_vertice);
  fscanf(fptr,"%d",&num_edge);
  fscanf(query,"%d",&queries);
  int i;
  vertice * vertlist[num_vertice]; //maintaining Coordinates
  list * adlist[num_vertice];// For adjacency list
    for(i=0;i<num_vertice;i++)
    {
      vertlist[i] = (vertice*)malloc(sizeof(vertice));
      fscanf(fptr,"%d",&vertlist[i]->vertice);
      fscanf(fptr,"%d",&vertlist[i]->x);
      fscanf(fptr,"%d",&vertlist[i]->y);
      adlist[i] = NULL;
    }
  int tempa,tempb;
  for(i=0;i<num_edge;i++)
    {
      fscanf(fptr,"%d",&tempa);
      fscanf(fptr,"%d",&tempb);
      insert_adjacent(tempa,tempb,adlist);
      insert_adjacent(tempb,tempa,adlist);

    }
//Dijkstras algorithm
for(i = 0;i<queries;i++)
    {
      int back = 0;
      lnode * head = NULL; //head of priority queue
      int * hash = (int *)malloc(sizeof(int)*num_vertice);
      int * prev = (int *)malloc(sizeof(int)*num_vertice);

      for(j=0;j<num_vertice;j++)
	{
	  hash[j]=INT_MAX;
          prev[j] = INT_MAX;
	} // hashmap to maintain distances of all vertice and setting all val to infinity
      fscanf(query,"%d",&source); //obtaining source and destination
      fscanf(query,"%d",&destination);
      hash[source] = 0; //setting source distance to 0;
      PQ_enqueue(&head,source,hash); //pushing source into queue
    
      lnode * hold =NULL;
      
      int check = 1;
       /////////////////////////////////LOOP/////////////////////////////////////////////
      while((check==1 || hold->val != destination) && (check==1||head!=NULL))
	{ 
	  hold = pop(&head);

	  check = 0;

          list * p = adlist[hold->val];
	
	  while(p!=NULL) // updating PQ
	    {
	      int result = calculate_dist(hash[hold->val],vertlist[hold->val],vertlist[p->val]); // calculating distance
	      if(hash[p->val]>result)
		{
		  hash[p->val] = result;
                  prev[p->val] = hold->val;
		  PQ_enqueue(&head,p->val,hash);
		
                  
		}
	  
	      p = p->next;
          
	    }

if(hold->val == destination)
{
back = 1;
}

	}
        //////////////////////END OF LOOP///////////////////////////////////////////
     if(head == NULL && back == 0) //incase destination is inreachable the Priority queue is empty
	{
	   printf("INF\n");
	    printf("%d %d\n",source,destination);
	}
       else
	{
	    printf("%d\n",hash[destination]);
	  print_path(prev,destination,source); //printing path from stored queue
	}


    }
  fclose(fptr);
  fclose(query);
  return 0;
}
////////////////END OF MAIN////////////////
  
