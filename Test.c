#include <stdio.h>

struct test{
    int n;
    int a;
    int b;
};

int main(){
    struct test testing;
    testing.a = 1;
    printf("%d\n", testing.a);
