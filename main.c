#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define MAXCHAR 1000;


//Structure definition
typedef struct card Card;
struct card{
    char value;
    char suit;
    //char column[3];
    //char field[3];
    bool visible;
    Card *next; //linked list
};

Card *CreateCard(char value, char suit, /*char * col, char * fie,*/ bool vis){
    Card *newCard;

    newCard = (Card *) malloc(sizeof(Card));
    newCard->value = value;
    newCard->suit = suit;
    //strcpy(newCard->column,col);
    //strcpy(newCard->field,fie);
    newCard->visible = vis;
    return newCard;
}

typedef struct deck Deck;
struct deck{
    Card cards;
};

typedef struct column Column;
struct column{
    Card cards;
};

Column * createColumn(Card cards){
    Column *newColumn;
    newColumn = (Column *) malloc(sizeof(Column));
    newColumn->cards = cards;
    return newColumn;
}

typedef struct field Field;
struct field{
    Card cards;
    char name[2];
};

Field *createField(Card cards, char name[]){
    Field *newField;
    newField = (Field *) malloc(sizeof(Field));
    newField->cards = cards;
    strcpy(newField->name,name);
    return newField;
}

typedef struct board Board;
struct board{
    Column  c1;
    Column  c2;
    Column  c3;
    Column  c4;
    Column  c5;
    Column  c6;
    Column  c7;
    Field   f1;
    Field   f2;
    Field   f3;
    Field   f4;
};

Board * createBoard(Column c1, Column c2, Column c3, Column c4, Column c5, Column c6, Column c7, Field f1, Field f2, Field f3, Field f4){
    Board *newBoard;
    newBoard = (Board *) malloc(sizeof(Board));
    newBoard->c1 = c1;
    newBoard->c2 = c2;
    newBoard->c3 = c3;
    newBoard->c4 = c4;
    newBoard->c5 = c5;
    newBoard->c6 = c6;
    newBoard->c7 = c7;
    newBoard->f1 = f1;
    newBoard->f2 = f2;
    newBoard->f3 = f3;
    newBoard->f4 = f4;
    return newBoard;
}

typedef struct savefile Savefile;
struct savefile{
    Board board;
    char moveList[10000][100];
    char undoList[10000][100];
    char CommandList[5000][100];
};

const char standardDeck[52][2] =
        {
                "2H",
                "3H",
                "4H",
                "5H",
                "6H",
                "7H",
                "8H",
                "9H",
                "TH",
                "JH",
                "QH",
                "KH",
                "AH",
                "2D",
                "3D",
                "4D",
                "5D",
                "6D",
                "7D",
                "8D",
                "9D",
                "TD",
                "JD",
                "QD",
                "KD",
                "AD",
                "2C",
                "3C",
                "4C",
                "5C",
                "6C",
                "7C",
                "8C",
                "9C",
                "TC",
                "JC",
                "QC",
                "KC",
                "AC",
                "2S",
                "3S",
                "4S",
                "5S",
                "6S",
                "7S",
                "8S",
                "9S",
                "TS",
                "JS",
                "QS",
                "KS",
                "AS"
        };

#define foreach(item, array) \
    for(int keep = 1, \
            count = 0,\
            size = sizeof (array) / sizeof *(array); \
        keep && count != size; \
        keep = !keep, count++) \
      for(item = (array) + count; keep; keep = !keep)

void switchPlace(Card *pCard, Card *pCard1);

void sr(Card * deck, int size){
    Card * firstCard = deck;
    Card * prevRandomCard1 = deck;
    Card * prevRandomCard2 = deck;
    int upper = size-1;
    int lower = 0;
    for (int i = 0; i < size; i++) {
        int r1 = (rand() % (upper - lower + 1)) + lower;
        int r2 = (rand() % (upper - lower + 1)) + lower;
        for(int j = 0; j<r1; j++){
            prevRandomCard1 = prevRandomCard1->next;
        }
        for(int j = 0; j<r2; j++){
            prevRandomCard2 = prevRandomCard2->next;
        }

        switchPlace(prevRandomCard1, prevRandomCard2);

        prevRandomCard1 = firstCard;
        prevRandomCard2 = firstCard;
    }
}

void switchPlace(Card *prevRandomCard1, Card *prevRandomCard2) {
    char suit = prevRandomCard1->suit;
    char value = prevRandomCard1->value;
    prevRandomCard1->suit = prevRandomCard2->suit;
    prevRandomCard1->value = prevRandomCard2->value;
    prevRandomCard2->suit = suit;
    prevRandomCard2->value = value;
}

void shuffle(char arr[52][2], int x_size, int y_size){

    srand(10);
    int upper = x_size-1;
    int lower = 0;
    for (int i = 0; i < x_size; i++) {
        int i1 = (rand() % (upper - lower + 1)) + lower;
        char t1 = arr[i][0];
        char t2 = arr[i][1];
        arr[i][0] = arr[i1][0];
        arr[i][1] = arr[i1][1];
        arr[i1][0] = t1;
        arr[i1][1] = t2;
    }
    //toLinkedList();
}

