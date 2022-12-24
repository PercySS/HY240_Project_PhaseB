/***************************************************************
 *
 * file: pss.h
 *
 * @Author  Nikolaos Vasilikopoulos (nvasilik@csd.uoc.gr)
 * @Version 20-10-2020
 *
 * @e-mail       hy240-list@csd.uoc.gr
 *
 * @brief   Implementation of the "pss.h" header file for the Public Subscribe System,
 * function definitions
 *
 *
 ***************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "pss.h"
#include "structures/info_tree.h"
#include "structures/subinfo_hashtable.h"
#include "structures/subscription_list.h"

int initialize(struct Group *G, int MG, struct SubInfo **S, int hashTableSize, int universalHashingNumber, int *p, int *m, int *a, int *b)
{
    int i;
    for (i = 0; i < MG; i++)
    {
        G[i].gId = -1;
        G[i].gsub = NULL;
        G[i].groot = NULL;
    }

    for (i = 0; i < hashTableSize; i++)
    {
        S[i] = NULL;
    }

    srand(time(NULL));
    *m = hashTableSize;
    *p = universalHashingNumber;
    *a = rand() % (universalHashingNumber - 1) + 1; /* a ∈ [1, p) */
    *b = rand() % universalHashingNumber;           /* b ∈ [0, p) */

    return EXIT_SUCCESS;
}

int free_all(struct Group **G, int MG, struct SubInfo ***S, int hashTableSize)
{
    int i;
    for (i = 0; i < MG && (*G)[i].gId != -1; i++)
    {
        struct Group *group = &(*G)[i];

        /* Free all Subscriptions */
        struct Subscription *curr = group->gsub;

        while (curr != NULL)
        {
            struct Subscription *temp = curr;
            curr = curr->snext;
            free(temp);
        }
    }

    free(*G);

    /* Free all SubInfos */
    for (i = 0; i < hashTableSize; i++)
    {
        struct SubInfo *curr = (*S)[i];

        while (curr != NULL)
        {
            struct SubInfo *temp = curr;
            curr = curr->snext;
            free(temp);
        }
    }

    free(*S);

    return EXIT_SUCCESS;
}

int Insert_Info(struct Group *G, int MG, int iTM, int iId, int *gids_arr, int size_of_gids_arr)
{
    int i;
    for (i = 0; i < size_of_gids_arr - 1; i++)
    {
        int inserted = 0;
        int gid = gids_arr[i];
        int j;
        for (j = 0; j < MG; j++)
        {
            struct Group *group = &G[j];

            /*  Make new group if it doesn't exist */
            if (group->gId == -1)
            {
                group->gId = gid;
            }

            if (group->gId == gid)
            {
                struct Info *node = (struct Info *) malloc(sizeof(struct Info));
                node->iId = iId;
                node->itm = iTM;
                /*  BONUS */
                node->igp = (int *) malloc(sizeof(int) * MG);

                /* Build the igp array */
                int k;
                for (k = 0; k < MG; k++)
                {
                    node->igp[k] = 0;
                }

                for (k = i; k < size_of_gids_arr - 1; k++)
                {
                    int gid = gids_arr[k];
                    node->igp[gid] = 1;
                }

                int ret = BST_Insert(&(group->groot), node);

                if (ret == EXIT_FAILURE)
                {
                    free(node);
                    return EXIT_FAILURE;
                }
                else
                {
                    inserted = 1;
                    break;
                }
            }
        }

        if (inserted == 0)
        {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

int Subscriber_Registration(struct Group *G, int MG, HashTable HT, int sTM, int sId, int *gids_arr, int size_of_gids_arr)
{
    /* Update the Subscriber's list inside the Groups */
    int i;
    for (i = 0; i < size_of_gids_arr - 1; i++)
    {
        int inserted = 0;
        int gid = gids_arr[i];
        int j;
        for (j = 0; j < MG; j++)
        {
            /* Make new group if it doesn't exist */
            if (G[j].gId == -1)
            {
                G[j].gId = gid;
            }

            if (G[j].gId == gid)
            {
                int ret = L_Insert(&(G[j].gsub), sId);

                if (ret == EXIT_FAILURE)
                {
                    return EXIT_FAILURE;
                }
                else
                {
                    inserted = 1;
                    break;
                }
            }
        }

        if (inserted == 0) return EXIT_FAILURE;
    }

    /*  Make the new SubInfo node */
    struct SubInfo *node = (struct SubInfo *) malloc(sizeof(struct SubInfo));
    node->sId = sId;
    node->stm = sTM;
    /* BONUS */
    node->sgp = (struct Info **) malloc(sizeof(struct Info *) * MG);

    /* For each Group */
    for (i = 0; i < MG; i++)
    {
        /*  For each Group that the subscriber is interested in */
        int interested = 0, j;
        for (j = 0; j < size_of_gids_arr - 1; j++)
        {
            if (gids_arr[j] == G[i].gId)
            {
                interested = 1;
                break;
            }
        }

        node->sgp[i] = interested ? NULL : (struct Info *) 1;
    }

    return HT_Insert(HT, node);
}

int Consume(struct SubInfo *subscriber, struct Group *G, int MG, int sId)
{
    int i;
    for (i = 0; i < MG; i++)
    {
        struct Group group = G[i];
        struct Info *lastInfo = subscriber->sgp[i];
        struct Info *cur = NULL;

        /*  Not interested in this group */
        if (lastInfo == (struct Info *) 1) continue;

        struct Info *curr = lastInfo;

        if (curr == NULL) curr = BST_First(group.groot);

        while (BST_Next(curr) != NULL)
        {
            curr = BST_Next(curr);
        }

        subscriber->sgp[i] = curr;
    }

    return EXIT_SUCCESS;
}

int Delete_Subscriber(struct Group *G, int MG, struct SubInfo **S, int sId)
{
    int ret = HT_Delete(S, sId);

    if (ret == EXIT_FAILURE) return EXIT_FAILURE;

    int i;
    for (i = 0; i < MG && G[i].gId != -1; i++)
    {
        L_Delete(&(G[i].gsub), sId);
    }

    return EXIT_SUCCESS;
}

int Print_all(struct Group *G, struct SubInfo **S)
{
    return EXIT_SUCCESS;
}
