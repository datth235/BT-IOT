#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define WORD_LEN 50
#define TABLE_SIZE 100

struct word{
    char data[WORD_LEN];
    int frequency;
    struct word *next;
};

typedef struct word* Word;

Word makeWord(char data[]){
    Word newWord = (Word)malloc(sizeof(struct word));
    strcpy(newWord->data, data);
    newWord->frequency = 1;
    newWord->next = NULL;
    return newWord;
}

int hash(char data[]){
    int i = 0;
    unsigned h = 0;
    while(data[i] != '\0'){
        h = h * 31 + data[i];
        i++;
    }
    return h % TABLE_SIZE;
}

//Thêm vào đầu dslk -> độ phức tạp O(1)
Word append(Word head, char data[]){
    Word newWord = makeWord(data);
    newWord->next = head;
    head = newWord;
    return head;
}

Word lookup(Word arr[], char data[]){
    int h = hash(data);
    Word head = arr[h];
    while(head != NULL){
        if(strcmp(head->data, data) == 0){
            head->frequency++;
            return head;
        }
        head = head->next;
    }
    arr[h] = append(arr[h], data);
    return NULL;
}

void print_list(Word head){
    if(head == NULL) return;
    while(head != NULL){
        printf("\t%s %d\n", head->data, head->frequency);
        head = head->next;
    }
}

void print_array(Word arr[]){
    for(int i = 0; i < TABLE_SIZE; i++){
        if(arr[i] != NULL){
            printf("Hash: %d\n", i);
            print_list(arr[i]);
        }
    }
}

int main(){
    Word arr[TABLE_SIZE] = {NULL};
    int cnt = 0;
    FILE *fp;
    char word[WORD_LEN];

    fp = fopen("data.txt", "r");
    if(fp == NULL){
        printf("Khong the mo file\n");
        return 0;
    }
    while(fscanf(fp, "%s", word) != EOF){
        cnt++;
        lookup(arr, word);
    }

    print_array(arr);
    printf("%d\n", cnt);
    return 0;
}
/*
Hash: 9
        programming 3
Hash: 10
        data 1
        apple 6
Hash: 15
        structure 1
Hash: 36
        science 1
Hash: 44
        dog 4
Hash: 50
        hash 4
Hash: 62
        cat 2
Hash: 65
        in 2
Hash: 69
        banana 4
Hash: 86
        orange 2
Hash: 87
        computer 1
Hash: 90
        table 3
Hash: 99
        c 2
36
*/