Board * prepareBoard(Card *deck){
    Board   *board = NULL;
    Column  *c1 = NULL;
    Column  *c2 = NULL;
    Column  *c3 = NULL;
    Column  *c4 = NULL;
    Column  *c5 = NULL;
    Column  *c6 = NULL;
    Column  *c7 = NULL;
    Field   *f1 = NULL;
    Field   *f2 = NULL;
    Field   *f3 = NULL;
    Field   *f4 = NULL;
    Card *ptr = NULL;
    c1 = createColumn(*deck);
    c1->cards.next = NULL;
    c1->cards.visible = true;
    deck = deck->next;
    c2 = createColumn(*deck);
    c2->cards.visible = false;
    c2->cards.next->visible = true;
    c2->cards.next->next->visible = true;
    c2->cards.next->next->next->visible = true;
    c2->cards.next->next->next->next->visible = true;
    c2->cards.next->next->next->next->next->visible = true;
    deck = deck->next->next->next->next->next->next;
    c2->cards.next->next->next->next->next->next = NULL;
    c3 = createColumn(*deck);
    c3->cards.visible = false;
    c3->cards.next->visible = false;
    c3->cards.next->next->visible = true;
    c3->cards.next->next->next->visible = true;
    c3->cards.next->next->next->next->visible = true;
    c3->cards.next->next->next->next->next->visible = true;
    c3->cards.next->next->next->next->next->next->visible = true;
    deck = deck->next->next->next->next->next->next->next;
    c3->cards.next->next->next->next->next->next->next = NULL;
    c4 = createColumn(*deck);
    c4->cards.visible = false;
    c4->cards.next->visible = false;
    c4->cards.next->next->visible = false;
    c4->cards.next->next->next->visible = true;
    c4->cards.next->next->next->next->visible = true;
    c4->cards.next->next->next->next->next->visible = true;
    c4->cards.next->next->next->next->next->next->visible = true;
    c4->cards.next->next->next->next->next->next->next->visible = true;
    deck = c4->cards.next->next->next->next->next->next->next->next;
    c4->cards.next->next->next->next->next->next->next->next = NULL;
    c5 = createColumn(*deck);
    c5->cards.visible = false;
    c5->cards.next->visible = false;
    c5->cards.next->next->visible = false;
    c5->cards.next->next->next->visible = false;
    c5->cards.next->next->next->next->visible = true;
    c5->cards.next->next->next->next->next->visible = true;
    c5->cards.next->next->next->next->next->next->visible = true;
    c5->cards.next->next->next->next->next->next->next->visible = true;
    c5->cards.next->next->next->next->next->next->next->next->visible = true;
    deck = c5->cards.next->next->next->next->next->next->next->next->next;
    c5->cards.next->next->next->next->next->next->next->next->next = NULL;
    c6 = createColumn(*deck);
    c6->cards.visible = false;
    c6->cards.next->visible = false;
    c6->cards.next->next->visible = false;
    c6->cards.next->next->next->visible = false;
    c6->cards.next->next->next->next->visible = false;
    c6->cards.next->next->next->next->next->visible = true;
    c6->cards.next->next->next->next->next->next->visible = true;
    c6->cards.next->next->next->next->next->next->next->visible = true;
    c6->cards.next->next->next->next->next->next->next->next->visible = true;
    c6->cards.next->next->next->next->next->next->next->next->next->visible = true;
    deck = c6->cards.next->next->next->next->next->next->next->next->next->next;
    c6->cards.next->next->next->next->next->next->next->next->next->next = NULL;
    c7 = createColumn(*deck);
    c7->cards.visible = false;
    c7->cards.next->visible = false;
    c7->cards.next->next->visible = false;
    c7->cards.next->next->next->visible = false;
    c7->cards.next->next->next->next->visible = false;
    c7->cards.next->next->next->next->next->visible = false;
    c7->cards.next->next->next->next->next->next->visible = true;
    c7->cards.next->next->next->next->next->next->next->visible = true;
    c7->cards.next->next->next->next->next->next->next->next->visible = true;
    c7->cards.next->next->next->next->next->next->next->next->next->visible = true;
    c7->cards.next->next->next->next->next->next->next->next->next->next->visible = true;
    deck = c7->cards.next->next->next->next->next->next->next->next->next->next->next;
    c7->cards.next->next->next->next->next->next->next->next->next->next->next = NULL;
    Card  *emptyCard = NULL;
    emptyCard = CreateCard(NULL,NULL,NULL/*,NULL,NULL*/);
    f1 = createField(*emptyCard,"F1");
    f2 = createField(*emptyCard,"F2");
    f3 = createField(*emptyCard,"F3");
    f4 = createField(*emptyCard,"F4");

    board = createBoard(*c1,*c2,*c3,*c4,*c5,*c6,*c7,*f1,*f2,*f3,*f4);
    return board;
}

Card * ld(char filename[]){
    FILE *fp;
    char row[1000];
    char *token;
    char filenameTmp[40];
    bool unixTypeOS = false;
    /*char cwd[10000];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working dir: %s\n", cwd);
    } else {
        perror("getcwd() error");
        return 1;
    }*/
    #ifdef _WIN32 // Includes both 32 bit and 64 bit
        #ifdef _WIN64
                printf("Windows 64 bit\n");
            #else
                printf("Windows 32 bit\n");
            #endif
    #else
        unixTypeOS = true;
    #endif

    if(unixTypeOS){
        //We need to go up one folder since mac is in the cmake-build-debug folder...
        strcpy(filenameTmp,"../");strcat(filenameTmp, filename);
        fp = fopen(filenameTmp,"r");
    }else{
        fp = fopen(filename,"r");
    }


    Card *newCard = NULL;
    Card *previous_card = NULL;
    Card *linked_list = NULL;
    while (fgets(row, 1000, fp) != NULL)
    {
        // fgets(row, 1000, fp);
        //printf("Row: %s", row);

        token = strtok(row, "\n"); //Separator

        while(token != NULL)
        {
            if(newCard!=NULL)
                previous_card = newCard;
            char value = *token;
            token++;
            char suit = *token;
            token = NULL;
            newCard = CreateCard(value,suit,NULL/*,NULL,NULL*/);
            if(previous_card!=NULL){
                previous_card->next=newCard;
            }else{
                linked_list = newCard;
            }
        }

    }
    return linked_list;
}

printTop(){
    for (int i = 1; i<8; i++){
        printf("%c%d\t",'C',i);
    }
    printf("\n\n");
}

printRight(){
    for (int i = 1; i<4; i++){
        printf("\t\t%s\t%c%d\n\n","[]","F",i);
    }
}

