#include <stdio.h>
#include <stdlib.h>

#include "../pss.h"

int BST_Insert(struct Info **tree, struct Info *node)
{
    struct Info *root = *tree;

    node->ilc = NULL;
    node->irc = NULL;

    if (root == NULL)
    {
        *tree = node;
        node->ip = NULL;

        return EXIT_SUCCESS;
    }

    if (node->iId < root->iId)
    {
        if (root->ilc == NULL)
        {
            root->ilc = node;
            node->ip = root;

            return EXIT_SUCCESS;
        }
        else
        {
            BST_Insert(&root->ilc, node);
        }
    }
    else if (node->iId > root->iId)
    {
        if (root->irc == NULL)
        {
            root->irc = node;
            node->ip = root;

            return EXIT_SUCCESS;
        }
        else
        {
            BST_Insert(&root->irc, node);
        }
    }
    else
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void BST_Visit(struct Info *tree, void (*func)(struct Info *))
{
    if (tree == NULL)
    {
        return;
    }

    BST_Visit(tree->ilc, func);
    func(tree);
    BST_Visit(tree->irc, func);
}

struct Info *BST_First(struct Info *tree)
{
    if (tree == NULL)
    {
        return NULL;
    }

    struct Info *curr = tree;

    while (curr->ilc != NULL)
    {
        curr = curr->ilc;
    }

    return curr;
}

struct Info *BST_Last(struct Info *tree)
{
    if (tree == NULL)
    {
        return NULL;
    }

    struct Info *curr = tree;

    while (curr->irc != NULL)
    {
        curr = curr->irc;
    }

    return curr;
}

struct Info *BST_Next(struct Info *curr)
{
    struct Info *next = NULL;

    if (curr->irc != NULL)
    {
        next = curr->irc;

        while (next->ilc != NULL)
        {
            next = next->ilc;
        }
    }
    else
    {
        next = curr->ip;

        while (next != NULL && curr == next->irc)
        {
            curr = next;
            next = next->ip;
        }
    }

    return next;
}
