#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student{
    char firstname[50];
    char lastname[50];
    int age;
};

typedef struct Student Student;

//So sánh theo firstname
int cmp_firstname(const void *pa, const void *pb){
    Student *a = (Student*)pa;
    Student *b = (Student*)pb;
    return strcmp(a->firstname, b->firstname);
}

//So sánh theo lastname
int cmp_lastname(const void *pa, const void *pb){
    Student *a = (Student*)pa;
    Student *b = (Student*)pb;
    return strcmp(a->lastname, b->lastname);
}

void isolder(void *pa){
    Student *a = (Student*)pa;
    if(a->age > 20){
        printf("%s %s %d\n", a->firstname, a->lastname, a->age);
    }
}

void apply(Student *arr, int n, void (*fp)(void *)){
    for(int i = 0; i < n; i++){
        fp(arr + i);
    }
}

void print_list(Student *arr, int n){
    for (int i = 0; i < n; i++) {
        printf("%s %s %d\n", (arr + i)->firstname, (arr + i)->lastname, (arr + i)->age);
    }
    printf("\n");
}

int main(){
    Student arr[] = {
        {"Thanh", "Dat", 21},
        {"Thanh", "Vinh", 19},
        {"Khac", "Thanh", 22},
        {"Tuan", "Anh", 20},
        {"Que", "Lam", 23}
    };

    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Mang ban dau:\n");
    print_list(arr, n);

    //sort theo first name
    qsort(arr, n, sizeof(Student), cmp_firstname);
    printf("Mang sau khi sap xep theo first name:\n");
    print_list(arr, n);

    //sort theo last name
    qsort(arr, n, sizeof(Student), cmp_lastname);
    printf("Mang sau khi sap xep theo last name:\n");
    print_list(arr, n);

    //In sinh vien lon hon 20 tuoi
    printf("Sinh vien lon hon 20 tuoi:\n");
    apply(arr, n, isolder);
    return 0;
}
/*
OUTPUT:
Mang ban dau:
Thanh Dat 21
Thanh Vinh 19
Khac Thanh 22
Tuan Anh 20
Que Lam 23

Mang sau khi sap xep theo first name:
Khac Thanh 22
Que Lam 23
Thanh Dat 21
Thanh Vinh 19
Tuan Anh 20

Mang sau khi sap xep theo last name:
Tuan Anh 20
Thanh Dat 21
Que Lam 23
Khac Thanh 22
Thanh Vinh 19

Sinh vien lon hon 20 tuoi:
Thanh Dat 21
Que Lam 23
Khac Thanh 22
*/