printFieldLine(Card *c1,Card *c2, Card *c3, Card *c4, Card *c5, Card *c6, Card *c7, Field *f){
    // region printFieldLine
    if(c1!=NULL && c1->value!=NULL)
        c1->visible ? printf("%c%c\t",c1->value,c1->suit) : printf("%s\t","[]");
    else
        printf("\t","");
    if(c2!=NULL && c2->value!=NULL)
        c2->visible ? printf("%c%c\t",c2->value,c2->suit) : printf("%s\t","[]");
    else
        printf("\t","");
    if(c3!=NULL && c3->value!=NULL)
        c3->visible ? printf("%c%c\t",c3->value,c3->suit) : printf("%s\t","[]");
    else
        printf("\t","");
    if(c4!=NULL && c4->value!=NULL)
        c4->visible ? printf("%c%c\t",c4->value,c4->suit) : printf("%s\t","[]");
    else
        printf("\t","");
    if(c5!=NULL && c5->value!=NULL)
        c5->visible ? printf("%c%c\t",c5->value,c5->suit) : printf("%s\t","[]");
    else
        printf("\t","");
    if(c6!=NULL && c6->value!=NULL)
        c6->visible ? printf("%c%c\t",c6->value,c6->suit) : printf("%s\t","[]");
    else
        printf("\t","");
    if(c7!=NULL && c7->value!=NULL)
        c7->visible ? printf("%c%c\t\t\t",c7->value,c7->suit) : printf("%s\t\t\t","[]");
    else
        printf("\t","");
    if(f!=NULL)
        f->cards.visible ? printf("%c%c\t",f->cards.value,f->cards.suit) : printf("%s\t%s","[]",f->name);
    printf("\n","");
    // endregion
}

printFieldLineFaceUp(Card *c1,Card *c2, Card *c3, Card *c4, Card *c5, Card *c6, Card *c7, Field *f){
    // region printFieldLineFaceUp
    if(c1!=NULL)
        printf("%c%c\t",c1->value,c1->suit);
    else
        printf("\t","");
    if(c2!=NULL)
        printf("%c%c\t",c2->value,c2->suit);
    else
        printf("\t","");
    if(c3!=NULL)
        printf("%c%c\t",c3->value,c3->suit);
    else
        printf("\t","");
    if(c4!=NULL)
        printf("%c%c\t",c4->value,c4->suit);
    else
        printf("\t","");
    if(c5!=NULL)
        printf("%c%c\t",c5->value,c5->suit);
    else
        printf("\t","");
    if(c6!=NULL)
        printf("%c%c\t",c6->value,c6->suit);
    else
        printf("\t","");
    if(c7!=NULL)
        printf("%c%c\t\t\t",c7->value,c7->suit);
    else
        printf("\t","");
    if(f!=NULL)
        f->cards.visible ? printf("%c%c\t",f->cards.value,f->cards.suit) : printf("%s\t%s","[]",f->name);
    printf("\n","");
    // endregion
}

printLine(Card *c1,Card *c2, Card *c3, Card *c4, Card *c5, Card *c6, Card *c7){
    // region printLine
    if(c1!=NULL)
        c1->visible ? printf("%c%c\t",c1->value,c1->suit) : printf("%s\t","[]");
    else
        printf("\t","");
    if(c2!=NULL)
        c2->visible ? printf("%c%c\t",c2->value,c2->suit) : printf("%s\t","[]");
    else
        printf("\t","");
    if(c3!=NULL)
        c3->visible ? printf("%c%c\t",c3->value,c3->suit) : printf("%s\t","[]");
    else
        printf("\t","");
    if(c4!=NULL)
        c4->visible ? printf("%c%c\t",c4->value,c4->suit) : printf("%s\t","[]");
    else
        printf("\t","");
    if(c5!=NULL)
        c5->visible ? printf("%c%c\t",c5->value,c5->suit) : printf("%s\t","[]");
    else
        printf("\t","");
    if(c6!=NULL)
        c6->visible ? printf("%c%c\t",c6->value,c6->suit) : printf("%s\t","[]");
    else
        printf("\t","");
    if(c7!=NULL)
        c7->visible ? printf("%c%c",c7->value,c7->suit) : printf("%s","[]");
    else
        printf("\t","");
    printf("\n","");
    // endregion
}

printLineFaceUp(Card *c1,Card *c2, Card *c3, Card *c4, Card *c5, Card *c6, Card *c7){
    // region printLineFaceUp
    if(c1!=NULL)
        printf("%c%c\t",c1->value,c1->suit);
    else
        printf("\t","");
    if(c2!=NULL)
        printf("%c%c\t",c2->value,c2->suit);
    else
        printf("\t","");
    if(c3!=NULL)
        printf("%c%c\t",c3->value,c3->suit);
    else
        printf("\t","");
    if(c4!=NULL)
        printf("%c%c\t",c4->value,c4->suit);
    else
        printf("\t","");
    if(c5!=NULL)
        printf("%c%c\t",c5->value,c5->suit);
    else
        printf("\t","");
    if(c6!=NULL)
        printf("%c%c\t",c6->value,c6->suit);
    else
        printf("\t","");
    if(c7!=NULL)
        printf("%c%c",c7->value,c7->suit);
    else
        printf("\t","");
    printf("\n","");
    // endregion
}

bool cardsLeft(Board *board){
    if(&board->c1.cards!=NULL || &board->c2.cards!=NULL || &board->c3.cards!=NULL || &board->c4.cards!=NULL
    || &board->c5.cards!=NULL || &board->c6.cards!=NULL || &board->c7.cards!=NULL || &board->f1.cards!=NULL
    || &board->f2.cards!=NULL || &board->f3.cards!=NULL || &board->f4.cards!=NULL){
        return true;
    }
    return false;
}

