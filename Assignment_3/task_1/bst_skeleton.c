#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

void tree_insert(Tree_Node **root, char data)
{
    if (*root == NULL)
    {
        Tree_Node *tmp = (Tree_Node *)malloc(sizeof(Tree_Node)); // allocating memory
        tmp->data = data;                                        // putting fields in correct elements
        tmp->left = NULL;                                        // setting to null as at the bottom of the tree
        tmp->right = NULL;
        *root = tmp;
        return;
    }
    else if ((*root)->data > data) // if data is less than the root
    {
        tree_insert(&(*root)->left, data); // go left
    }
    else if ((*root)->data < data) // if data is greater than the root
    {
        tree_insert(&(*root)->right, data); // go right
    }
    else if ((*root)->data == data) // if the data and root are the same
    {
        tree_insert(&(*root)->left, data); // go left
    }
}

Tree_Node *create_bst(char data[])
{
    Tree_Node *root = NULL;
    for (int i = 0; data[i] != '\0'; i++) // continue through array until it reaches the null terminator '\0'
    {
        tree_insert(&root, data[i]); // inserting into the tree
    }
    return root;
}

Tree_Node *tree_search(Tree_Node *root, char data)
{
    if (root == NULL || root->data == data) // if root is null or data is the same as the root
    {
        return root;
    }
    else if (root->data < data) // if data is greater than the root
    {
        return tree_search(root->right, data); // searching to the right
    }
    else
    {
        return tree_search(root->left, data); // searches to the left otherwise
    }
}

void tree_print_sorted(Tree_Node *root)
{
    if (root == NULL) // if no root do nothing
    {
        return;
    }
    else
    {
        tree_print_sorted(root->left); //print nodes from smallest to biggest
        printf("%c", root->data);
        tree_print_sorted(root->right);
    }
}

void tree_delete(Tree_Node *root)
{
    if (root == NULL) //do nothing if empty
    {
        return;
    }
    tree_delete(root->left); //freeing (deleting) memory starting from smallest to largest
    tree_delete(root->right);
    free(root);
}
