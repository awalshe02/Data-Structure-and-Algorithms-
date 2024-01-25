#include "bstdb.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

// Write your submission in this file
//
// A main function and some profiling tools have already been set up to test
// your code in the task2.c file. All you need to do is fill out this file
// with an appropriate Binary Search Tree implementation.
//
// The input data will be books. A book is comprised of a title and a word
// count. You should store both these values in the tree along with a unique
// integer ID which you will generate.
//
// We are aiming for speed here. A BST based database should be orders of
// magnitude faster than a linked list implementation if the BST is written
// correctly.
//
// We have provided an example implementation of what a linked list based
// solution to this problem might look like in the db/listdb.c file. If you
// are struggling to understand the problem or what one of the functions
// below ought to do, consider looking at that file to see if it helps your
// understanding.
//
// There are 6 functions you need to look at. Each is provided with a comment
// which explains how it should behave. The functions are:
//
//  + bstdb_init
//  + bstdb_add
//  + bstdb_get_word_count
//  + bstdb_get_name
//  + bstdb_stat
//  + bstdb_quit
//
// Do not rename these functions or change their arguments/return types.
// Otherwise the profiler will not be able to find them. If you think you
// need more functionality than what is provided by these 6 functions, you
// may write additional functions in this file.


typedef struct books books;
struct books
{
	int id, wcount, height; // elements
	char *name;
	char *author;
	books *left;
	books *right;
};

// global variables
books *root;
int  i;


books *get_book(char *name, char *author, int wcount, unsigned int ID)
{
	books *tmp = (books *)malloc(sizeof(books)); // allocating memory
	tmp->id = ID;								 // putting fields in correct elements
	tmp->name = name;
	tmp->author = author;
	tmp->wcount = wcount;
	tmp->height = 1;
	tmp->left = NULL; // setting to null as bottom of tree
	tmp->right = NULL;
	return tmp; // returning struct
}

int bstdb_init(void)
{
	if (1)
	{ // setting all global varibales to 0
		i = 0;
		root = NULL;
		return 1;
	}
	else
		return 0;
	// This function will run once (and only once) when the database first
	// starts. Use it to allocate any memory you want to use or initialize
	// some globals if you need to. Function should return 1 if initialization
	// was successful and 0 if something went wrong.
}

unsigned int get_id(char *s) // using hash table
{
	if (s == NULL || *s == '\0')
	{
		return i++;
	}
	unsigned long hash = 5381;
	int c;

	while ((c = *s++))
	{
		hash = ((hash << 5) + hash) + c; // hash * 33 + c
	}
	return hash;
}

int max_num(int a, int b) // finding the biggest number
{
	if (a > b) // if a  or equal then b
	{
		return a;
	}
	else if (a < b) // if b greater than a
	{
		return b;
	}
	else
	{ // if a and b are the same
		return a;
	}
}

int find_height(books *root)
{
	if (root == NULL) // no tree so no levels
	{
		return 0;
	}

	int max = max_num(find_height(root->left), find_height(root->right)); // finds the greatest level height of left and right sub trees

	return 1 + max; // returns greatest height plus 1
}

books *rotate_right(books *root)
{
	books *tmp = root->left;
	books *book2 = tmp->right;

	// doing rotation
	tmp->right = root;
	root->left = book2;

	// update heights
	tmp->height = find_height(tmp);
	root->height = find_height(root);
	return tmp;
}

books *rotate_left(books *root)
{
	books *tmp = root->right;
	books *book2 = tmp->left;

	// doing rotation
	tmp->left = root;
	root->right = book2;

	// updating height;
	tmp->height = find_height(tmp);
	root->height = find_height(root);

	return tmp;
}

int balancing(books *root) // this function retruns 1 if balanced and 0 otherwise
{

	if (root == NULL) // returns 0 if empty
	{
		return 0;
	}

	return find_height(root->left) - find_height(root->right);
}

