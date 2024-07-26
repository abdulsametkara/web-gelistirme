#include <stdio.h>
#include <stdlib.h>

int main()
{
    /*

    int %d
    float %f
    double %lf
    char %c

    */

    /*int a = 15;
    printf("%d\n" , a);

    int b ,c ;
    b = 2;
    c = 1;
    printf ("%d\n%d\n",b,c);
    */

    /*float a = 2.78;
    double b = 6.97;


    printf("%.3f %.2lf" , a,b);
    */

    /*float a = 5.789;
    double b = 5.123;
    char c = 'A';

    printf("first number : %.2f\nsecond number : %.3lf\nchar : %c",a,b,c);
    */

    /*float a ;
    printf("enter a number : \n");
    scanf("%f", &a);
    printf("number is %f", a);*/

    float a ;
    float b ;
    char c ;

    printf("enter first number\n");
    scanf("%f",&a);
    printf("enter second number\n");
    scanf("%f",&b);
    printf("enter a char\n");
    scanf(" %c",&c);
    printf("first number is : %f\nsecond number is : %f\nchar is : %c",a,b,c);


    return 0;
}
