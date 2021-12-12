#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include<math.h>
#include "esp_lib.h"

void showNextExamSchedule();

void showSyllabus();

struct ssc_marks{
    //All marks out of 100
    int math;
    int sci;
    int lang;
    int sst;
};

struct hsc_marks{
    //All marks out of 100
    int phy;
    int chem;
    int math;
    int lang;
};

struct student{
    //Max Name size: 20
    //Max roll number size: 20
    char name[20];
    int roll_number;
    //all out of 300
    float p1;
    float p2;
    float p3;
};

void createTimeTable(struct student);

void main(){

    //Creating Directories if not already created
    CreateDirectory("Resources",NULL);
    char *StudentDatabase="Resources\\StudentDatabase";
    CreateDirectory(StudentDatabase,NULL);

    //Welcome Screen for Student
    showHeadingLn("Efficient Study Planner");


    int response_output;
    while(1){
            //Check whether a student is using this for the first time
    printf("\nAre you using ESP for the first time?(Y/N)\n");
     response_output=response();
            if(response_output==0){
                break;
    }else if(response_output==1){

        showHeadingLn("     SIGN UP     ");
        struct student stu;
        //Taking Input of Past Records from Student
        printf("\nEnter your Name:");

        gets(stu.name);

        while(1){
            printf("\nEnter your Roll Number:");
            fflush(stdin);
            int error_check=scanf("%d",&stu.roll_number);
            if(error_check!=1){
                printf("\nInvalid Input. Please try again.\n");
                continue;
            }
            break;
        }

            struct ssc_marks SM;

            showHeadingLn("Enter your 10th Marks details:\n(Out of 100)\n(Integers only)");

            printf("\nMath:");
            scanf("%d", &SM.math);

            printf("Science:");
            scanf("%d", &SM.sci);

            printf("Language:");
            scanf("%d", &SM.lang);

            printf("SST:");
            scanf("%d", &SM.sst);

            struct hsc_marks HM;

            showHeadingLn("Enter your 12th Marks details:\n(Out of 100)\n(Integers only)");

            printf("\nPhysics:");
            scanf("%d", &HM.phy);
            printf("Chemistry:");
            scanf("%d", &HM.chem);
            printf("Math:");
            scanf("%d", &HM.math);
            printf("Language:");
            scanf("%d", &HM.lang);

            stu.p1=(SM.sst+(SM.lang/2)+(HM.lang/2))*(1.5);
            stu.p2=SM.sci+(SM.lang/2)+(HM.lang/2)+HM.chem;
            stu.p3=SM.math+HM.math+HM.phy;

            char roll_number[20];
            toString(roll_number,stu.roll_number);
            char dir[80];
            strcpy(dir,StudentDatabase);
            strcat(dir,"\\");
            strcat(dir,roll_number);
            CreateDirectory(dir,NULL);
            strcat(dir,"\\");
            strcat(dir,"student_details");

            printf("%s",dir);

            FILE *outfile=fopen(dir,"wb");
            fwrite(&stu, sizeof(struct student), 1, outfile);
            fclose(outfile);
            break;

        }else{

            printf("\nInvalid response. Please try again.\n");
            continue;
            //Handle Exception
            //Invalid input
        }
    }

    struct student stu_in;
    while(1){
        int roll_number_int;
        showHeadingLn("     SIGN IN     ");

        puts("Enter your Roll Number:");
        scanf("%d",&roll_number_int);

        char roll_number[20];
        toString(roll_number,roll_number_int);
        char dir[50];
        strcpy(dir,StudentDatabase);
        strcat(dir,"\\");
        strcat(dir,roll_number);
        strcat(dir,"\\");
        strcat(dir,"student_details");


        FILE *infile = fopen (dir, "rb");
        if (infile == NULL){
            fprintf(stderr, "\nNo Such roll number exists. Please try again.\n");
            continue;
        }else{}
        fread(&stu_in, sizeof(struct student), 1, infile);
        fclose (infile);
        break;
    }


    {
        char welcome_banner[30];
        strcpy(welcome_banner,"Welcome, ");
        strcat(welcome_banner, stu_in.name);
        showHeadingLn(welcome_banner);
    }


    while(1){

        showHeadingLn("     MENU     ");
        printf("\n1: Create my Personalized Time Table");
        printf("\n2: Show Syllabus");
        printf("\n3: Show Next Exam Schedule");
        printf("\n4: Show Strengths and Weakness");
        printf("\n0: LogOut & Exit");



        printf("\n");

        int error_check=scanf("%d",&response_output);
        //scanf string exception not handled


        if(response_output==1){

            //create new time_table

            createTimeTable(stu_in);

        }else if(response_output==2){
            //show syllabus
            showSyllabus();

        }else if(response_output==3){
            //show exam time table
            showNextExamSchedule();
        }else if(response_output==4){

            showHeadingLn("Strengths and Weakness\n(Out of 300 each)");
            printf("\n Memorization Score:%f",stu_in.p1);
            printf("\n Conceptual Grasping Score:%f",stu_in.p2);
            printf("\n Logical Aptitude Score:%f\n",stu_in.p3);


        }else if(response_output==0){
            exit(1);
        }else if(error_check!=1){
            printf("\nInvalid response. Please try again.\n");
            continue;
        }else{

        }

    }

}

