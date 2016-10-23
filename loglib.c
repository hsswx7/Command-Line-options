#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include "log.h"

#define BILLION  1000000000L;

typedef struct list_struct {
	data_t item;
	struct list_struct *next;
} log_t;


static log_t *headptr = NULL;
static log_t *tailptr = NULL;

int addmsg(data_t data) 
{
  log_t *newnode;
  int nodesize;
  
  nodesize = sizeof(log_t) + strlen(data.string) +1;  // making the size of the node my taking the size of log_t and the size of data +1 for \0
  if ((newnode = (log_t *)(malloc(nodesize))) == NULL) // if newnode failed to be allocated in memory 
  {
    perror ("Failed to make newnode");
    return -1;
  }
  
  newnode -> item.time = data.time; // getting the current time of the statement
  newnode -> item.string = (char *)newnode + sizeof(log_t);  
  strcpy(newnode -> item.string, data.string); // copying  
  newnode -> next = NULL; // setting the next to be null so when new data needs to be aded to the list 
  if(headptr == NULL)
  {
    headptr = newnode;
  }
  else tailptr->next = newnode; // moving to the tailptr to add more data 
  tailptr = newnode; 
  return 0;
}

void clearlog(void) 
{
  log_t *next = headptr; // starting at the dead 
  while(next != NULL) // clearing up the memory untill tail hits NULL
  {
    next = headptr->next; // setting up next when the head is cleared 
    free(headptr);
    headptr = next; //moving to the next 
  }
}

char *getlog(void) 
{
  size_t length = 0;  
  size_t msglength = 0;
  size_t offset = 0;
  log_t *head = headptr;
  
  while (head != NULL) //going to the end of the list struct 
  {
    length += strlen(head -> item.string)+1; // adding up the size of the entire list
    head = head -> next; //moving to the next part of list 
  }
  char *log = (char *) malloc(length); //allocating that size
  if (log == NULL) // if I fail to allocate memory
  {
    perror ("Cannot allocate memeory for the log");
    return NULL;
  }
  head = headptr; // getting head 
  offset = 0;
  
  while (head) //while I have log to print 
  {
    msglength = strlen(head -> item.string) ;
    memcpy(log + offset, "\n", 1); // copying everything to log that we created;
    offset++;  //I think this is for \0  
    head = head -> next; //moving on
  }
  memcpy(log + offset - 1, "\0", 1);  //adding end
  return log; //returning log to be printed or stored 
}

void input_msg(char *msg)
{
  data_t data; // making data

  clock_gettime(CLOCK_REALTIME,&data.time);
  //long long unsigned int calc = 0;
  // calc = data.time.tv_sec;
  // calc*=BILLION;
  // calc += data.time.tv_nsec;
  //printf ("calc add: %llu\n", calc);
  //data.totaltime = calc;
  //printf ("toatltime: %llu\n", data.totaltime);

 
  size_t msglen = strlen(msg); // getting size of the messge`
  data.string = malloc(msglen + 1); //allocating the for the size 
  memcpy(data.string, msg, msglen + 1); 
  addmsg(data); // calling addmsg to add msg to the log
  free(data.string); // freeing the memeory I allocated in malloc
}
 
int savelog(char *filename, char *exeName) 
{
  FILE  *pFile;
  log_t *node;  //making for head  
  
  pFile = fopen(filename, "a"); // opening file to write
  if (pFile == NULL)
  {
    perror ("File did not open: ");
    return -1;
  }
  
  node = headptr; // starting at head 
  while(node)
  {
    //time_t seconds;
    //seconds = (node -> item.time); // getting the time stored in seconds 
    //char *time = ctime(&node -> item.time); //getting time
    //time[strlen(time) - 1] = 0;
    //printf("tv_sec %llu\n" , node->item.time.tv_sec);
    //printf("tv_nsec %llu\n", node->item.time.tv_nsec);
    long long unsigned int calc =0;
    calc = node->item.time.tv_sec * BILLION;
    calc += node->item.time.tv_nsec;
    fprintf(pFile, "%s: %llu:  %s %s\n",exeName, calc, " Error: ", node->item.string);
    node = node -> next;
  }
  if(fclose(pFile)) //closing file
  {
    perror("Failed to close file");
    return -1; 
  }
  return 0;
}
