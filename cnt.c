/*1から1000000000まで総和を求めて出力するプログラム*/

#include <stdio.h>

int main(void){
    long long int sum = 0;
    long int i;

    for(i=1;i<=1000000000;i++){
       sum +=i;
    }
    printf("%lld", sum);

    return 0;

}

