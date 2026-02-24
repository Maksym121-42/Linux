#include <stdio.h>
#include <string.h>

#define MAX 100

struct Student{
    char name[50];
    char birth[20];
    char address[100];
};

struct Student s[MAX];
int count=0;


void add(){
    if(count>=MAX){
        printf("База заповнена\n");
        return;
    }

    printf("Ім'я: ");
    scanf(" %[^\n]",s[count].name);

    printf("Дата народження: ");
    scanf(" %[^\n]",s[count].birth);

    printf("Адреса: ");
    scanf(" %[^\n]",s[count].address);

    count++;
    printf("Додано\n");
}


void show(){
    int i;
    for(i=0;i<count;i++){
       printf("\n%d\n",i+1);
        printf("%s\n",s[i].name);
        printf("%s\n",s[i].birth);
        printf("%s\n",s[i].address);
    }
}


void edit(){
    int n;
    printf("Номер: ");
    scanf("%d",&n);

    if(n>=0&&n<count){
        printf("Нове ім'я: ");
        scanf(" %[^\n]",s[n].name);

        printf("Нова дата: ");
        scanf(" %[^\n]",s[n].birth);

        printf("Нова адреса: ");
        scanf(" %[^\n]",s[n].address);

        printf("Змінено\n");
    }else{
        printf("Помилка\n");
    }
}


void del(){
    int n,i;
    printf("Номер: ");
    scanf("%d",&n);

    if(n>=0&&n<count){
        for(i=n;i<count-1;i++){
            s[i]=s[i+1];
        }
        count--;
        printf("Видалено\n");
    }else{
        printf("Помилка\n");
    }
}


void search(){
    char t[50];
    int i,f=0;

    printf("Пошук: ");
    scanf(" %[^\n]",t);

    for(i=0;i<count;i++){
        if(strstr(s[i].name,t)||strstr(s[i].birth,t)||strstr(s[i].address,t)){
            printf("\n%d\n",i);
            printf("%s\n",s[i].name);
            printf("%s\n",s[i].birth);
            printf("%s\n",s[i].address);
            f=1;
        }
    }

    if(!f){
        printf("Нічого не знайдено\n");
    }
}


int main(){
    int c;

    do{
        printf("\n1-Додати\n");
        printf("2-Показати\n");
        printf("3-Редагувати\n");
        printf("4-Видалити\n");
        printf("5-Пошук\n");
        printf("0-Вихiд\n");
        printf("Вибiр: ");

        scanf("%d",&c);

        switch(c){
            case 1:add();break;
            case 2:show();break;
            case 3:edit();break;
            case 4:del();break;
            case 5:search();break;
        }

    }while(c!=0);

    return 0;
}
