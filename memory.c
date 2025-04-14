#include <stdio.h>
#include <stdlib.h>

int* intP(int num){
    int* ptr = (int*)malloc(sizeof(int));
    if(ptr == NULL){
        printf("fucntion falied!\n");
        returnn NULL;
    }
    *ptr = num;
    return ptr;
}
int main() {
    // Write C code here
    // question 4
    int*m = intP(4);
    if(m != NULL){
        printf("%d\n",*m);
        free(m)
    }
    return 0;
}