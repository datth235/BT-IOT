#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hashtable.h"

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