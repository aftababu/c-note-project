#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#include <time.h>

#define elif else if
#define PI acos(-1.0)

char red[12]="\033[0;31m";
char green[12]="\033[0;32m";
char yellow[12]="\033[0;33m";
char white[12]="\033[0;0m";


// functions prototype
void gotoPage(int page);
void gotoxy(int x, int y );
void noteCurdOP(int pageY);
void header();
void hero();
void mainPage();
void createCategory();
void notesDisplay();
void createNote();
void deleteNote();
void editNote();
// void getCurrentDateTime();

struct categoryProps {
    int id;
    char title[100];
};
struct notesProps{
    int id;
    int categoryID;
    char title [100];
    char content [1000];
};
char *noteCRUD[3]={"back","edit","delete"};
typedef struct categoryProps catPP;
typedef struct notesProps notePP;

void readNotes(int *notesCNT); 
void readNotesById(int notesCNT);
void keyControl(int totalNote, char key[4]) ;
void displayPage(int totalNote,char key[4]);
void readCategory(int *totalNote);
 void viewNote();

// ######   gobal initialization   ######
int activeNote = 0;
int activePage = 0;
int running = 1;
int ant=0;
int subAnt=0;
int noteInPage=0;
int mainX=50;
int textX=12;
int lastborderX=31;
catPP *Mpp;
notePP *Npp,*subNpp;

// gcc main.c -o main.exe && ./main.exe



int main() {
   srand(time(NULL));

    gotoPage(activePage);

    return 0;
}






void keyControl(int totalNote,char key[4]) {
    int ch;

    while (1) {
        if(strcmp(key,"crud")!=0){
        header();
        }

        int tempTotalNote=totalNote;
        if(strcmp(key,"Mpp")==0){
            displayPage(totalNote,"Mpp");
        }elif(strcmp(key,"Npp")==0){
            tempTotalNote=noteInPage;
            displayPage(tempTotalNote,"Npp");
        }else{
            tempTotalNote=1;
            noteCurdOP(totalNote);
        }
        // getCurrentDateTime();

        // printf("helo %i %i %i",ant,tempTotalNote,activeNote);
        ch = _getch(); 
        if (ch == 0 || ch == 224) {
            ch = _getch();  
            if (ch == 72) { 
                if (activeNote <= 0) {
                    activeNote = tempTotalNote+1 ;
                } else {
                    activeNote--;
                }
            } elif (ch == 80) {  
                if (activeNote >= tempTotalNote+1) {
                    activeNote = 0;
                } else {
                    activeNote++;
                }
            }
        }elif(ch == 13){
            if(activePage==0){
                if(activeNote==tempTotalNote  ){
                    createCategory();
                }elif(activeNote==tempTotalNote+1){
                    exit(1);
                }else{
                    ant=activeNote;
                    gotoPage(1);
                }
            }elif( activePage==1){
                if(activeNote==tempTotalNote ){
                    createNote();
                }elif(activeNote==tempTotalNote+1){
                    activePage--;
                    gotoPage(activePage);
                }
                else{
                    subAnt=activeNote;
                    gotoPage(2);
                }
            }
            elif(activePage==2){

                if(activeNote==tempTotalNote){
                    gotoPage(3);
                    // edit note
                }elif(activeNote==tempTotalNote+1){
                    deleteNote();
                    // delete note
                }else{
                    gotoPage(1);
                }
                
            }

            
        }
         else {
            if(ch==8){
                if(activePage==0){
                printf("\n Exiting...\n");
                exit(1);
                }else{
                    gotoPage(--activePage);
                }
            }elif (ch == 27) {  
                printf("\n Exiting...\n");
                exit(1);
            } 
        }

    }
}

void boxofTitle(char color[],int *boxWidth,int i,char key[4]){
 
            printf("%s", color);fflush(stdout);
            gotoxy(mainX, *boxWidth);
            printf("+------------------------------+\n");fflush(stdout);
            gotoxy(mainX, *boxWidth + 1);
               printf("%s", color);fflush(stdout);
            printf("|");fflush(stdout);
            gotoxy(mainX+textX, *boxWidth + 1);
            if(strcmp(color,yellow)==0){
                if(strcmp(key,"Mpp")==0){
                    printf(">> %s", Mpp[i].title);fflush(stdout);
                }else{
                    printf(">> %s", subNpp[i].title);fflush(stdout);

                }

            }else{
                if(strcmp(key,"Mpp")==0){
                    printf("%s", Mpp[i].title);fflush(stdout);
                }else{
                    printf("%s", subNpp[i].title);fflush(stdout);
                }

            }
            gotoxy(mainX+lastborderX, *boxWidth + 1);
            printf("%s", color);fflush(stdout);
            printf("|");fflush(stdout);
            gotoxy(mainX, *boxWidth + 2);
            printf("%s", color);fflush(stdout);
            printf("+------------------------------+\n");fflush(stdout);
            *boxWidth += 3;
}