sw(Board *board, char lastC[], char message[], bool faceUp){
    // region sw
    //Clear the console
    printTop();

    Card *tmpC1 = NULL;Card *tmpC2 = NULL;Card *tmpC3 = NULL;Card *tmpC4 = NULL;
    Card *tmpC5 = NULL;Card *tmpC6 = NULL;Card *tmpC7 = NULL;
    Card *tmpF1 = NULL;Card *tmpF2 = NULL;Card *tmpF3 = NULL;Card *tmpF4 = NULL;

    tmpC1 = &board->c1.cards;tmpC2 = &board->c2.cards;tmpC3 = &board->c3.cards;tmpC4 = &board->c4.cards;
    tmpC5 = &board->c5.cards;tmpC6 = &board->c6.cards;tmpC7 = &board->c7.cards;
    tmpF1 = &board->f1;tmpF2 = &board->f2;tmpF3 = &board->f3;tmpF4 = &board->f4;

    int i = 1;
    while(tmpC1!=NULL || tmpC2!=NULL || tmpC3!=NULL || tmpC4!=NULL || tmpC5!=NULL || tmpC6!=NULL || tmpC7!=NULL){
        if(i==1){
            if(faceUp){
                printFieldLineFaceUp(tmpC1,tmpC2,tmpC3,tmpC4,tmpC5,tmpC6,tmpC7,tmpF1);
            }else{
                printFieldLine(tmpC1,tmpC2,tmpC3,tmpC4,tmpC5,tmpC6,tmpC7,tmpF1);
            }
        }else if(i==3){
            if(faceUp){
                printFieldLineFaceUp(tmpC1,tmpC2,tmpC3,tmpC4,tmpC5,tmpC6,tmpC7,tmpF2);
            }else{
                printFieldLine(tmpC1,tmpC2,tmpC3,tmpC4,tmpC5,tmpC6,tmpC7,tmpF2);
            }
        }else if(i==5){
            if(faceUp){
                printFieldLineFaceUp(tmpC1,tmpC2,tmpC3,tmpC4,tmpC5,tmpC6,tmpC7,tmpF3);
            }else{
                printFieldLine(tmpC1,tmpC2,tmpC3,tmpC4,tmpC5,tmpC6,tmpC7,tmpF3);
            }
        }else if(i==7){
            if(faceUp){
                printFieldLineFaceUp(tmpC1,tmpC2,tmpC3,tmpC4,tmpC5,tmpC6,tmpC7,tmpF4);
            }else{
                printFieldLine(tmpC1,tmpC2,tmpC3,tmpC4,tmpC5,tmpC6,tmpC7,tmpF4);
            }
        }else{
            if(faceUp){
                printLineFaceUp(tmpC1,tmpC2,tmpC3,tmpC4,tmpC5,tmpC6,tmpC7);
            }else{
                printLine(tmpC1,tmpC2,tmpC3,tmpC4,tmpC5,tmpC6,tmpC7);
            }
        }
        i++;
        if(tmpC1!=NULL)
            tmpC1 = tmpC1->next;
        if(tmpC2!=NULL)
            tmpC2 = tmpC2->next;
        if(tmpC3!=NULL)
            tmpC3 = tmpC3->next;
        if(tmpC4!=NULL)
            tmpC4 = tmpC4->next;
        if(tmpC5!=NULL)
            tmpC5 = tmpC5->next;
        if(tmpC6!=NULL)
            tmpC6 = tmpC6->next;
        if(tmpC7!=NULL)
            tmpC7 = tmpC7->next;
    }

    // the 3 bottom lines of the screen
    printf("LAST Command: %s \n", lastC);
    printf("Message: %s \n", message);
    printf("input >  ");

    //printLine(tmpC1.next,tmpC2->next,tmpC3->next,tmpC4->next,tmpC5->next,tmpC6->next,tmpC7->next);
    // endregion
}

Card * unPrepareBoard(Board * board){
    Card * deck = NULL;
    Card * current = NULL;
    deck = &board->c1.cards;
    current = &board->c1.cards;
    while(current->next!=NULL){
        current = current->next;
    }
    current->next = &board->c2.cards;
    current = current->next;
    while(current->next!=NULL){
        current = current->next;
    }
    current->next = &board->c3.cards;
    current = current->next;
    while(current->next!=NULL){
        current = current->next;
    }
    current->next = &board->c4.cards;
    current = current->next;
    while(current->next!=NULL){
        current = current->next;
    }
    current->next = &board->c5.cards;
    current = current->next;
    while(current->next!=NULL){
        current = current->next;
    }
    current->next = &board->c6.cards;
    current = current->next;
    while(current->next!=NULL){
        current = current->next;
    }
    current->next = &board->c7.cards;
    current = current->next;
    return deck;
}

// here we save the cards from the current deck into a txt file
void sd(Deck * deck, char * filename){
    FILE * fp;

    char temp[100];


    if(strlen(filename) != 0) // did the user set a filename
    {
        strcpy(temp, filename);

        strcat(temp, ".txt");

        fp = fopen(temp, "w");
    }
    else // there was no filename given by the user
    {
        fp = fopen("cards.txt", "w");
    }

    // int length = getCount(deck);
    Card * current = & deck->cards;

    while(current != NULL)
    {
        fprintf(fp, "%c%c", current->value, current->suit);
        if(current->next != NULL)
        {
            fprintf(fp, "\n");
        }
        current = current->next;
    }

    fclose(fp);
}

void s(Board * board, char * movelist[], char * undoList[], char * commandList[], char * filename){
//    FILE * fp;
//
//    char temp[100];
//
//
//    if(strlen(filename) != 0) // did the user set a filename
//    {
//        strcpy(temp, filename);
//
//        strcat(temp, ".txt");
//
//        fp = fopen(temp, "w");
//    }
//    else // there was no filename given by the user
//    {
//        fp = fopen("cards.txt", "w");
//    }
//
//    // int length = getCount(deck);
//    // Card * current = & deck->cards;
//
//    while(current != NULL)
//    {
//        fprintf(fp, "%c%c", current->value, current->suit);
//        if(current->next != NULL)
//        {
//            fprintf(fp, "\n");
//        }
//        current = current->next;
//    }
//
//    fclose(fp);
}

bool checkCardToField(Board * board, char cardFrom[], char fieldTo[]);
// this is the master yoda function
Card * getLastCardFromColumn(Board *pBoard, int column);

Card * getLastCardFromColumn(Board *pBoard, int column) {
    if(column==1){
        Card *card = &pBoard->c1.cards;
        while(card!=NULL){
            if(card->next==NULL){
                break;
            }
            card = card->next;
        }
        return card;
    }else if(column==2){
        Card *card = &pBoard->c2.cards;
        while(card!=NULL){
            if(card->next==NULL){
                break;
            }
            card = card->next;
        }
        return card;
    }else if(column==3){
        Card *card = &pBoard->c3.cards;
        while(card!=NULL){
            if(card->next==NULL){
                break;
            }
            card = card->next;
        }
        return card;
    }else if(column==4){
        Card *card = &pBoard->c4.cards;
        while(card!=NULL){
            if(card->next==NULL){
                break;
            }
            card = card->next;
        }
        return card;
    }else if(column==5){
        Card *card = &pBoard->c5.cards;
        while(card!=NULL){
            if(card->next==NULL){
                break;
            }
            card = card->next;
        }
        return card;
    }else if(column==6){
        Card *card = &pBoard->c6.cards;
        while(card!=NULL){
            if(card->next==NULL){
                break;
            }
            card = card->next;
        }
        return card;
    }else if(column==7){
        Card *card = &pBoard->c7.cards;
        while(card!=NULL){
            if(card->next==NULL){
                break;
            }
            card = card->next;
        }
        return card;
    }
}

