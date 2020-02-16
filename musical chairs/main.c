#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "dlist.h"
char tmp[101];
int arr[13] = {6, 6, 5, 5, 6, 5, 1, 1, 5, 3, 6, 6, 2};
int j = -1;
int rollDice()
{
    // int i = 1 + rand() % 6;
    // return i;
    j += 1;
    return arr[j];
}
int main(void)
{
    char *name;
    int dice;
    initDList();
    FILE *playerF = fopen("players.txt", "r");
    assert(playerF != NULL); // File is open
    fgets(tmp, 100, playerF);
    while (!feof(playerF))
    {
        // Get space filled with \0
        name = calloc(1, strlen(tmp) + 1);
        // Newline should not copied
        strncpy(name, tmp, strlen(tmp) - 1);
        // printf(name);
        insertChair(name);
        fgets(tmp, 100, playerF);
    }

    printList();
    printf("\nAll players are in their chairs now. Game begins\n\n");

    while (!isEmpty())
    {
        printf("%s is in chair 0. ", whoInChair(0));
        dice = rollDice();
        if (dice % 2 == 1) // Odd numbers on left!
            dice *= -1;
        printf("Rid chair %d. \n\n", dice);
        name = removeChair(dice);
        // printList();
        if (isEmpty())
            printf("\n\nWinner is %s\n", name);
        else
            printf("\nLosing player was %s.\n", name);
        free(name);
    }
    return 0;
}