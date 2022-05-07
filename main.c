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
        strcat(filenameTmp,"../");strcat(filenameTmp, filename);
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

sw(Board *board, char lastC[], char message[]){
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
            printFieldLineFaceUp(tmpC1,tmpC2,tmpC3,tmpC4,tmpC5,tmpC6,tmpC7,tmpF1);
        }else if(i==3){
            printFieldLineFaceUp(tmpC1,tmpC2,tmpC3,tmpC4,tmpC5,tmpC6,tmpC7,tmpF2);
        }else if(i==5){
            printFieldLineFaceUp(tmpC1,tmpC2,tmpC3,tmpC4,tmpC5,tmpC6,tmpC7,tmpF3);
        }else if(i==7){
            printFieldLineFaceUp(tmpC1,tmpC2,tmpC3,tmpC4,tmpC5,tmpC6,tmpC7,tmpF4);
        }else{
            printLineFaceUp(tmpC1,tmpC2,tmpC3,tmpC4,tmpC5,tmpC6,tmpC7);
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

// this is the master function
void gameLoop()
{
    // start values -----------------------------------------
    char message[100]; // the message showed on the screen
    char phase[100]; // the game phase (STARTUP, PLAY, ____)

    char commandList[5000][100]; // all the commands we have made
    int clIndex = 0; // this will be the index of commandList

    Card *deck = NULL;
    Board *board = NULL;
    deck = ld("cardDeck");

    sd(deck, "batman");

    // TODO: move these functions around
    board = prepareBoard(deck);
    sw(board, "SW", "OK");
    deck = unPrepareBoard(board);
    sr(deck,52);
    board = prepareBoard(deck);
    sw(board, "SW", "OK");


    // the endless game loop
    while(true)

    {
        // 00 - print to the screen / render

        // 01 - check if the game is done

        // 02 - ask for command input

        char userInput [100];

        printf("input: ");
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
            {}
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
            else if(strcmp(userInput[0], "L") == 0 && strcmp(userInput[1], " ") == 0) // #13 - L <filename>
            {}
            else if(strcmp(userInput[0], "S") == 0 && strcmp(userInput[1], " ") == 0) // #12 - S <filename>
            {}

            // <Game Moves> | <from>-><to>  |
            else if(strstr(userInput, "->")) // #9
            {
                //C6:4H->C4:5C
                //C6:4H->C4
                //C6:4H->F4
                //C6->C4:5C
                //F4->C4:5C

                //C6->C4

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

    board = prepareBoard(deck);
    sw(board, "SW", "OK");
    //deck = unPrepareBoard(board);
    //sr(deck,52);
    //board = prepareBoard(deck);
    //sw(board);

    char testing[100];
    scanf("%s", testing);

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
    //printf("Hello, World!\n");

    return 0;
}