Card * getSecondLastCardFromColumn(Board *pBoard, int column);

Card * getSecondLastCardFromColumn(Board *pBoard, int column) {
    if(column==1){
        Card *card = &pBoard->c1.cards;
        while(card!=NULL){
            if(card->next==NULL || card->next->next==NULL){
                break;
            }
            card = card->next;
        }
        return card;
    }else if(column==2){
        Card *card = &pBoard->c2.cards;
        while(card!=NULL){
            if(card->next->next==NULL){
                break;
            }
            card = card->next;
        }
        return card;
    }else if(column==3){
        Card *card = &pBoard->c3.cards;
        while(card!=NULL){
            if(card->next->next==NULL){
                break;
            }
            card = card->next;
        }
        return card;
    }else if(column==4){
        Card *card = &pBoard->c4.cards;
        while(card!=NULL){
            if(card->next->next==NULL){
                break;
            }
            card = card->next;
        }
        return card;
    }else if(column==5){
        Card *card = &pBoard->c5.cards;
        while(card!=NULL){
            if(card->next->next==NULL){
                break;
            }
            card = card->next;
        }
        return card;
    }else if(column==6){
        Card *card = &pBoard->c6.cards;
        while(card!=NULL){
            if(card->next->next==NULL){
                break;
            }
            card = card->next;
        }
        return card;
    }else if(column==7){
        Card *card = &pBoard->c7.cards;
        while(card!=NULL){
            if(card->next->next==NULL){
                break;
            }
            card = card->next;
        }
        return card;
    }
}

void moveCardToField(Card * card,Card * previousCard,Board * board,char fieldTo);

void moveCardToField(Card * card,Card * previousCard,Board * board,char fieldTo){
   if(fieldTo=='1'){
       previousCard->next=NULL;
       //Last card is always visible
       previousCard->visible=true;

       //Move card
       if(board->f1.cards.value==NULL){ //if card is an empty dummy card
           board->f1.cards = *card;
       }else{
           //Reverse linked list for the fields
           Card tmp = board->f1.cards;
           board->f1.cards = *card;
           board->f1.cards.next = &tmp;
       }
   } else if(fieldTo=='2'){
       previousCard->next=NULL;
       //Last card is always visible
       previousCard->visible=true;

       //Move card
       if(board->f2.cards.value==NULL){ //if card is an empty dummy card
           board->f2.cards = *card;
       }else{
           //Reverse linked list for the fields
           Card tmp = board->f2.cards;
           board->f2.cards = *card;
           board->f2.cards.next = &tmp;
       }
   }else if(fieldTo=='3'){
       previousCard->next=NULL;
       //Last card is always visible
       previousCard->visible=true;

       //Move card
       if(board->f3.cards.value==NULL){ //if card is an empty dummy card
           board->f3.cards = *card;
       }else{
           //Reverse linked list for the fields
           Card tmp = board->f3.cards;
           board->f3.cards = *card;
           board->f3.cards.next = &tmp;
       }
   }else if(fieldTo=='4'){
       previousCard->next=NULL;
       //Last card is always visible
       previousCard->visible=true;

       //Move card
       if(board->f4.cards.value==NULL){ //if card is an empty dummy card
           board->f4.cards = *card;
       }else{
           //Reverse linked list for the fields
           Card tmp = board->f4.cards;
           board->f4.cards = *card;
           board->f4.cards.next = &tmp;
       }
   }
}

bool checkIfCardFitOnCard(Card * cardFrom, Card * cardTo);

void moveCardToColumn(Card * lastCardFrom,Card * secondLastCardFrom,Card * lastCardTo, char columnFrom, Board * board);

void moveCardToColumn(Card * lastCardFrom,Card * secondLastCardFrom,Card * lastCardTo, char columnFrom, Board * board){
    secondLastCardFrom->next=NULL;
    secondLastCardFrom->visible=true;
    lastCardTo->next=lastCardFrom;
    Card * tmpCard;
    Column * col;
    if(columnFrom=='1'){
        tmpCard=&board->c1.cards;
        col = &board->c1;
    }else if(columnFrom=='2'){
        tmpCard=&board->c2.cards;
        col = &board->c2;
    }else if(columnFrom=='3'){
        tmpCard=&board->c3.cards;
        col = &board->c3;
    }else if(columnFrom=='4'){
        tmpCard=&board->c4.cards;
        col = &board->c4;
    }else if(columnFrom=='5'){
        tmpCard=&board->c5.cards;
        col = &board->c5;
    }else if(columnFrom=='6'){
        tmpCard=&board->c6.cards;
        col = &board->c6;
    }else if(columnFrom=='7'){
        tmpCard=&board->c7.cards;
        col = &board->c7;
    }
    //Only one card in column
    if(tmpCard->next==NULL){
        //We have to take a copy of the card because we are wiping it from existence
        lastCardTo->next= CreateCard(tmpCard->value,tmpCard->suit,tmpCard->visible);
        Column emptyCol = { NULL, NULL, NULL };
        *col=emptyCol;
    }
}

