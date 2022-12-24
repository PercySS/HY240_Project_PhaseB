#include <stdio.h>
#include <stdlib.h>

#include "../pss.h"

/**
 * @brief Insert Subscription into the subscribers' list
 *
 * @param sId Identifier of subscriber
 * @return 0 on success
 *         1 on failure
 */
int L_Insert(struct Subscription **GS, int sId);

/** @brief Delete Subscription from the subscribers' list
 *
 * @param sId Identifier of subscriber
 * @return 0 on success
 *         1 on failure
 */
int L_Delete(struct Subscription **GS, int sId);

/* struct SubInfo *L_LookUp(struct Group *G, int id); */

void L_Print(struct Group *G);
