#include <stdio.h>
#include <stdlib.h>

#include "../pss.h"

int L_Insert(struct Subscription **GS, int sId)
{
    struct Subscription *node = (struct Subscription *) malloc(sizeof(struct Subscription));
    node->sId = sId;
    node->snext = NULL;

    if (*GS == NULL)
    {
        *GS = node;

        return EXIT_SUCCESS;
    }

    struct Subscription *curr = *GS;

    while (curr->snext != NULL)
    {
        curr = curr->snext;
    }

    curr->snext = node;

    return EXIT_SUCCESS;
}

int L_Delete(struct Subscription **GS, int sId)
{
    struct Subscription *head = *GS;

    if (head == NULL)
    {
        return EXIT_FAILURE;
    }

    if (head->sId == sId)
    {
        *GS = head->snext;
        free(head);

        return EXIT_SUCCESS;
    }

    struct Subscription *curr = head;

    while (curr->snext != NULL && curr->snext->sId != sId)
    {
        curr = curr->snext;
    }

    if (curr->snext == NULL)
    {
        return EXIT_FAILURE;
    }

    struct Subscription *node = curr->snext;
    curr->snext = node->snext;
    free(node);

    return EXIT_SUCCESS;
}

/*struct Subscription *L_LookUp(struct Group *G, int id)
{
    struct Subscription *curr = head;

    while (curr != NULL)
    {
        if (curr->sId == id)
        {
            return curr;
        }

        curr = curr->snext;
    }

    return NULL;
}
*/

void L_Print(struct Group *G)
{
    struct Subscription *curr = G->gsub;

    printf("Subscription List:\n");
    printf("-------------\n");

    while (curr != NULL)
    {
        printf("sId: %d\n", curr->sId);
        curr = curr->snext;
    }

    printf("-------------\n");
}
