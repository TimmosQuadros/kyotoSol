#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
};

Field *createField(Card cards){
    Field *newField;
    newField = (Field *) malloc(sizeof(Field));
    newField->cards = cards;
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
    f1 = createField(*emptyCard);
    f2 = createField(*emptyCard);
    f3 = createField(*emptyCard);
    f4 = createField(*emptyCard);

    board = createBoard(*c1,*c2,*c3,*c4,*c5,*c6,*c7,*f1,*f2,*f3,*f4);
    return board;
}

Card * ld(char filename[]){
    FILE *fp;
    char row[1000];
    char *token;

    fp = fopen(filename,"r");

    Card *newCard = NULL;
    Card *previous_card = NULL;
    Card *linked_list = NULL;
    while (feof(fp) != true)
    {
        fgets(row, 1000, fp);
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
    prepareBoard(linked_list);
    return linked_list;
}

printTop(){
    for (int i = 1; i<8; i++){
        printf("%c%d\t","C",i);
    }
    printf("\n\n");
}

printRight(){
    for (int i = 1; i<4; i++){
        printf("\t\t%s\t%c%d\n\n","[]","F",i);
    }
}

sw(Board board){


    system("cls"); //Clear the console
    printTop();



    for(int i = 0; i<3; i++){

        for(int j = 0; j<8; j++){

        }
    }
}


int main() {
    char stdDeck[52][2];
    strncpy(stdDeck,standardDeck,104);
    //shuffle(stdDeck,52,2);
    Card *deck = NULL;
    deck = ld("/Users/timmrasmussen/Desktop/cardDeck");

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



    //printf("Hello, World!\n");
    return 0;
}