isValidMove(char move[6], Board * board){
    char * from = strtok(move, "->");
    char * to = strtok(NULL, "->");

    char * columnFrom = strtok(from, ":");
    char * cardFrom = strtok(NULL, ":");
    if(strstr(columnFrom,"C")==NULL){
        cardFrom = columnFrom;
        columnFrom = NULL;
    }

    char * fieldFrom = NULL;
    if(cardFrom!=NULL && strstr(cardFrom,"F")!=NULL){
        fieldFrom = cardFrom;
        cardFrom = NULL;
    }

    char * columnTo = strtok(to, ":");
    char * cardTo = strtok(NULL, ":");
    if(strstr(columnTo,"C")==NULL){
        cardTo = columnTo;
        columnTo = NULL;
    }

    char * fieldTo = NULL;
    if(cardTo!=NULL && strstr(cardTo,"F")!=NULL){
        fieldTo = cardTo;
        cardTo = NULL;
    }

    if(fieldTo!=NULL && fieldFrom==NULL){
        if(cardFrom!=NULL && columnFrom!=NULL){
            //column card to field i.e. C1:AS->F1
            //TODO check if Card can fit in F1
            int column = (int)columnFrom[1]-48;
            if(column==1 || column==2 || column==3 || column==4 || column==5 || column==6 || column==7){
                //check if card is the last card
                Card *lastCard = getLastCardFromColumn(board, column);
                if(cardFrom[0]!=lastCard->value || cardFrom[1]!=lastCard->suit){
                    return false;
                }
                if(checkCardToField(board,cardFrom,fieldTo)){
                    Card *secondLastCard = getSecondLastCardFromColumn(board, column);

                    moveCardToField(lastCard,secondLastCard,board,fieldTo[1]);

                    return true;
                }else{
                    return false;
                }
            }
        }else if(cardFrom==NULL && columnFrom!=NULL){
            //column to field i.e. C1->F1
            int column = (int)columnFrom[1]-48;
            if(column==1 || column==2 || column==3 || column==4 || column==5 || column==6 || column==7){
                Card *lastCard = getLastCardFromColumn(board, column);
                char p[2]={lastCard->value,lastCard->suit};
                if(checkCardToField(board, p,fieldTo)){
                    Card *secondLastCard = getSecondLastCardFromColumn(board, column);

                    moveCardToField(lastCard,secondLastCard,board,fieldTo[1]);
                    return true;
                }
            }
        }
    }else if(fieldFrom!=NULL && fieldTo==NULL){
        if(cardTo!=NULL && columnTo!=NULL){
            //field to column card i.e. F1->C1:AS

        }else if(cardTo==NULL && columnTo!=NULL){
            //field to column i.e. F1->C1

        }
    }else if(fieldFrom!=NULL && fieldTo!=NULL){
        //Field to Field i.e. F1->F2

    }else if(fieldFrom==NULL && fieldTo==NULL){
        if(cardFrom==NULL && columnFrom!=NULL){
            if(cardTo!=NULL && columnTo!=NULL){
                //column to column-card i.e. C1->C2:JH
                int column = (int)columnTo[1]-48;
                if(column==1 || column==2 || column==3 || column==4 || column==5 || column==6 || column==7){
                    Card *lastCardTo = getLastCardFromColumn(board, column);
                    //Check if cardTo is the last Card as you cannot move a card to the middle of a column
                    if((char)cardTo[0]==lastCardTo->value && (char)cardTo[1]==lastCardTo->suit){
                        column = (int)columnFrom[1]-48;
                        if(column==1 || column==2 || column==3 || column==4 || column==5 || column==6 || column==7){
                            Card *lastCardFrom = getLastCardFromColumn(board, column);
                            Card *secondLastCardFrom = getSecondLastCardFromColumn(board, column);
                            if(checkIfCardFitOnCard(lastCardFrom,lastCardTo)){
                                moveCardToColumn(lastCardFrom,secondLastCardFrom,lastCardTo,columnFrom[1],board);
                                return true;
                            }
                        }
                    }
                }
            }else if(cardTo==NULL && columnTo!=NULL){
                //column to column i.e. C1->C2

            }
        }else if(cardFrom!=NULL && columnFrom!=NULL){
            if(cardTo!=NULL && columnTo!=NULL){
                //column-card to column-card i.e. C1:TH->C2:JS

            }else if(cardTo==NULL && columnTo!=NULL){
                //column-card to column i.e. C1:TH->C2

            }
        }
    }else{
        return false;
    }
    return false;
}

char returnCardValueOneGreater(char value){
    if(value=='A'){
        return '2';
    }else if(value=='2'){
        return '3';
    }else if(value=='3'){
        return '4';
    }else if(value=='4'){
        return '5';
    }else if(value=='5'){
        return '6';
    }else if(value=='6'){
        return '7';
    }else if(value=='7'){
        return '8';
    }else if(value=='8'){
        return '9';
    }else if(value=='9'){
        return 'T';
    }else if(value=='T'){
        return 'J';
    }else if(value=='J'){
        return 'Q';
    }else if(value=='Q'){
        return 'K';
    }else if(value=='K'){
        return 'K';
    }
}

bool checkIfCardFitOnCard(Card * cardFrom, Card * cardTo){
    //c1 is cardFrom and c2 is cardTo
    if(returnCardValueOneGreater(cardFrom->value)==cardTo->value){
        if(cardFrom->suit=='H' || cardFrom->suit=='D'){
            if(cardTo->suit=='S' || cardTo->suit=='C'){
                return true;
            }
        }else if(cardFrom->suit=='S' || cardFrom->suit=='C'){
            if(cardTo->suit=='H' || cardTo->suit=='D'){
                return true;
            }
        }
    }
    return false;
}

bool checkCardToField(Board * board, char cardFrom[], char fieldTo[]){
    //TODO a lot of redundant code maybe fix it one day
    if(((char)fieldTo[1])=='1'){
        //Value = null means no cards on field
        if(board->f1.cards.value==NULL){
            //Check if card is an ace
            if(cardFrom[0]=='A'){
                return true;
            }
        }else{
            //Here it gets difficult first check if suit is the same
            if(board->f1.cards.suit==(char)cardFrom[1]){
                //If suit is the same then check if value is one greater
                if(returnCardValueOneGreater(board->f1.cards.value)==(char)cardFrom[0]){
                    return true;
                }
            }
        }
    }else if(((char)fieldTo[1])=='2'){
        //Value = null means no cards on field
        if(board->f2.cards.value==NULL){
            //Check if card is an ace
            if(cardFrom[0]=='A'){
                return true;
            }
        }else{
            //Here it gets difficult first check if suit is the same
            if(board->f2.cards.suit==(char)cardFrom[1]){
                //If suit is the same then check if value is one greater
                if(returnCardValueOneGreater(board->f2.cards.value)==(char)cardFrom[0]){
                    return true;
                }
            }
        }
    }else if(((char)fieldTo[1])=='3'){
        //Value = null means no cards on field
        if(board->f3.cards.value==NULL){
            //Check if card is an ace
            if(cardFrom[0]=='A'){
                return true;
            }
        }else{
            //Here it gets difficult first check if suit is the same
            if(board->f3.cards.suit==(char)cardFrom[1]){
                //If suit is the same then check if value is one greater
                if(returnCardValueOneGreater(board->f3.cards.value)==(char)cardFrom[0]){
                    return true;
                }
            }
        }
    }else if(((char)fieldTo[1])=='4'){
        //Value = null means no cards on field
        if(board->f4.cards.value==NULL){
            //Check if card is an ace
            if(cardFrom[0]=='A'){
                return true;
            }
        }else{
            //Here it gets difficult first check if suit is the same
            if(board->f4.cards.suit==(char)cardFrom[1]){
                //If suit is the same then check if value is one greater
                if(returnCardValueOneGreater(board->f4.cards.value)==(char)cardFrom[0]){
                    return true;
                }
            }
        }
    }
    return false;
}