void displayPage(int totalNote,char key[4]) {
    int boxWidth = 15;
    
    int i;
    // if(strcmp(key,"Mpp")==0){
        for ( i = 0; i < totalNote; i++) {
        if (i == activeNote) {
           boxofTitle(yellow,&boxWidth,i,key);
        } else {
           boxofTitle(white,&boxWidth,i,key);
        }
    }
    // }


  
    gotoxy(53, boxWidth + 3);
    if(i==activeNote){
    printf("%s", yellow);
    }else{
    printf("%s", white);
    }
    
    if(strcmp(key,"Mpp")==0){
        printf("+----add new category----+\n");fflush(stdout);
    }else{
        printf("+----add new note----+\n");fflush(stdout);
    }
    gotoxy(62, boxWidth + 5);
    if(i+1==activeNote){
    printf("%s", yellow);
    }else{
    printf("%s", white);
    }
    if(activePage==0){
         printf("+exit+\n");fflush(stdout);
    }else{
         printf("+back+\n");fflush(stdout);

    }
    printf("%s", white);

}
void noteCurdOP(int pageY) {
    
    int i;
    gotoxy(20,pageY+5);
        for ( i = 0; i < 3; i++) {
        if (i == activeNote) {
            printf("%s",yellow);
            printf("<< %s >>",noteCRUD[i]);
        } else {
            printf("%s",white);
            printf(" %s ",noteCRUD[i]);
        }
    }
    printf("%s",white);
    printf("\n");
}



// ######## pages ########
void mainPage(){
    header();
    hero();

}

void notesContainer(){//subpage 1
header();
notesDisplay();

}




// ########### functions ###########
void header() {
    system("cls");
    printf("%s",green);   
    gotoxy(mainX-8, 4);
    printf("--------------------------------------------------\n");
    gotoxy(mainX, 5);
    printf("  ---------- \033[1mMy Note\033[0m%s ----------\n",green);
    gotoxy(mainX-8, 6);
    printf("--------------------------------------------------\n");
    printf("%s",white);  

}

// ### mainpage funtions ###
void hero() {

    int totalNote;
    readCategory(&totalNote);
    printf("%d",totalNote);
    if (Mpp != NULL) {
        keyControl(totalNote,"Mpp");
        free(Mpp); 
    }
    keyControl(totalNote,"Mpp");
    
    
}
void createCategory(){
    system("cls");
    header();
    gotoxy(40, 10);
    int totalNote;

    readCategory(&totalNote);

    printf("Enter category name : ");
    char title[100];
    gets(title);
    int x=strlen(title);
    if(x<1){
        printf("title is empty ; ");
        // exit(1);
        gotoPage(0);
        // activePage=0;
    }
    int f=1;
    int randId = 5437 + rand() % (32659 - 5437 + 1);
    FILE *fp;
    fp= fopen("category.txt","w");
    totalNote++;
 
     fprintf(fp,"%d\n",totalNote);
    for(int i=0;i<totalNote-1;i++){
        fprintf(fp,"%d\n%s\n",Mpp[i].id,Mpp[i].title);
        if(Mpp[i].id==randId){
            f=0;
        }
    }


    if(f){
   
        fprintf(fp,"%d\n%s\n",randId,title);

    }else{
        printf("error creating category");
        exit(1);
    }
    fclose(fp);
    hero();
    
}
// ###### notes container funtions ######

void notesDisplay(){
    int notesCNT;

    readNotesById(notesCNT);


    if (Npp != NULL) {
        keyControl(notesCNT,"Npp");
        free(Npp); 
    }

    keyControl(notesCNT,"Npp");
}
 void createNote(){
    system("cls");
    header();
    gotoxy(40, 10);
    int totalNote;

    readNotes(&totalNote);
    printf("%d",totalNote);
    FILE *fp;
    fp=fopen("notes.txt","w");
    fprintf(fp,"%d\n",totalNote+1);
    for(int i=0;i<totalNote;i++){
        fprintf(fp,"%d\n%d\n%s\n%s\n",Npp[i].id,Npp[i].categoryID,Npp[i].title,Npp[i].content);
    }

    int randId = 32700 + rand() % (60000 - 32700 + 1);

    char title[100];
    do{
    gotoxy(40, 10);
    printf("enter note title : ");
    gets(title);
    }while(strlen(title)<1);

    char content[1000]="";
    do{
        gotoxy(40, 13);
        printf("enter note content : ");
        gets(content);  
    }while(strlen(content)<2);
         
    fprintf(fp,"%d\n%d\n%s\n%s\n",randId,Mpp[ant].id,title,content);
    fclose(fp);
    notesContainer();
 }

 void viewNote(){
    system("cls");
    header();
    int totalNote;
    int pageY=15;
    readNotesById(totalNote);

            gotoxy(20,pageY);
            printf("title : %s\n",subNpp[subAnt].title);
            pageY+=2;
            gotoxy(20,17);
            printf("__________________________________________________________________________________________");
            pageY+=2;
            gotoxy(20,19);
            int x=strlen(subNpp[subAnt].content);
            printf("content : ");
            int br=0;
            for(int i=0;i<x;i++){
                br++;
                if(br>39){
                    if(subNpp[subAnt].content[i]==32){
                        pageY++;
                    br=0;
                    printf("\n\t\t\t\t\b\b\b");
                    }
                }
                printf("%c",subNpp[subAnt].content[i]);
            }
     

    keyControl(pageY,"crud");
 }



