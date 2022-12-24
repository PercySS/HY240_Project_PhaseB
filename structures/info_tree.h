#include <stdio.h>
#include <stdlib.h>

#include "../pss.h"

/**
 * @brief Insert a new node in the binary search tree
 *
 * @param tree A pointer to the tree to insert the node in
 * @param node A pointer to the node to insert
 * @return 0 on success
 *         1 on failure
 */
int BST_Insert(struct Info **tree, struct Info *node);

/**
 * @brief Visit each node of the tree, in order
 *
 * @param tree A pointer to the tree to traverse
 * @param func A pointer to the function to call on each node
 */
void BST_Visit(struct Info *tree, void (*func)(struct Info *));

/**
 * @brief Get the node with the smallest value in the tree
 *
 * @param tree A pointer to the tree to traverse
 * @return A pointer to the node with the smallest value
 */
struct Info *BST_First(struct Info *tree);

/**
 * @brief Get the node with the largest value in the tree
 *
 * @param tree A pointer to the tree to traverse
 * @return A pointer to the node with the largest value
 */

struct Info *BST_Last(struct Info *tree);

/**
 * @brief Get the next node in the tree
 * @param curr A pointer to the current node
 * @return A pointer to the next node
 */
struct Info *BST_Next(struct Info *curr);