void removeLastCardFromColumn(int column, Board * board){
    Card * current = NULL;
    Card * tmp = NULL;
    if(column==1){
        current = &board->c1.cards;
        if(current->next==NULL){
            current=NULL;
        }
        while(current!=NULL){
            if(current->next->next==NULL){
                tmp = current->next;
                current->next=NULL;
            }
            current=current->next;
        }
    }else if(column==2){
        current = &board->c2.cards;
    }else if(column==3){
        current = &board->c3.cards;
    }else if(column==4){
        current = &board->c4.cards;
    }else if(column==5){
        current = &board->c5.cards;
    }else if(column==6){
        current = &board->c6.cards;
    }else if(column==7){
        current = &board->c7.cards;
    }
}

Card * findCard(Board * board, char value, char suit){
    Card * c = &board->c1.cards;
    while(c!=NULL){
        if(strcmp(value,c->value)==0 && strcmp(suit,c->suit)==0){
            return c;
        }
        c = c->next;
    }

    c = &board->c2.cards;
    while(c!=NULL){
        if(strcmp(value,c->value)==0 && strcmp(suit,c->suit)==0){
            return c;
        }
        c = c->next;
    }

    c = &board->c3.cards;
    while(c!=NULL){
        if(strcmp(value,c->value)==0 && strcmp(suit,c->suit)==0){
            return c;
        }
        c = c->next;
    }

    c = &board->c4.cards;
    while(c!=NULL){
        if(strcmp(value,c->value)==0 && strcmp(suit,c->suit)==0){
            return c;
        }
        c = c->next;
    }

    c = &board->c5.cards;
    while(c!=NULL){
        if(strcmp(value,c->value)==0 && strcmp(suit,c->suit)==0){
            return c;
        }
        c = c->next;
    }

    c = &board->c6.cards;
    while(c!=NULL){
        if(strcmp(value,c->value)==0 && strcmp(suit,c->suit)==0){
            return c;
        }
        c = c->next;
    }

    c = &board->c7.cards;
    while(c!=NULL){
        if(strcmp(value,c->value)==0 && strcmp(suit,c->suit)==0){
            return c;
        }
        c = c->next;
    }
}

// this is the master function
void gameLoop()
{
    // start values -----------------------------------------
    bool running = true;

    char message[100]; // the message showed on the screen
    char phase[100]; // the game phase (STARTUP, PLAY, ____)
    strcpy(phase, "STARTUP");

    char moveList[1000][100]; // list of all moves made, so we can undo them
    char undoList[1000][100]; // list of all undo done, we be resat after one new move

    char commandList[1000][100]; // all the commands we have made
    int clIndex = 0; // this will be the index of commandList

    Card *deck = NULL;
    Board *board = NULL;
    deck = ld("cardDeck");

    // sd(deck, "batman");

    // TODO: move these functions around
    board = prepareBoard(deck);
    sw(board, "SW", "OK",false);
    deck = unPrepareBoard(board);
    sr(deck,52);
    board = prepareBoard(deck);
    sw(board, "SW", "OK",false);


    // the endless game loop
    while(running)

    {
        // 00 - print to the screen / render

        // 01 - check if the game is done

        // 02 - ask for command input

        char userInput [100];

        scanf("%100s", &userInput);

        // 03 - validation for input

        // no input
        if(strlen(userInput) == 0)
        {
            continue; // resets the loop
        }

        // simply commands: SW, SR, QQ, P, Q, U, R | SD, SI
        // is the input only 1 to 2 chars?
        if(strlen(userInput) <=2 && strlen(userInput) > 0)
        {
            // 04 - do command, if any
            if(strcmp(userInput, "SW") == 0 && strcmp(phase, "STARTUP") == 0) // #2
            {}
            else if(strcmp(userInput, "SR") == 0 && strcmp(phase, "STARTUP") == 0) // #4
            {}
            else if(strcmp(userInput, "QQ") == 0 && strcmp(phase, "STARTUP") == 0) // #6
            {
                printf("\n");
                printf("the program has stop and will be killed in 3 seconds");
                sleep(3);
                running = false;
                continue;
            }
            else if(strcmp(userInput, "P") == 0 && strcmp(phase, "STARTUP") == 0) // #7
            {
                strcpy(phase, "PLAY");
            }
            else if(strcmp(userInput, "Q") == 0 && strcmp(phase, "PLAY") == 0) // #8
            {
                strcpy(phase, "STARTUP");
            }
            else if(strcmp(userInput, "U") == 0) // #10
            {}
            else if(strcmp(userInput, "R") == 0) // #11
            {}
            else if(strcmp(userInput, "SD") == 0 && strcmp(phase, "STARTUP") == 0) // #5 - if the user does not set a filename, use the default
            {
                sd(deck, "");
            }
            else if(strcmp(userInput, "SI") == 0 && strcmp(phase, "STARTUP") == 0) // #3 - if the user didn't set the second parameter
            {
                sd(deck, "");
            }
            else
            {
                continue; // reset the game loop
            }
        }
        else // hard commands
        {
            // hard commands: LD <filename>, SI <split>, SD <filename>, L <filename>, S <filename>
            // 04 - do command, if any

            if(strcmp(userInput[0], "L") == 0 && strcmp(userInput[1], "D") == 0
            && strcmp(userInput[2], " ") == 0 && strcmp(phase, "STARTUP") == 0) // #1 - LD <filename>
            {}
            else if(strcmp(userInput[0], "S") == 0 && strcmp(userInput[1], "I") == 0
            && strcmp(userInput[2], " ") == 0 && strcmp(phase, "STARTUP") == 0) // #3 - SI <split>
            {}
            else if(strcmp(userInput[0], "S") == 0 && strcmp(userInput[1], "D") == 0
            && strcmp(userInput[2], " ") == 0  && strcmp(phase, "STARTUP") == 0) // #5 - SD <filename>
            {
                //TODO: check if there is a better way to do this
                char * fname = strtok(userInput, " ");
                sd(deck, fname);
            }
            else if(strcmp(userInput[0], "L") == 0 && strcmp(userInput[1], " ") == 0 && strcmp(phase, "STARTUP") == 0) // #13 - L <filename>
            {
                // TODO: read the pdf, to check which state we need to be in
            }
            else if(strcmp(userInput[0], "S") == 0 && strcmp(userInput[1], " ") == 0 && strcmp(phase, "PLAY") == 0) // #12 - S <filename>
            {
                // TODO: read the pdf, to check which state we need to be in
            }

            // <Game Moves> | <from>-><to>  |
            else if(strstr(userInput, "->")) // #9
            {

                //C6:4H->C4
                //C6:4H->F4
                //C6->C4

                //F4->C4
                //C6->F4
                //F4->C6

                //F4->F3

                // validation 1
                // check if suit moved to is black (S,C) if the card moved is (H,D)
                // check if suit moved to is red (H,D) if the card moved is (S,C)

                // validation 2
                // check if the number moved to, is one higher than the card moved

                // validation 3 - could be moved somewhere else
                // check if the column is full | this one deck/column is done !

            }
            else
            {
                continue; // reset the game loop
            }
        }

        // if the code have gotten down to here, we can assume that a command have been run
        // TODO: check if this works
        strcpy(commandList[clIndex], userInput);
        clIndex++;
    }
}

