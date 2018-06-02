//写冒泡排序可以排序多个字符串。
#include<stdio.h>
#include<string.h>
void arr_bubble_sort(char(*p)[10])//数组指针，即指向大小为10的数组的指针
{
     int i = 0;
     int j = 0;
     char temp[10] ;
     char *t = temp;
     for (i = 0; i < 3; i++)
     {
        for (j = 0; j < 3 - i-1; j++)
        {
           if (strcmp(p[j], p[j + 1])>0)
           {
              strcpy(t, p[j]);
              strcpy(p[j], p[j + 1]);
              strcpy(p[j + 1], t);
           }
        }
     }
}
int main()
{
     char a[3][10] = { "add", "aedd", "addd" };
     char i = 0;
     char (*p)[10] = { 0 };
     p = a;//p指向a的第0行
     arr_bubble_sort(p);
     for (i = 0; i < 3; i++)
     {
        printf("%s  ", a[i]);//按行输出
     }
     system("pause");
     return 0;
}