// ######### utils ##########
// void getCurrentDateTime() {
//     time_t now;
//     time(&now);

//     char* time_str = ctime(&now);

//     printf("%s", time_str);
  
// }
void gotoPage(int page){
    while(1){
        if(page==0){
            activePage=0;
            activeNote=0;
            mainPage();
        }elif(page==1){
            // readNotes()
            activePage=1;
            activeNote=0;
            notesContainer();
        }elif(page==2){
            activePage=2;
            activeNote=0;
            viewNote();
        }elif(page==3){
            activePage=3;
            
            editNote();
        }
    }

    
}
void editNote(){
 system("cls");
    header();
    int totalNote;
    int pageY=15;
    char title[100];
    int titleLen=strlen(title);
    char content[1000];
    readNotesById(totalNote);

            gotoxy(20,pageY);
            printf("current title : %s\n",subNpp[subAnt].title);
  
        pageY+=2;
        gotoxy(20,pageY);
        do{
        printf("enter new title : ");
        gets(title);
        }while(strlen(title)<1);

        
           
            pageY+=2;
            gotoxy(20,pageY);
            int x=strlen(subNpp[subAnt].content);
            printf("current content : ");
            int br=0;
            for(int i=0;i<x;i++){
                br++;
                if(br>39){
                    if(subNpp[subAnt].content[i]==32){
                        pageY++;
                    br=0;
                    printf("\n\t\t\t\t\b\b\b");
                    }
                }
                printf("%c",subNpp[subAnt].content[i]);
            }
            
            do{
            gotoxy(20,pageY+3);
            printf("new content : ");
     
            gets(content);  
            }while(strlen(content)<2);


           int noteCnt;

    readNotes(&noteCnt);
    printf("%d",noteCnt);
    FILE *fp;
    fp=fopen("notes.txt","w");
    fprintf(fp,"%d\n",noteCnt);
    for(int i=0;i<noteCnt;i++){
        if(Npp[i].id==subNpp[subAnt].id){
        fprintf(fp,"%d\n%d\n%s\n%s\n",Npp[i].id,Npp[i].categoryID,title,content);

        }else{

        fprintf(fp,"%d\n%d\n%s\n%s\n",Npp[i].id,Npp[i].categoryID,Npp[i].title,Npp[i].content);
        }
    }



         
    fclose(fp);
    gotoPage(2);
     



}
void deleteNote(){
    int ID;

    ID=subNpp[subAnt].id;
    int notesCNT;
    readNotes(&notesCNT);
    FILE *fp;
    fp=fopen("notes.txt","w");
    fprintf(fp,"%d\n",notesCNT-1);
    for(int i=0;i<notesCNT;i++){
        if(Npp[i].id!=ID){
            fprintf(fp,"%d\n%d\n%s\n%s\n",Npp[i].id,Npp[i].categoryID,Npp[i].title,Npp[i].content);
        }
    }

    fclose(fp);
    gotoPage(1);
}

void readNotes(int *notesCNT){
    FILE *fr;
    fr= fopen("notes.txt","r");
    if (fr == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }
    fscanf(fr, "%d", notesCNT); 
    if(*notesCNT>3000){
        *notesCNT=0;
    }
    Npp = (notePP *)malloc((*notesCNT) * sizeof(notePP));
       if (Npp == NULL) {
        printf("Memory allocation failed.\n");
        fclose(fr);
        return;
    }
    // printf("note cnt %i",ant);
    for (int i = 0; i < *notesCNT; i++) {
            fscanf(fr, "%d %d %[^\n] %[^\n]", &Npp[i].id,&Npp[i].categoryID, Npp[i].title,Npp[i].content);
    }


    fclose(fr);
} 
void readNotesById(int notesCNT){
    readNotes(&notesCNT);
    int x=0;
    noteInPage=0;
    for(int i=0;i<notesCNT;i++){
        if(Mpp[ant].id==Npp[i].categoryID){
            noteInPage++;
        }
    }
    subNpp=(notePP *) malloc((noteInPage)*sizeof(notePP));
        for(int i=0;i<notesCNT;i++){
        if(Mpp[ant].id==Npp[i].categoryID){
           subNpp[x++]=Npp[i];
        }
    }
}

void readCategory(int *totalNote) {
    FILE *fr = fopen("category.txt", "r");

    if (fr == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    fscanf(fr, "%d", totalNote); 
    if(*totalNote>3000){
        *totalNote=0;
    }
    Mpp = (catPP *)malloc((*totalNote) * sizeof(catPP));
    if (Mpp == NULL) {
        printf("Memory allocation failed.\n");
        fclose(fr);
        return;
    }

    for (int i = 0; i < *totalNote; i++) {
        fscanf(fr, "%d %[^\n]", &Mpp[i].id, Mpp[i].title);
    }

    fclose(fr);
}


void gotoxy(int x, int y) {
   printf("\033[%d;%dH", y+1, x+1);
   fflush(stdout);
}


// gcc main.c -o main.exe && ./main.exe