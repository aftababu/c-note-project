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
void header();
void hero();
void mainPage();
void createCategory();
void notesDisplay();
void createNote();
void getCurrentDateTime();

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
        header();

        int tempTotalNote=totalNote;
        if(strcmp(key,"Mpp")==0){
            displayPage(totalNote,"Mpp");
        }else{
            tempTotalNote=noteInPage;
            displayPage(tempTotalNote,"Npp");
        }
        getCurrentDateTime();

        // printf("helo %i %i %i",ant,tempTotalNote,activeNote);
        ch = _getch(); 
        if (ch == 0 || ch == 224) {
            ch = _getch();  
            if (ch == 72) { 
                if (activeNote <= 0) {
                    activeNote = tempTotalNote ;
                } else {
                    activeNote--;
                }
            } elif (ch == 80) {  
                if (activeNote >= tempTotalNote) {
                    activeNote = 0;
                } else {
                    activeNote++;
                }
            }
        }elif(ch == 13){
            if(activePage==0){
                if(activeNote==tempTotalNote  ){
                    createCategory();
                }else{
                    ant=activeNote;
                    gotoPage(1);
                }
            }elif( activePage==1){
                if(activeNote==tempTotalNote ){
                    createNote();
                }else{
                    subAnt=activeNote;
                    gotoPage(2);
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
            gotoxy(42, *boxWidth);
            printf("+-----------------------+\n");fflush(stdout);
            gotoxy(42, *boxWidth + 1);
               printf("%s", color);fflush(stdout);
            printf("|");fflush(stdout);
            gotoxy(50, *boxWidth + 1);
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
            gotoxy(66, *boxWidth + 1);
            printf("%s", color);fflush(stdout);
            printf("|");fflush(stdout);
            gotoxy(42, *boxWidth + 2);
            printf("%s", color);fflush(stdout);
            printf("+-----------------------+\n");fflush(stdout);
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


  
    gotoxy(42, boxWidth + 3);
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
    printf("%s", white);

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
    gotoxy(40, 4);
    printf("----------------------------------\n");
    gotoxy(40, 5);
    printf("  ---------- \033[1mMy Note\033[0m%s ----------\n",green);
    gotoxy(40, 6);
    printf("----------------------------------\n");
    printf("%s",white);  

}

// ### mainpage funtions ###
void hero() {

    int totalNote;
    readCategory(&totalNote);
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

    // keyControl(notesCNT,"Npp");
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
    readNotesById(totalNote);

            gotoxy(20,15);
            printf("title : %s\n",subNpp[subAnt].title);
            gotoxy(20,17);
            printf("___________________________________________________");
            gotoxy(20,19);
            printf("content : %s",subNpp[subAnt].content);


    getchar();
 }



// ######### utils ##########
void getCurrentDateTime() {
  
        time_t now = time(NULL);
        struct tm *local = localtime(&now);

        gotoxy(50, 55); 
        printf("%02d:%02d:%02d", local->tm_hour, local->tm_min, local->tm_sec);
        Sleep(1000);
        getCurrentDateTime();
        // gotoxy(40,10);
 
}
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
            activeNote=subAnt;
            viewNote();
        }
    }

    
}

void readNotes(int *notesCNT){
    FILE *fr;
    fr= fopen("notes.txt","r");
    if (fr == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }
    fscanf(fr, "%d", notesCNT); 
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