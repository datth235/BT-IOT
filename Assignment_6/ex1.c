#include<stdio.h>
#include<string.h>

#define MAXLEN 100

int strend(char s[], char t[]){
    int i = strlen(s) - 1, j = strlen(t) - 1;

    if(i < j) return 0;

    while(j >= 0){
        if(t[j] != s[i]) return 0;
        i--;
        j--;
    }
    return 1;
}

int main(){
    printf("%d\n", strend("hello","lo"));   // 1
    printf("%d\n", strend("hello","he"));   // 0
    printf("%d\n", strend("hello","hello")); // 1
    printf("%d\n", strend("hi","hello"));   // 0
    return 0;
}