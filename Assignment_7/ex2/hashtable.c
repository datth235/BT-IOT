#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

// copy chuỗi
void Copy(char *des, char *src){
    int i = 0;
    while(src[i] != '\0'){
        des[i] = src[i];
        i++;
    }
    des[i] = '\0';
}

// so sánh chuỗi
int Compare(char *a, char *b){
    return strcmp(a, b) == 0;
}

// tạo node
node makeNode(char *name, char *phone){
    node newNode = (node)malloc(sizeof(struct Node));
    Copy(newNode->name, name);
    Copy(newNode->phone, phone);
    newNode->next = NULL;
    return newNode;
}

// hash
unsigned int hash(char *str){
    unsigned int ret = 0;
    while(*str){
        ret = ret * MULTIPLIER + *str;
        str++;
    }
    return ret % MAX_BUCKETS;
}

// insert
void insert(char *name, char *phone){
    node newNode = makeNode(name, phone);
    unsigned int idx = hash(name);
    newNode->next = buckets[idx];
    buckets[idx] = newNode;
}

// search
node* search(char *name){
    int cnt = 0;
    node head = buckets[hash(name)];

    while(head){
        if(Compare(head->name, name)) cnt++;
        head = head->next;
    }

    if(cnt == 0) return NULL;

    node* ret = (node*)malloc((cnt + 1) * sizeof(node));

    int i = 0;
    head = buckets[hash(name)];
    while(head){
        if(Compare(head->name, name)){
            ret[i++] = head;
        }
        head = head->next;
    }
    ret[cnt] = NULL;
    return ret;
}

// delete
void deleteNode(char *name){
    node* result = search(name);

    if(result == NULL){
        printf("Khong tim thay!\n");
        return;
    }

    int n = 0;
    while(result[n]) n++;

    int choice = 1;

    if(n > 1){
        for(int i = 0; i < n; i++){
            printf("%d. %s - %s\n", i + 1, result[i]->name, result[i]->phone);
        }

        printf("Chon so muon xoa: ");
        scanf("%d", &choice);

        while(choice < 1 || choice > n){
            printf("Nhap lai: ");
            scanf("%d", &choice);
        }
    }

    node target = result[choice - 1];
    unsigned int idx = hash(name);

    node cur = buckets[idx], prev = NULL;

    while(cur){
        if(cur == target){
            if(prev == NULL) buckets[idx] = cur->next;
            else prev->next = cur->next;

            free(cur);
            printf("Da xoa!\n");
            break;
        }
        prev = cur;
        cur = cur->next;
    }

    free(result);
}

// print
void print(){
    int cnt = 0;

    for(int i = 0; i < MAX_BUCKETS; i++){
        node head = buckets[i];
        while(head){
            printf("%d. %s - %s\n", ++cnt, head->name, head->phone);
            head = head->next;
        }
    }

    if(cnt == 0){
        printf("Danh ba rong!\n");
    }
}

// pause
void pause(){
    printf("\nAn phim bat ky de tiep tuc...");
    getchar();
}