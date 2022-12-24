/***************************************************************
 *
 * file: pss.h
 *
 * @Author  Nikolaos Vasilikopoulos (nvasilik@csd.uoc.gr)
 * @Version 20-10-2020
 *
 * @e-mail       hy240-list@csd.uoc.gr
 *
 * @brief   Header file for the Public Subscribe System,
 * with the structures and function prototypes
 *
 ***************************************************************
 */

#ifndef pss_h
#define pss_h

struct Info {
    int iId;
    int itm;
    int *igp;
    struct Info *ip;  /*  parent */
    struct Info *ilc; /*  left child */
    struct Info *irc; /* right child */
};

struct Subscription {
    int sId;
    struct Subscription *snext;
};

struct Group {
    int gId;
    struct Subscription *gsub;
    struct Info *groot;
};

struct SubInfo {
    int sId;
    int stm;
    struct Info **sgp;
    struct SubInfo *snext;
};

typedef struct SubInfo **HashTable;

/**
 * @brief Optional function to initialize data structures that
 *        need initialization
 *
 * @param G The array of groups
 * @param MG The size of the array of groups
 * @param S The list of subscriptions
 * @param hashTableSize The size of the hash table
 * @param universalHashingNumber The number of the universal hashing function
 * @return 0 on success
 *         1 on failure
 */
int initialize(struct Group *G, int MG, struct SubInfo **S, int hashTableSize, int universalHashingNumber, int *p, int *m, int *a, int *b);

/**
 * @brief Free resources
 *
 * @param G A pointer to the table of groups
 * @param MG The size of the array of groups
 * @param S An pointer to the subscribers' hashtable
 * @param hashTableSize The size of the hash table
 * @return 0 on success
 *         1 on failure
 */
int free_all(struct Group **G, int MG, struct SubInfo ***S, int hashTableSize);

/**
 * @brief Insert info
 *
 * @param G The array of groups
 * @param MG The max size of the array of groups
 * @param iTM Timestamp of arrival
 * @param iId Identifier of information
 * @param gids_arr Pointer to array containing the gids of the Event.
 * @param size_of_gids_arr Size of gids_arr including -1
 * @return 0 on success
 *         1 on failure
 */
int Insert_Info(struct Group *G, int MG, int iTM, int iId, int *gids_arr, int size_of_gids_arr);

/**
 * @brief Subsriber Registration
 *
 * @param G The array of groups
 * @param MG The max size of the array of groups
 * @param S The list of subscriptions
 * @param sTM Timestamp of subscription
 * @param sId Identifier of subscriber
 * @param gids_arr Pointer to array containing the gids of the Event.
 * @param size_of_gids_arr Size of gids_arr including -1
 * @return 0 on success
 *         1 on failure
 */
int Subscriber_Registration(struct Group *G, int MG, HashTable HT, int sTM, int sId, int *gids_arr, int size_of_gids_arr);

/**
 * @brief Consume Information for subscriber
 *
 * @param subscriber The subscriber object
 * @param G The array of groups
 * @param MG The max size of the array of groups
 * @param sId Subscriber identifier
 * @return 0 on success
 *         1 on failure
 */
int Consume(struct SubInfo *subscriber, struct Group *G, int MG, int sId);

/**
 * @brief Delete subscriber
 *
 * @param G The array of groups
 * @param MG The max size of the array of groups
 * @param S A pointer to the list of subscriptions
 * @param sId Subscriber identifier
 * @return 0 on success
 *         1 on failure
 */
int Delete_Subscriber(struct Group *G, int MG, struct SubInfo **S, int sId);

/**
 * @brief Print Data Structures of the system
 *
 * @param G Group array
 * @param S A pointer to the subscribers' hashtable
 * @return 0 on success
 *         1 on failure
 */
int Print_all(struct Group *G, struct SubInfo **S);

#endif /* pss_h */
