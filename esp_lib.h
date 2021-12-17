/*
ESP-Lib is a simple library file that has the commonly used 
functions and structures used by Student.c and University.c programs.
*/

#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include<math.h>

int response();//This Function takes binary response(Yes=1 or No=0 or Invalid = -1)
int getN_S();//Gets Number of Subjects

void showHeading(char string[]);
void showHeadingLn(char string[]);

struct date{
    int day;
    int month;
    int year;
};


struct date stringToDate(char date_string[]); //convert string to Date
void dateExtracter(char str[],struct date dt); //just does the opposite of the above

void toString(char[],int);//converts integer to string
int toInt(char[]);//converts string to integer

//max 10 subjects allowed
struct subject{
    char name[20];//uniquely identifies a subject
    int n_t;//number of topics
    char topic[20][50];//there can be max 50 number of topics in a subject
};

struct syllabus{
    struct subject sub_arr[10];
    int n_s;
};


int toInt(char str[]){
    int len = strlen(str);
    int i, num = 0;
    for (i = 0; i < len; i++){
        num = num + ((str[len - (i + 1)] - '0') * pow(10, i));
    }
   return num;
}

void toString(char str[], int num){
    int i, rem, len = 0, n;
    n = num;
    while (n != 0){
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++){
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}

void dateExtracter(char date_string[], struct date dt){
    char day[3];
    char month[3];
    char year[5];
    toString(day,dt.day);
    toString(month,dt.month);
    toString(year,dt.year);

    strcpy(date_string,day);
    strcat(date_string,"/");
    strcat(date_string,month);
    strcat(date_string,"/");
    strcat(date_string,year);
}

struct date stringToDate(char date_string[]){
    struct date dt;
    char day[3]={date_string[0],date_string[1],'\0'};
    char month[3]={date_string[3],date_string[4],'\0'};
    char year[5]={date_string[6],date_string[7],date_string[8],date_string[9],'\0'};
    dt.day=toInt(day);
    dt.month=toInt(month);
    dt.year=toInt(year);
    return dt;
}

int response(){
    //Yes=1
    //No=0
    //Invalid=-1
    int i=0;
    char response[3];
    gets(response);
    strlwr(response);
    if( strcmp( response,"yes" )==0 || (  response[0]=='y' && (strlen(response)==1) )   ){
        i=1;
    }else if( strcmp( response,"no" )==0 || ( (response[0]=='n') && (strlen(response)==1) )   ){
        i=0;
    }else{
        i=-1;
    }
    return i;
}

struct exam{
    struct subject exam_subject[10];
    struct date exam_date[10];
};

void showHeading(char string[]){
    int i,l=strlen(string);
    printf("\n");
    for(i=1;i<=l;i++){
        printf("-");
    }
    printf("\n");
    printf("%s", string);

    printf("\n");
    for(i=1;i<=l;i++){
        printf("-");
    }
}

void showHeadingLn(char string[]){
    int i,l=strlen(string);
    printf("\n");
    for(i=1;i<=l;i++){
        printf("-");
    }
    printf("\n");
    printf("%s", string);

    printf("\n");
    for(i=1;i<=l;i++){
        printf("-");
    }
    printf("\n");
}

int getN_S(){
    int n=0;
    struct syllabus syll;
    FILE *infile = fopen("Resources//UniversityDatabase//syllabus", "rb");
    fread(&syll, sizeof(struct syllabus), 1, infile);
    n=syll.n_s;
    fclose (infile);
    return n;
}

const int monthdays[12]={31, 28, 31, 30, 31, 30,31, 31, 30, 31, 30, 31};

int countLeapYears(struct date d){
    int years = d.day;
    if (d.month <= 2)
        years--;
    return ((years / 4) - (years / 100) + (years / 400));
}

int getDaysInBetween(struct date dt1,struct date dt2){

    long int n1 = dt1.year*365 + dt1.day;

    for (int i=0; i<dt1.month - 1; i++)
        n1 += monthdays[i];

    n1 += countLeapYears(dt1);
    long int n2 = dt2.year*365 + dt2.day;
    for (int i=0; i<dt2.month - 1; i++)
        n2 += monthdays[i];

    n2 += countLeapYears(dt2);
    int number_of_days;
    if(n1>n2)
        number_of_days=n1-n2+((dt1.year-dt2.year)/3);
    else
        number_of_days=n2-n1+((dt2.year-dt1.year)/3);
    return number_of_days;

}

struct date getMinDate(struct date dt[] , int n)
{
    struct date min_date;
    min_date.day=dt[0].day;
    min_date.year=dt[0].year;
    min_date.month=dt[0].month;
    int c=0;int i;
    for(i=1;i<n;i++)
    {
        if(dt[i].year<min_date.year)
        {
            c=i;
        }
        else if(dt[i].year==min_date.year)
        {
            if((dt[i].month==min_date.month)&&(dt[i].day==min_date.day))
            {
            }
            else if(dt[i].month<min_date.month)
            {
                c=i;
            }
            else if(dt[i].month==min_date.month)
            {
                if(dt[i].day<min_date.day)
                {
                    c=i;
                }
                else if(dt[i].day==min_date.day)
                {
                }

            }
        }
        min_date.day=dt[c].day;
    min_date.year=dt[c].year;
    min_date.month=dt[c].month;
    }


    return min_date;
}
