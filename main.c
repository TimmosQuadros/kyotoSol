#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Structure definition
typedef struct card Card;
struct card{
    char value;
    char suit;
    char column[3];
    char field[3];
    bool visible;
    Card *next; //linked list
};

Card *CreateCard(char val, char sui, char * col, char * fie, bool vis){
    Card *newCard;

    newCard = (Card *) malloc(sizeof(Card));
    newCard->value = val;
    newCard->suit = sui;
    if(col!=NULL){
        strcpy(newCard->column,col);
    }
    if(fie!=NULL){
        strcpy(newCard->field,fie);
    }
    newCard->visible = vis;
}

typedef struct deck Deck;
struct deck{
    Card cards;
};

typedef struct column Column;
struct column{
    Card cards;
};

typedef struct field Field;
struct field{
    Card cards;
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



int main() {
    char stdDeck[52][2];
    strncpy(stdDeck,standardDeck,104);

    Card *newCard = NULL;

    newCard = CreateCard('A','S',"C1",NULL,true);

    printf("Successful add of flight %c",newCard->value);

    /*for(int i = 0; i<52; i++){
        for(int j = 0; j<2; j++){
            printf("%c ",stdDeck[i][j]);
        }
        printf("\n");
    }*/

    //printf("Hello, World!\n");
    return 0;
}
