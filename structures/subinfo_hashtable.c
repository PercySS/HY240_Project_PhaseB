#include <stdio.h>
#include <stdlib.h>

#include "../pss.h"
#include "../uhf.h"

int SL_Insert(struct SubInfo **S, struct SubInfo *node)
{
    struct SubInfo *head = *S;

    if (head == NULL || head->sId > node->sId)
    {
        node->snext = head;
        head = node;
        *S = head;

        return EXIT_SUCCESS;
    }

    struct SubInfo *curr = head;

    while (curr->snext != NULL && curr->snext->sId < node->sId)
    {
        curr = curr->snext;
    }

    if (curr->stm == node->stm)
    {
        return EXIT_FAILURE;
    }

    node->snext = curr->snext;
    curr->snext = node;

    return EXIT_SUCCESS;
}

int SL_Delete(struct SubInfo **S, int sId)
{
    struct SubInfo *head = *S;

    if (head == NULL)
    {
        return EXIT_FAILURE;
    }

    if (head->sId == sId)
    {
        *S = head->snext;
        free(head);

        return EXIT_SUCCESS;
    }

    struct SubInfo *curr = head;

    while (curr->snext != NULL && curr->snext->sId != sId)
    {
        curr = curr->snext;
    }

    if (curr->snext == NULL)
    {
        return EXIT_FAILURE;
    }

    struct SubInfo *node = curr->snext;
    curr->snext = node->snext;
    free(node);

    return EXIT_SUCCESS;
}

struct SubInfo *SL_LookUp(struct SubInfo *head, int id)
{
    struct SubInfo *curr = head;

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

void SL_Print(struct SubInfo *head)
{
    struct SubInfo *curr = head;

    printf("SubInfo List:\n");
    printf("-------------\n");

    while (curr != NULL)
    {
        printf("sId: %d, stm: %d\n", curr->sId, curr->stm);
        curr = curr->snext;
    }

    printf("-------------\n");
}

int HT_Insert(HashTable HT, struct SubInfo *node)
{
    int index = Universal_Hashing_Function(node->sId);
    struct SubInfo **plist = &HT[index];

    return SL_Insert(plist, node);

    return EXIT_SUCCESS;
}

int HT_Delete(HashTable HT, int sId)
{
    int index = Universal_Hashing_Function(sId);
    struct SubInfo **plist = &HT[index];

    return SL_Delete(plist, sId);

    return EXIT_SUCCESS;
}

struct SubInfo *HT_LookUp(HashTable HT, int sId)
{
    int index = Universal_Hashing_Function(sId);
    struct SubInfo *list = HT[index];

    return SL_LookUp(list, sId);
}
