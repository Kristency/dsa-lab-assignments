#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "dlist.h"

struct chair *pointAtChair0;

void initDList()
{
    if (isEmpty())
    {
        return;
    }
    if (pointAtChair0->rightChair != NULL)
    {
        struct chair *cur = pointAtChair0->rightChair;
        struct chair *next;
        while (cur != pointAtChair0)
        {
            next = cur->rightChair;
            free(cur->player);
            free(cur);
            cur = next;
        }
    }

    free(pointAtChair0->player);
    free(pointAtChair0);
    pointAtChair0 = NULL;
}

int isEmpty()
{
    if (pointAtChair0 == NULL)
    {
        return 1;
    }
    return 0;
}

void insertChair(char *player)
{
    if (pointAtChair0 == NULL)
    {
        struct chair *new_chair = (struct chair *)malloc(sizeof(struct chair));
        new_chair->player = player;
        new_chair->leftChair = new_chair->rightChair = new_chair;
        pointAtChair0 = new_chair;
        return;
    }
    struct chair *last_chair = pointAtChair0->leftChair;

    struct chair *new_chair = (struct chair *)malloc(sizeof(struct chair));
    new_chair->player = player;
    new_chair->rightChair = pointAtChair0;
    pointAtChair0->leftChair = new_chair;
    new_chair->leftChair = last_chair;
    last_chair->rightChair = new_chair;
}

char *whoInChair(int displacement)
{
    int i = 0;
    struct chair *cur = pointAtChair0;
    if (displacement < 0)
    {
        displacement = -1 * displacement;
        while (i < displacement)
        {
            cur = cur->leftChair;
            i++;
        }
        return cur->player;
    }
    else
    {
        while (i < displacement)
        {
            cur = cur->rightChair;
            i++;
        }
        return cur->player;
    }
}

void printList()
{
    struct chair *cur = pointAtChair0;
    printf("%s\n", cur->player);
    cur = cur->rightChair;
    while (cur != pointAtChair0)
    {
        printf("%s\n", cur->player);
        cur = cur->rightChair;
    }
}

char *removeChair(int displacement)
{
    // if (isEmpty())
    // {
    //     return;
    // }
    char *name;

    // if only one node
    if (pointAtChair0->leftChair == pointAtChair0 && pointAtChair0->rightChair == pointAtChair0)
    {
        name = pointAtChair0->player;
        pointAtChair0 = NULL;
        free(pointAtChair0);
        return name;
    }

    // if more than one node
    int i = 0;
    struct chair *cur = pointAtChair0;
    struct chair *prev = NULL;
    struct chair *next;
    if (displacement > 0)
    {
        while (i < displacement)
        {
            prev = cur;
            cur = cur->rightChair;
            i++;
        }
    }
    else
    {
        displacement = -1 * displacement;
        while (i < displacement)
        {
            cur = cur->leftChair;
            prev = cur->leftChair;
            i++;
        }
    }
    // printf("\n\n%s %s\n\n", prev->player, cur->player);

    // if node is the first node
    if (cur == pointAtChair0)
    {
        // printf("current player: %s ", cur->player);
        // printf("previous player: %s", prev->player);
        next = cur->rightChair;
        next->leftChair = prev;
        prev->rightChair = next;
        pointAtChair0 = next;
        // printf("%s", pointAtChair0->player);
        name = cur->player;
        free(cur);
        return name;
    }
    // if node is the last node
    if (cur->rightChair == pointAtChair0)
    {
        prev->rightChair = pointAtChair0;
        pointAtChair0->leftChair = prev;
        name = cur->player;
        free(cur);
        return name;
    }

    // if any middle node
    next = cur->rightChair;
    prev->rightChair = next;
    next->leftChair = prev;
    name = cur->player;
    free(cur);
    return name;
}