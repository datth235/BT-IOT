#ifndef HASHTABLE_H
#define HASHTABLE_H

#define MAX_BUCKETS 100
#define MULTIPLIER 31
#define MAX_NAME_LEN 100
#define PHONE_LEN 11

struct Node{
    char name[MAX_NAME_LEN];
    char phone[PHONE_LEN];
    struct Node* next;
};

typedef struct Node* node;

extern node buckets[MAX_BUCKETS];

// Hàm
node makeNode(char *name, char *phone);
unsigned int hash(char* str);
void insert(char* name, char* phone);
node* search(char* name);
void deleteNode(char* name);
void print();
void Copy(char *des, char *src);
int Compare(char *a, char *b);
void pause();

#endif