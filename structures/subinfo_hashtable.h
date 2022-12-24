#include <stdio.h>
#include <stdlib.h>

#include "../pss.h"

/**
 * @brief Insert SubInfo into the hash table
 *
 * @param S The hash table
 * @param node The SubInfo node to be inserted
 * @param hashing_function A pointer to the hashing function
 * @param hashTableSize The size of the hash table
 * @return 0 on success
 *         1 on failure
 */
int HT_Insert(struct SubInfo **S, struct SubInfo *node);

/**
 * @brief Delete SubInfo from the hash table
 *
 * @param S The hash table
 * @param sId Identifier of the subscriber
 * @param hashing_function A pointer to the hashing function
 * @param hashTableSize The size of the hash table
 * @return 0 on success
 *         1 on failure
 */
int HT_Delete(struct SubInfo **S, int sId);

/**
 * @brief Look up a subscriber in the hash table
 *
 * @param S The hash table
 * @param sId Identifier of the subscriber
 * @param hashing_function A pointer to the hashing function
 * @param hashTableSize The size of the hash table
 * @return A pointer to the SubInfo node
 */
struct SubInfo *HT_LookUp(struct SubInfo **S, int sId);

/**
 * @brief Insert SubInfo into the subscribers' list
 *
 * @param S A pointer to the list of subscribers
 * @param node The node to be inserted
 * @param sTM Timestamp of subscription
 * @return 0 on success
 *         1 on failure
 */
int SL_Insert(struct SubInfo **S, struct SubInfo *node);

/** @brief Delete SubInfo from the subscribers' list
 *
 * @param S A pointer to the list of subscribers
 * @param sId Identifier of subscriber
 * @return 0 on success
 *         1 on failure
 */
int SL_Delete(struct SubInfo **S, int sId);

struct SubInfo *SL_LookUp(struct SubInfo *head, int id);

void SL_Print(struct SubInfo *head);