int bstdb_add(char *name, int word_count, char *author)
{
	unsigned int ID = get_id(author);
	if (root == NULL) // starting the tree
	{
		root = get_book(name, author, word_count, ID); // making memory for new book
		return root->id;
	}
	else if (root->id < ID) // ID goes to the right if greater than root
	{	
		bstdb_add(root->right->name, root->right->wcount, root->right->author);
	}
	else if (root->id > ID) // ID goes to the left if less than root
	{	
		bstdb_add(root->left->name, root->left->wcount, root->left->author);
	}
	else if (root->id == ID) // ID goes to left if the same and id change as it needs to be unique for each book
	{
		ID = get_id(name); // switch to name instead of author if equal
		bstdb_add(root->left->name, root->left->wcount, root->left->author);
	}

	root->height = find_height(root); // getting heigth of the tree
	int balance = balancing(root);	  // seeing is balanced or not

	// left case
	if (balance > 1 && ID < root->left->id ) // less than 1 and
	{
		books *tmp = rotate_right(root);
		return tmp->id;
	}
	// right case
	if (balance < -1 && ID > root->right->id)
	{ // less than -1
		books *tmp = rotate_left(root);
		return tmp->id;
	}
	// left-right case
	if (balance > 1 && ID > root->left->id)
	{
		root->left = rotate_left(root->left);
		books *tmp = rotate_right(root);
		return tmp->id;
	}
	// right-left case
	if (balance < -1 && ID < root->right->id)
	{
		root->right = rotate_right(root->right);
		books *tmp = rotate_left(root);
		return tmp->id;
	}

	return -1; // if the data cannot be stored
			   // This function should create a new node in the binary search tree,
			   // populate it with the name, word_count and author of the arguments and store
			   // the result in the tree.
			   //
			   // This function should also generate and return an identifier that is
			   // unique to this document. A user can find the stored data by passing
			   // this ID to one of the two search functions below.
			   //
			   // How you generate this ID is up to you, but it must be an integer. Note
			   // that this ID should also form the keys of the nodes in your BST, so
			   // try to generate them in a way that will result in a balanced tree.
			   //
			   // If something goes wrong and the data cannot be stored, this function
			   // should return -1. Otherwise it should return the ID of the new node
}

books *search(books *root, int id)
{
	if (root == NULL)
	{
		return NULL;
	}
	else if (root->id == id) // return root if id's the same or the root is null
	{
		return root;
	}
	else if (root->id < id && root->right != NULL) // if greater then root, move right when not null
	{
		return search(root->right, id);
	}
	else if (root->id > id && root->left != NULL) // if less than root, move left when not null
	{
		return search(root->left, id);
	}
	else
	{
		return NULL;
	}
}

int bstdb_get_word_count(int doc_id)
{
	books *tmp = search(root, doc_id); // struct that contains id

	if (tmp != NULL && tmp->id == doc_id ) // if the same
	{
		int wordc = tmp->wcount;
		return wordc; // return word count
	}
	else
	{	
		return -1; // not found
	}
	// This is a search function. It should traverse the binary search tree
	// and return the word_count of the node with the corresponding doc_id.
	//
	// If the required node is not found, this function should return -1
}

char *
bstdb_get_name(int doc_id)
{
	books *tmp = search(root, doc_id); // struct that conatins id

	if (tmp != NULL) // if not null (found)
	{
		char *name = tmp->name;
		return name; // return name of found id
	}
	else
	{
		return 0;
	}

	// This is a search function. It should traverse the binary search tree
	// and return the name of the node with the corresponding doc_id.
	//
	// If the required node is not found, this function should return NULL or 0
}

int get_level(books *root, int id, int level)
{
	if (root == NULL) // empty so no levels
	{
		return 0;
	}

	if (root->id == id) // return level if id matches root id
	{
		return level;
	}
	// when id does not match root id
	int down = get_level(root->left, id, level + 1); // try level+1 to the left

	if (down != 0) // if not zero then level has been found
	{
		return down; // returning level
	}
	down = get_level(root->right, id, level + 1); // try level+1 to the right

	if (down != 0) // if not zero then level has been found
	{
		return down; // returning level
	}
	else
	{
		return -1; // if no level found
	}
}

int Level(books *root, int id)
{
	return get_level(root, id, 1); // gets level of id
}

void bstdb_stat(void)
{
	// seeing if the tree is height balanced
	if (balancing(root) > 1)
	{
		printf("This tree is not height balanced\n");
	}
	else if(balancing(root) < -1)
	{
		printf("This tree is not height balanced\n");
	}
	else{
		printf("This tree is height balanced\n");
	}

	// calculating what level an id is found at
	int id_num = get_id(root->author);
	if (Level(root, id_num) == -1)
	{
		printf("\nId not found at any level\n");
	}
	else
	{
		printf("The id %d can be found at level %d \n", id_num, Level(root, id_num));
	}

	// Use this function to show off! It will be called once after the
	// profiler ends. The profiler checks for execution time and simple errors,
	// but you should use this function to demonstrate your own innovation.
	//
	// Suggestions for things you might want to demonstrate are given below,
	// but in general what you choose to show here is up to you. This function
	// counts for marks so make sure it does something interesting or useful.
	//
	//  + Check if your tree is balanced and print the result
	//
	//  + Does the number of nodes in the tree match the number you expect
	//    based on the number of insertions you performed?
	//
	//  + How many nodes on average did you need to traverse in order to find
	//    a search result?
	//
	//  + Can you prove that there are no accidental duplicate document IDs
	//    in the tree?
}

void delete(books *root)
{
	if (root == NULL) // root is empty so at end
	{
		return;
	}
	else
	{
		delete (root->left);  // go left
		delete (root->right); // go right
		free(root);			  // free memory
	}
}

void bstdb_quit(void)
{
	delete (root); // calls delete function
				   // This function will run once (and only once) when the program ends. Use
				   // it to free any memory you allocated in the course of operating the
				   // database.
}
