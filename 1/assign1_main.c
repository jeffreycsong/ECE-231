
#include <stdio.h>
void dec_to_bi(int);

int main(void){
    int user_dec;
    int user_base;

    do {
    printf("Please enter a number & base separated by a space (enter 0 0 to quit)...");
    scanf("%d %d", &user_dec, &user_base);


    if (user_base == 16){
        printf("%d in the base %d = %X\n", user_dec, user_base, user_dec);
    } else if (user_base == 10){
        printf("%d in the base %d = %d\n", user_dec, user_base, user_dec);
    } else if (user_base == 8){
        printf("%d in the base %d = %o\n", user_dec, user_base, user_dec);
    } else if (user_base == 2){
        dec_to_bi(user_dec);
    } else if (user_base == 0){
        if (user_dec == 0){
            break;
        }
        else{
            printf("\nPlease enter a base of either 16, 10, 8, or 2\n");
        }
    } else {
        printf("\nPlease enter a base of either 16, 10, 8, or 2\n");
    }

    } while (user_dec + user_base != 0);

}

void dec_to_bi(int dec){
    int d[10], i, j;
    printf("%d in the base 2 = ", dec);
    if (dec == 0){
        printf("0");
    } else {
        for (i = 0; dec>0; i++){
            d[i] = dec % 2;
            dec = dec / 2;
        }
        for (i = i - 1; i >= 0; i--){
            printf("%d", d[i]);
        }
    }

    printf("\n");
}