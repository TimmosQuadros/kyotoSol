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

char standardDeck[52][2] =
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

    

    printf("Hello, World!\n");
    return 0;
}
