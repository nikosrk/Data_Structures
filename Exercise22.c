#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//declaration of struct Foititis
typedef struct Foititis {

  char last_name[30];
  char first_name[20];
  char phone_number[10];
  int reg_year;
  long int am;
  
  struct Foititis *next_lastname;
  struct Foititis *next_am;
  struct Foititis *prev_lastname;
  struct Foititis *prev_am;


} foititis;

typedef foititis *foititis_ptr;
 
//Initialize the empty list
void List_Init (foititis_ptr *head) {
 *head = NULL;
}

//Insert student
int insertStudent (foititis_ptr *head1, foititis_ptr *head2, foititis_ptr *tail1, foititis_ptr *tail2) {
  
  int pos1, pos2;
  foititis_ptr newnode;
  
  newnode = (foititis *)malloc(sizeof(foititis));
  
  if (!newnode) {
    printf("Memory not allocated!");
    return;
  }
  
  insertElements(&newnode);  

  if (*head1 == NULL && *head2 == NULL) {
    newnode -> next_lastname = NULL;
    newnode -> next_am = NULL;
    newnode -> prev_lastname = NULL;
    newnode -> prev_am = NULL;
    *head1 = newnode;
    *head2 = newnode;
      
    *tail1 = newnode;
    *tail2 = newnode;
  
  }
  else {
    head1DL(&head1, &newnode, &tail1);
    head2DL(&head2, &newnode, &tail2);
  }
  

    
}

//function that returns the node foititis with initialized attributes
void insertElements(foititis_ptr *newnode) {
  
  char lstnm[30];
  char frstnm[20];
  char phnum[10];
  int regy;
  long int amm;
    
  printf("Insert last name: ");
  scanf("%s", lstnm);
  toUpper(lstnm);
  printf("\nInsert first name: ");
  scanf("%s", frstnm);
  toUpper(frstnm);
  printf("\nInsert phone number: ");
  scanf("%s", phnum);  
  printf("\nInsert registration year: ");
  scanf("%d", &regy);
  printf("\nInsert am: ");
  scanf("%ld", &amm);
  
  strcpy((*newnode) -> last_name, lstnm);
  strcpy((*newnode) -> first_name, frstnm);
  strcpy((*newnode) -> phone_number, phnum);
  (*newnode) -> reg_year = regy;
  (*newnode) -> am = amm;

}

//function that convert lowercase letters to uppercase
void toUpper (char *ch) {
  
  int i = 0;
  char temp;
  
  while (ch[i]) {
    temp = ch[i];
    temp = toupper(temp);
    ch[i] = temp;
    i++;
  }

}

void head1DL (foititis_ptr *head1, foititis_ptr *newnode, foititis_ptr *tail1 ) {
    
  foititis_ptr current = *head1;
    
  if (current -> next_lastname == NULL) {
    if (cmpString(current->last_name, (*newnode)->last_name) < 0) {
      (*newnode) -> next_lastname = NULL;
      (*newnode) -> prev_lastname = current;
      current -> next_lastname = *newnode;
    }
    else if (cmpString(current->last_name, (*newnode)->last_name > 0)) {
      (*newnode) -> next_lastname = *head1;
      (*newnode) -> prev_lastname = NULL;
      (*head1) -> prev_lastname = *newnode;
      *head1 = *newnode;
    }
  }
  
  while (current -> next_lastname != NULL) {

    current = current -> next_lastname;
  }

}

void head2DL (foititis_ptr *head2, foititis_ptr *newnode, foititis_ptr *tail2) {



}
//compare two strings(lastnames)
int cmpString (char *str1, char *str2) {
  return strcmp(str1, str2);
}
//compare to numbers(am)
int cmpAm (long int a, long int b) {
  
  if (a > b) {
    return 0;
  }
  else {
    return 1;
  }
  
}

void displayList (foititis_ptr head, int x) {
  
  foititis_ptr current = head;
    
  while (current != NULL) {
    
    if (x == 1) { 
      printf("%s\t%s\n", current->first_name, current->last_name);
      current = current -> next_lastname;  
    }
    else {
      printf("%s\t%ld\n", current->first_name, current->am);
      current = current -> next_am;
    }

  }

}

void changeTail (foititis_ptr head, foititis_ptr *tail, int x) {
    
  foititis_ptr current = head;
  
  if (x == 1) {
    while (current -> next_lastname != NULL) {
      current = current -> next_lastname;
    }
    *tail = current;
  }
  else if (x == 2) {
    while (current -> next_am != NULL) {
      current = current -> next_am;
    }
    *tail = current;
  }

}


int main () {

  int choice, flag = 0, x = 0;
  foititis_ptr head1, head2, tail1, tail2;
  
  List_Init(&head1);
  List_Init(&head2);
  List_Init(&tail1);
  List_Init(&tail2);
  
  while (flag != 1) {
  
    printf("Press:\n1)Insert Student\n2)Display List\n3)Search Student\n4)Delete Student\n===> ");
    scanf("%d", &choice);
    
    switch (choice) {
      case 1:
        insertStudent(&head1, &head2, &tail1, &tail2);
        break;
      case 2:
        printf("Press:\n1)Search by lastname\n2)Search by AM\n ");
        scanf("%d", &x);
        if (x == 1) {
          displayList(head1, x);
        }
        else if (x == 2) {
          displayList(head2, x);
        }
        break;
      case 3:
        //searchStudent(head);
        break;  
      case 4:
        //deleteStudent(&head);
        break;
      default:
        flag = 1;
        break;
     } 

  }

  return 0; 
 
}
