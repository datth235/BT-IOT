#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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

node buckets[MAX_BUCKETS];

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

// main
int main(){
    memset(buckets, 0, sizeof(buckets));

    while(1){
        printf("\n|----------------------------DANH BA----------------------------|\n");
        printf("|1. Nhap them so vao danh ba                                    |\n");
        printf("|2. Tim kiem                                                    |\n");
        printf("|3. Xoa                                                         |\n");
        printf("|4. In danh ba                                                  |\n");
        printf("|0. Thoat                                                       |\n");
        printf("|---------------------------------------------------------------|\n");

        int choice;
        printf("Nhap lua chon: ");
        scanf("%d", &choice);

        while(choice < 0 || choice > 4){
            printf("Nhap lai: ");
            scanf("%d", &choice);
        }

        getchar(); // clear buffer

        if(choice == 0) break;

        if(choice == 1){
            char name[MAX_NAME_LEN], phone[PHONE_LEN];

            printf("Nhap ten: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0';

            printf("Nhap so dien thoai: ");
            fgets(phone, sizeof(phone), stdin);
            phone[strcspn(phone, "\n")] = '\0';

            insert(name, phone);
        }
        else if(choice == 2){
            char name[MAX_NAME_LEN];

            printf("Nhap ten: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0';

            node* ret = search(name);

            if(ret == NULL){
                printf("Khong tim thay!\n");
            } 
            else{
                int i = 0;
                while(ret[i]){
                    printf("%d. %s - %s\n", i + 1, ret[i]->name, ret[i]->phone);
                    i++;
                }
                free(ret);
            }

            pause();
        }
        else if(choice == 3){
            char name[MAX_NAME_LEN];

            printf("Nhap ten muon xoa: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0';

            deleteNode(name);
            pause();
        }
        else if(choice == 4){
            print();
            pause();
        }
    }

    return 0;
}