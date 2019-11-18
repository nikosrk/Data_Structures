#include <stdio.h>
#include <stdlib.h>

//creating a struct 
typedef struct Node {

  int data;
  struct Node *next;

} node;

typedef struct D_Node {
  
  int data;
  struct D_Node *next;
  struct D_Node *prev;
  
} d_node;

typedef d_node *d_node_ptr;

//new name for node pointer (List_Ptr)
typedef node *node_ptr;

int delete_after (node_ptr prev) {

  node_ptr current;
  
  current = prev -> next;
  prev -> next = current -> next;

  free(current);
  
  return 0;

}

//initialize the list
void List_Init (node_ptr *head) {
  *head = NULL;
}

void D_List_Init (d_node_ptr *head) {
  *head = NULL;
}

//Insert the element x in list
int addNodeSingle (node_ptr *head, int x, int pos) {
  //add element x at the top of the list
  if (pos == 0) {
    //create the new node
    node_ptr newnode;
  
    //allocate memory for new node
    newnode = (node *)malloc(sizeof(node));
    //Print message for memory allocation
    if (!newnode) {
      printf("Memory not allocated!");
      return 1;
    }
    //put the argument(x) from function equal with 
    //data of the newnode
    newnode -> data  = x;
    newnode -> next = *head;
    *head = newnode;
  
    return 0;
  
  }
  else if (pos == 1) {
    
    node_ptr current;
    current = *head;
    node_ptr newnode;
    
    newnode = (node *)malloc(sizeof(node));
    
    if (!newnode) {
      printf("Memory not allocated!");
      return 1;
    }
    
    while (current -> next != NULL) {
      current = current -> next;
    }
    newnode -> data = x;
    current -> next = newnode;
    newnode-> next = NULL;
    
    return 0;
  }
  else {
    printf("Wrong argument!");
    return 1;
  }
  
}

void addDescending (node_ptr *head, int x) {
  
  node_ptr newnode;
  //check if list is empty
  if (*head == NULL) {
    printf("List is empty!");
    return;
  }
  
  newnode = (node *)malloc(sizeof(node));

  if (!newnode) {
    printf("Memory not allocated!");
    return;
  }
  
  newnode -> data = x;
  //check if the first node's data is smaller than x
  //if true then put the newnode first  
  if ((*head) -> data < x) {
    newnode -> next = *head;
    *head = newnode; 
    return; 
  } 
 
  node_ptr current = *head;
  //All other cases
  while (current -> next != NULL) {
  
    if (current -> data > x && current -> next -> data < x) {
      newnode -> next = current -> next;
      current -> next = newnode;
      return;
    }
    
    if (current -> next -> next == NULL && current -> next -> data > x) {
      newnode -> next = NULL;
      current -> next -> next = newnode;
      return; 
    }

    current = current -> next;

  } 
   
}

int countList (node_ptr head) {
  
  node_ptr current = head;
  int count = 0;
  
  while (current != NULL) {
    count = count + 1;
    current = current -> next;
  }
  
  return count;

}

void displayList (node_ptr head) {
  
  node_ptr current = head;
    
  while (current != NULL) {
    printf("%d\t", current -> data);
    current = current -> next;
  }
  printf("\n");

}

void deleteLast (node_ptr head) {
  
  int number = 0;
   
  if (head -> next == NULL) {
    free(head);
  }

  node_ptr current = head;
  
  while (current -> next -> next != NULL) {
    current = current -> next;
  }
  
  free(current -> next);
  
  current -> next = NULL;

}

void deleteNode (node_ptr *head, int x) {

  node_ptr current = *head, *prev;

  if (current == NULL) {
    printf("List is empty!");
    return;
  }
  
  
  if (current -> data == x) {

    *head = current -> next;
    free(current);
    return;

  } 
  
  while (current != NULL && current -> data != x) {
    prev = current;
    current = current -> next;
  }
  
  delete_after(prev);
  
  
}

int addNodeDouble (d_node_ptr *head, d_node_ptr *tail, int x, int pos) {
  
  if (pos == 0) {
   
    d_node_ptr newnode;
  
    newnode = (d_node *)malloc(sizeof(d_node));
  
    if (!newnode) {
      printf("Memory not allocated!");
      return 1;
    }

    newnode -> data = x;
    
    newnode -> next = *head;
    newnode -> prev = NULL;
    *head = newnode;
    if (newnode -> next != NULL) {
      newnode -> next -> prev = newnode;
    }
    
    if ((*head) -> next == NULL && (*head) -> prev == NULL) {
      *tail = newnode;
    }
    else {
      d_node_ptr current = *head;
      while (current -> next != NULL) {
        current = current -> next;
      }
      *tail = current;
    }  

    return 0;

  }
  else if (pos == 1) {  
    
    d_node_ptr newnode, current;
  
    newnode = (d_node *)malloc(sizeof(d_node));
  
    if (!newnode) {
      printf("Memory not allocated!");
      return 1;
    }
  
    current = *tail;
    
    newnode -> data = x;
    newnode -> next = current -> next;
    current -> next = newnode;
    newnode -> prev = current;
    
    *tail = newnode;

    return 0;

  } 
  else {
    printf("Wrong argument!");
  }
  
}

void ReversedisplayList (d_node_ptr head, d_node_ptr tail) {

  d_node_ptr current = tail;
  
  while (current != NULL) {
    printf("%d\t", current -> data);
    current = current -> prev;
  }
  
  printf("\n");

}
 
int main () {
  
  int users_input;
  //declaration of list 
  node_ptr head;
  //initialize list
  List_Init(&head);  

  addNodeSingle(&head, 8, 0);
  addNodeSingle(&head, 10, 0);
  addNodeSingle(&head, 6, 1);
  addNodeSingle(&head, 3, 1);
  printf("The created list is: \n");
  displayList(head);
  printf("Add the numbers 2 and 9 in descending order: \n");
  addDescending(&head, 9);
  addDescending(&head, 2);
  displayList(head);
  printf("Delete the last element of the list: \n");
  deleteLast(head);
  displayList(head);
  printf("Delete 6 from the list: \n");
  deleteNode(&head, 6);
  displayList(head);
  int x = countList(head);
  printf("Finally the number of elements in list are: %d\n", x);
  
  //declaration head1, tail
  d_node_ptr head1;
  d_node_ptr tail;
  //initialize head1, tail
  D_List_Init(&head1);
  D_List_Init(&tail);
  //add node in DLL
  addNodeDouble(&head1, &tail, 2, 0);
  addNodeDouble(&head1, &tail, 1, 0);
  addNodeDouble(&head1, &tail, 3, 1);
  printf("The created list is: \n");
  ReversedisplayList(head, tail);
   
  return 0;

}