void showNextExamSchedule(){

    showHeadingLn("Next Exam Schedule:");
    FILE *infile;
    struct exam input_exam;
    infile = fopen("Resources//UniversityDatabase//next_exam", "rb");
    fread(&input_exam, sizeof(struct exam), 1, infile);
    fclose (infile);
    int i,n_s=getN_S();
    for(i=0;i<n_s;i++){
        char date_string[11];
        dateExtracter(date_string,input_exam.exam_date[i]);
        printf("\n%s:%s",input_exam.exam_subject[i].name,date_string);
    }

}

void createTimeTable(struct student stu){

    float p1=stu.p1;
    float p2=stu.p2;
    float p3=stu.p3;
    int n_s=getN_S();
    int i;

    printf("\nEnter the date of start studying(DD/MM/YYYY):");
    struct date begin_date;
    char begin_date_string[11];
    fflush(stdin);
    gets(begin_date_string);
    begin_date=stringToDate(begin_date_string);

    //retrieving exam schedule
    struct exam next_exam;
    FILE *infile = fopen("Resources//UniversityDatabase//next_exam", "rb");
    fread(&next_exam, sizeof(struct exam), 1, infile);
    fclose(infile);

    int rate=5;// number of hours each day studied

    while(1){
        printf("\nEnter avg number of hours you can study daily:");

        int error_check=scanf("%d",&rate);
        if(error_check!=1){
            printf("\nInvalid Input. Please try again.");
            continue;
        }else{
            break;
        }
    }

    int n_hour_left;//number of hour left for beginning of exam

    n_hour_left=rate*getDaysInBetween(getMinDate(next_exam.exam_date,n_s),begin_date);

    //retrieving exam syllabus
    struct syllabus syll;
    FILE *infile1 = fopen("Resources//UniversityDatabase//syllabus", "rb");
    fread(&syll, sizeof(struct syllabus), 1, infile);
    fclose(infile1);

     //number of subjects in float
    float n_hour_left_each_sub=((float)n_hour_left)/((float)n_s);

    struct subject sub_arr[n_s];
    for(i=0;i<n_s;i++){
        sub_arr[i]=syll.sub_arr[i];
    }

    //It is now assumed that n_s=5

    struct subject sub_arr_o[5];

    if(p1>p2 && p2>p3){
        sub_arr_o[0]=sub_arr[4];
        sub_arr_o[1]=sub_arr[3];
        sub_arr_o[2]=sub_arr[2];
        sub_arr_o[3]=sub_arr[1];
        sub_arr_o[4]=sub_arr[0];

    }else if(p3>p2 && p2>p1){
        sub_arr_o[0]=sub_arr[0];
        sub_arr_o[1]=sub_arr[1];
        sub_arr_o[2]=sub_arr[2];
        sub_arr_o[3]=sub_arr[3];
        sub_arr_o[4]=sub_arr[4];

    }else if(p1>p3 && p3>p2){

        sub_arr_o[0]=sub_arr[1];
        sub_arr_o[1]=sub_arr[2];
        sub_arr_o[2]=sub_arr[3];
        sub_arr_o[3]=sub_arr[4];
        sub_arr_o[4]=sub_arr[0];

    }else if(p2>p3 && p3>p1){
        sub_arr_o[0]=sub_arr[0];
        sub_arr_o[1]=sub_arr[4];
        sub_arr_o[2]=sub_arr[3];
        sub_arr_o[3]=sub_arr[2];
        sub_arr_o[4]=sub_arr[1];

    }else if(p3>p1 && p1>p2){
        sub_arr_o[0]=sub_arr[1];
        sub_arr_o[1]=sub_arr[2];
        sub_arr_o[2]=sub_arr[0];
        sub_arr_o[3]=sub_arr[3];
        sub_arr_o[4]=sub_arr[4];


    }else if(p2>p1 && p1>p3){
        sub_arr_o[0]=sub_arr[4];
        sub_arr_o[1]=sub_arr[3];
        sub_arr_o[2]=sub_arr[0];
        sub_arr_o[3]=sub_arr[2];
        sub_arr_o[4]=sub_arr[1];

    }else{
        sub_arr_o[0]=sub_arr[4];
        sub_arr_o[1]=sub_arr[3];
        sub_arr_o[2]=sub_arr[2];
        sub_arr_o[3]=sub_arr[1];
        sub_arr_o[4]=sub_arr[0];
    }

    showHeadingLn("   Time Table   ");

    for(i=0;i<5;i++){
        printf("\n%s\n",sub_arr_o[i].name);
        int n_t=sub_arr_o[i].n_t;
        float temp=n_hour_left_each_sub/((float)n_t);
        int j;
        for(j=0;j<n_t;j++){
            printf("    %s:%f Hrs\n",sub_arr_o[i].topic[j],temp);
        }

    }

}

void showSyllabus(){

    //retrieving exam syllabus
    struct syllabus syll;
    FILE *infile = fopen("Resources//UniversityDatabase//syllabus", "rb");
    fread(&syll, sizeof(struct syllabus), 1, infile);
    fclose(infile);
    int i;
    for(i=0;i<5;i++){

        printf("\n%s\n",syll.sub_arr[i].name);
        int n_t=syll.sub_arr[i].n_t;

        int j;
        for(j=0;j<n_t;j++){
            printf("    %s \n",syll.sub_arr[i].topic[j]);
        }

    }

}