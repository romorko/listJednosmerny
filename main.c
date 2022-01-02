#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node
{
    int hodnota;  //hodnota v uzle
    struct node * next;  //pointer na nasledujuci uzol
};

void printList(struct node* from);
struct node * initList(int ini);
void pushFront(struct node ** pHead, int newData);
void pushBack(struct node** pHead, int newData);
void deleteNodeHodnota(struct node** pHead, int key);
void deleteNodePosition(struct node** pHead, int position);
void pop(struct node ** pHead);
int getCount(struct node* head);
int search(struct node* head, int hladam);
int getNkey(struct node* head, int index);

int main()
{
    struct node * head =NULL;
    pushFront(&head,2);
    pushBack(&head,7);
    pushFront(&head,3);
    pushFront(&head,4);
    pushFront(&head,5);
    pushFront(&head,6);
    pushBack(&head,8);
    pushBack(&head,9);
    printList(head);
    deleteNodePosition(&head,0);
    //pop(&head);
    printList(head);
    deleteNodePosition(&head,0);
    //pop(&head);
    deleteNodeHodnota(&head,3);
    printList(head);
    return 0;
}

void printList(struct node* from)
{
    while (from != NULL)
    {
        printf("%d ", from->hodnota);
        from = from->next;
    }
    printf("\n");
}

void pushFront(struct node ** pHead, int newData)
{
    struct node * newNode = (struct node *)malloc(sizeof(struct node));
    newNode->hodnota=newData;
    newNode->next =*pHead;
    *pHead = newNode;
}

void pushBack(struct node** pHead, int newData)
{
    struct node *last = *pHead; //zazalohujeme si zaciatok listu
    struct node* newNode = (struct node*) malloc(sizeof(struct node));
    newNode->hodnota  = newData;
    newNode->next = NULL; //bude posledny
    if (*pHead == NULL)/*Ak je list prazdny tak bude z neho hlava */
    {
       *pHead = newNode;
       return;
    }
    while (last->next != NULL)//prechadzame az na koniec listu
    {
         last = last->next;
    }

    last->next = newNode;/* posledny bude ukazovat na novy */
}

void insertAfter(struct node* afNode, int newData)
{
    if (afNode == NULL)
    {
        printf("Uzol nemoze byt NULL");
        return;
    }
    struct node* newNode =(struct node*) malloc(sizeof(struct node));
    newNode->hodnota = newData;
    newNode->next = afNode->next;
    afNode->next = newNode;
}

void deleteNodeHodnota(struct node** pHead, int key)
{
    struct node *temp = *pHead; // ulozime si hlavu
    struct node *prev; //na ulozenie predchadzjuceho uzla
    if (temp != NULL && temp->hodnota == key)// ak ma hned hlava hladany kluc
    {
        *pHead = temp->next; // Changed head
        free(temp); // free old head
        return;
    }
    while (temp != NULL)
    {
        if(temp->hodnota == key)
        {
            prev->next = temp->next; //najdeny uzol vyradime
            free(temp); // uvolnime pamat
            break;
        }
        prev = temp;
        temp = temp->next;
    }
    return;
    /*while (temp != NULL && temp->hodnota != key) //hladame uzol ktoreho hodnota je rovna klucu a ukladame si predchadzajuci uzol
    {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) //nenasli sme uzol
        return;

    prev->next = temp->next; //najdeny uzol vyradime
    free(temp); // uvolnime pamat*/
}

void deleteNodePosition(struct node** pHead, int position)
{
    if (*pHead == NULL)// If linked list is empty
    {
        return;
    }
    struct node* temp = *pHead;// Store head node
    if (position == 0) // If head needs to be removed
    {
        *pHead = temp->next; // Change head
        free(temp); // free old head
        return;
    }
    for (int i = 0; temp != NULL && i < position - 1; ++i)// Find previous node of the node to be deleted
    {
        temp = temp->next;
    }
    if (temp == NULL || temp->next == NULL)// If position is more than number of nodes
    {
        return;
    }
    struct node* next = (temp->next)->next;// Node temp->next is the node to be deleted// Store pointer to the next of node to be deleted
    free(temp->next); // Unlink the node from linked list// Free memory
    temp->next = next; // Unlink the deleted node from list
}

void deleteList(struct node** pHead)
{
   struct node* current = *pHead;
   struct node* next;

   while (current != NULL)
   {
       next = current->next;
       free(current);
       current = next;
   }
   *pHead = NULL;/* deref head_ref to affect the real head back in the caller. */
}

int getCount(struct node* head)
{
    int count = 0;  // Initialize count
    struct node* current = head;  // Initialize current
    while (current != NULL)
    {
        ++count;
        current = current->next;
    }
    return count;
}

int search(struct node* head, int hladam)
{
    struct node* current = head;  // Initialize current
    while (current != NULL)
    {
        if (current->hodnota == hladam)
            return 1;
        current = current->next;
    }
    return 0;
}

int getNkey(struct node* head, int index)
{
    struct node* current = head;

    // the index of the
    // node we're currently
    // looking at
    int count = 0;
    while (current != NULL)
    {
        if (count == index)
        {
            return (current->hodnota);
        }
        count++;
        current = current->next;
    }

    /* if we get to this line,
       the caller was asking
       for a non-existent element
       so we assert fail */
    assert(0);
}

void sortLinkedList(struct node** pHead)
{
  struct node *current = *pHead;
  struct node *index = NULL;
  int temp;

  if (pHead == NULL)
  {
    return;
  }
  else
  {
      while (current != NULL)
      {
        // index points to the node next to current
        index = current->next;

        while (index != NULL)
        {
            if (current->hodnota > index->hodnota)
            {
              temp = current->hodnota;
              current->hodnota = index->hodnota;
              index->hodnota = temp;
            }
            index = index->next;
        }
        current = current->next;
      }
  }
}

void pop(struct node ** pHead)
{
    if((*pHead)==NULL)
    {
        return;
    }
    struct node * temp=*pHead;
    *pHead = (*pHead)->next;
    free(temp);
}
