#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include<math.h>
#include "esp_lib.h"
void getNextExamSchedule(struct subject sub_arr[],int n_s);

void main(){

    //Creating Directories if not already created
    CreateDirectory("Resources",NULL);
    char UniversityDatabase[30]="Resources\\UniversityDatabase";
    CreateDirectory(UniversityDatabase,NULL);
    //Welcome Screen for University

    int i,n_s=5;//number of subjects
    struct subject sub_arr[n_s];

    strcpy(sub_arr[0].name,"evs");
    strcpy(sub_arr[1].name,"pic");
    strcpy(sub_arr[2].name,"physics");
    strcpy(sub_arr[3].name,"math");
    strcpy(sub_arr[4].name,"mechanics");

    for(i=0;i<n_s;i++){
        printf("%s%s:","Enter Number of topics in ",sub_arr[i].name);
        scanf("%d",&sub_arr[i].n_t);
    }

    for(i=0;i<n_s;i++){
        printf("Enter Topic name(s) of %s:\n",sub_arr[i].name);
        int j=0;
        for(j=0;j<sub_arr[i].n_t;j++){
            fflush(stdin);
            gets(sub_arr[i].topic[j]);
        }
    }

    //saving sub_arr to file
    {
        struct syllabus syll;
        syll.n_s=n_s;
        for(i=0;i<n_s;i++){syll.sub_arr[i]=sub_arr[i];}
        FILE *outfile=fopen("Resources//UniversityDatabase//syllabus","wb");
        fwrite(&syll, sizeof(struct syllabus), 1, outfile);
        fclose(outfile);
    }

    for(i=0;i<n_s;i++){
        char dir[100];
        strcpy(dir,UniversityDatabase);
        strcat(dir,"\\");
        strcat(dir,sub_arr[i].name);
        //puts(dir);
        CreateDirectory(dir,NULL); //subject dir creation
        strcat(dir,"\\");
        int j=0;
        for(j=0;j<sub_arr[i].n_t;j++){
            char topic_dir[100];
            strcpy(topic_dir,dir);
            strcat(topic_dir,sub_arr[i].topic[j]);
            //puts(topic_dir);
            CreateDirectory(topic_dir,NULL);//topic dir creation
        }
    }
    getNextExamSchedule(sub_arr,n_s);

}

void getNextExamSchedule(struct subject sub_arr[],int n_s){

    showHeadingLn("Enter Next Exam Details:");

    struct exam next_exam;
    int i;
    for(i=0;i<n_s;i++){
        next_exam.exam_subject[i]=sub_arr[i];

        char date_string[11];
        printf("Enter Exam Date(DD/MM/YYYY) of %s:",sub_arr[i].name);
        fflush(stdin);
        gets(date_string);
        next_exam.exam_date[i]=stringToDate(date_string);
    }

    FILE *outfile;
    outfile = fopen("Resources//UniversityDatabase//next_exam", "wb");
    fwrite (&next_exam, sizeof(struct exam), 1, outfile);
    fclose (outfile);

}