int main() {
    //char stdDeck[52][2];
    //strncpy(stdDeck,standardDeck,104);
    //shuffle(stdDeck,52,2);
    Card *deck = NULL;
    Board *board = NULL;
    deck = ld("cardDeck");
    
    // sd(deck, "batman");

    // board = prepareBoard(deck);
    // sw(board, "SW", "OK");
    board = prepareBoard(deck);
    sw(board, "SW", "OK",false);
    //deck = unPrepareBoard(board);
    //sr(deck,52);
    //board = prepareBoard(deck);
    //sw(board);

    // char testing[100];
    // scanf("%s", testing);
    //printf("Hello, World!\n");
    //gameLoop();
    char tmpArr[] = "C7->F1";

    bool test = isValidMove(tmpArr,board);

    char tmpArr2[] = "C1->C2:9C";

    test = isValidMove(tmpArr2,board);

    sw(board, "SW", "OK",false);


    //char testing[100];
    //scanf("%s", testing);

    // region stuff

    /*Card *card = NULL;
    card = deck;
    while(card!=NULL){
        printf("%c%c\n",card->value,card->suit);
        card = card->next;
    }*/
    //Card *newCard = NULL;

    //newCard = CreateCard('A','S',"C1",NULL,true);

    //printf("Successful add of flight %c",newCard->value);
    /*int count=0;
    for(int i = 0; i<52; i++){
        for(int j = 0; j<2; j++){
            printf("%c",stdDeck[i][j]);
        }
        //printf(" %d", count);
        count++;
        printf("\n");
    }*/

    /*printf("%s\t%s\t%s\t%s\n","value","Column","Field","Visible");


    for(int i = 0; i<52; i++){
        if(i==0){
            printf("%c%c",stdDeck[i][0],stdDeck[i][1]);
            printf("\t%s","C1");
            printf("\t%s","NULL");
            printf("\t%s\n","true");
        }
        if(i>0 && i<7){
            if(i==1){
                printf("%c%c",stdDeck[i][0],stdDeck[i][1]);
                printf("\t%s","C2");
                printf("\t%s","NULL");
                printf("\t%s\n","false");
            }else{
                printf("%c%c",stdDeck[i][0],stdDeck[i][1]);
                printf("\t%s","C2");
                printf("\t%s","NULL");
                printf("\t%s\n","true");
            }
        }
        if(i>6 && i<14){
            if(i<9){
                printf("%c%c",stdDeck[i][0],stdDeck[i][1]);
                printf("\t%s","C3");
                printf("\t%s","NULL");
                printf("\t%s\n","false");
            }else{
                printf("%c%c",stdDeck[i][0],stdDeck[i][1]);
                printf("\t%s","C3");
                printf("\t%s","NULL");
                printf("\t%s\n","true");
            }
        }
        if(i>13 && i<22){
            if(i<17){
                printf("%c%c",stdDeck[i][0],stdDeck[i][1]);
                printf("\t%s","C4");
                printf("\t%s","NULL");
                printf("\t%s\n","false");
            }else{
                printf("%c%c",stdDeck[i][0],stdDeck[i][1]);
                printf("\t%s","C4");
                printf("\t%s","NULL");
                printf("\t%s\n","true");
            }
        }
        if(i>21 && i<31){
            if(i<26){
                printf("%c%c",stdDeck[i][0],stdDeck[i][1]);
                printf("\t%s","C5");
                printf("\t%s","NULL");
                printf("\t%s\n","false");
            }else{
                printf("%c%c",stdDeck[i][0],stdDeck[i][1]);
                printf("\t%s","C5");
                printf("\t%s","NULL");
                printf("\t%s\n","true");
            }
        }
        if(i>30 && i<41){
            if(i<36){
                printf("%c%c",stdDeck[i][0],stdDeck[i][1]);
                printf("\t%s","C6");
                printf("\t%s","NULL");
                printf("\t%s\n","false");
            }else{
                printf("%c%c",stdDeck[i][0],stdDeck[i][1]);
                printf("\t%s","C6");
                printf("\t%s","NULL");
                printf("\t%s\n","true");
            }
        }
        if(i>40 && i<52){
            if(i<47){
                printf("%c%c",stdDeck[i][0],stdDeck[i][1]);
                printf("\t%s","C7");
                printf("\t%s","NULL");
                printf("\t%s\n","false");
            }else{
                printf("%c%c",stdDeck[i][0],stdDeck[i][1]);
                printf("\t%s","C7");
                printf("\t%s","NULL");
                printf("\t%s\n","true");
            }
        }
    }*/


    // endregion


    return 0;
}


