#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node* next;
};

typedef struct node* Node;
//Node = struct node*

Node makeNode(int data){
    Node newNode = (Node)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void display(Node head){
    if(head == NULL){
        printf("Rong\n");
        return;
    }
    
    while(head != NULL){
        printf("%d ", head->data);
        head = head->next;
    }
    putchar('\n');
}

Node addback(Node head, int data){
    Node newNode = makeNode(data);
    if(head == NULL){
        head = newNode;
        return head;
    }
    Node tmp = head;
    while(tmp->next != NULL) tmp = tmp->next;
    tmp->next = newNode;
    return head;
}

Node find(Node head, int data){
    if(head == NULL) return NULL;
    while(head != NULL){
        if(head->data == data) return head;
        head = head->next;
    }
    return NULL;
}

Node delnode(Node head, Node pelement){
    Node prev = head, next = head;
    while(next != pelement){
        prev = next;
        next = next->next;
    }
    prev->next = next->next;
    return head;
}

void freelist(Node head){
    Node tmp;
    while(head != NULL){
        tmp = head->next;
        free(head);
        head = tmp;
    }
}

int main(){
    Node head = NULL;
    display(head);
    head = addback(head, 1);
    head = addback(head, 2);
    head = addback(head, 3);
    head = addback(head, 4);
    head = addback(head, 5);
    display(head);
    Node x = find(head, 2);
    display(head);
    head = delnode(head, x);
    display(head);
    free(head);
    display(head);
    return 0;
}