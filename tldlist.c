/*name		Jason Egan
  matric	2191867e
  assignment	APH Exercise 1
  This is my own work as defined in the Academic Ethics agreement I have signed
*/



#include "tldlist.h"
#include "stdlib.h"
#include "stdio.h"
#include "date.h"
#include "string.h"
#include "math.h"
#include "ctype.h"


/* structs required from the header file */
struct tldlist{
	TLDNode *root;	
	Date *beginDate;
	Date *endDate;
	long size;
	long count;
};


struct tldnode{
	TLDNode *parent, *left, *right;
	char *content;
	long count, height;


};

struct tlditerator{
	long size;
	long next;
	TLDNode **nodeList;


};

/*AVL functions*/


/*function defined to return the max between a & b*/
int max(int a, int b){
	return a>b?a:b;
}


/*returns the height of the given node and 0 if the node is NULL to prevent segmentation faults*/
long getHeight(TLDNode *node){
	if(node == NULL){
		return 0;
	}
	return node->height;

}


/*int method to determine whether the given node is imbalanced*/
static int isImbalanced(TLDNode *node){

	/*again a check is carried out if either node is NULL so there is no seg fault*/
	if((node->right != NULL) && (node->left!=NULL)){

	/*returns 1 if the balance between the nodes is bad or 0 if balanced properly*/
	return abs(node->left->height - node->right->height) > 1? 1:0;
	}
	
}


/*given a node, this function returns a pointer to the unbalanced node when found*/
static TLDNode *findImbalanced(TLDNode *node){
	/*this case is checked again to prevent seg faults*/
	if(node == NULL){
		return NULL;
	/*returns the imbalanced node once it is found*/
	}else if(isImbalanced(node) == 1){
		return node;

	}else{
	/*recurses the method through the parent node*/
	}return findImbalanced(node->parent);

}


/*method to update height of a node*/
static void updateHeight(TLDNode *node){
	/*case is checked to prevent seg faults*/
	if(node == NULL){
		return;
	}
	/*sets the current node height to the max of the left and right subtrees*/
	node->height = max(getHeight(node->left),getHeight(node->right))+1;
	/*recurses method through parent*/
	updateHeight(node->parent);
	

}


/*checks whether an LL rotation is required*/
static int caseLL(TLDNode *node){
	if((node->left->height > node->right->height) && (node->left->left->height > node->left->right->height)){
		return 1;
	}
	return 0;

}

/*checks whether an LR rotation is required*/
static int caseLR(TLDNode *node){
	if((node->left->height > node->right->height) && (node->left->right->height > node->left->left->height)){
		return 1;
	}

	return 0;
}


/*checks whether an RL rotation is required*/
static int caseRL(TLDNode *node){
	if((node->right->height > node->left->height) && (node->right->left->height > node->right->right->height)){
		return 1;
	}

	return 0;
}

/*checks whether an RR rotation is required*/
static int caseRR(TLDNode *node){
	if((node->right->height > node->left->height) && (node->right->right->height > node->right->left->height)){
		return 1;
	}
	return 0;
}


/*function to perform an LL rotation on a given node*/
static void LLRotate(TLDList *tld,TLDNode *node){
	/*initialises nodes that will be used in the function to perform the rotation*/
	TLDNode *root = node;
	TLDNode *leftChild = node->left;
	TLDNode *p = root->parent;
	
	/*rotation*/
	if(p==NULL){
		root = leftChild;
		tld->root = root;
		leftChild->parent = NULL;
	}else if(root->parent->left == root){
		p->left = leftChild;
	}else{
		p->right = leftChild;
	}
	root->left = leftChild->right;
	leftChild->right = root;
	
	/*updates the height through the newly rotated nodes*/
	updateHeight(root);

}

/*function to perform an RR rotation on a given node*/
static void RRRotate(TLDList *tld,TLDNode *node){
	/*initialises nodes that will be used in the function to perform the rotation*/
	TLDNode *root = node;
	TLDNode *rightChild = node->right;
	TLDNode *p = root->parent;
	/*rotation*/
	if(p==NULL){
		root = rightChild;
		tld->root = root;
		rightChild->parent = NULL;
	}else if(root->parent->right == root){
		p->right = rightChild;
	}else{
		p->left = rightChild;
	}
	root->right = rightChild->left;
	rightChild->left = root;
	
	/*updates the height through the newly rotated nodes*/
	updateHeight(root);
}

/*function is created in the case that both an R and L rotation are required and vice versa*/
static void DRotate(TLDList *tld,TLDNode *n1,TLDNode *n2,TLDNode *n3,TLDNode *p, int leftChild){
	/*rotation*/
	if(p==NULL){
		tld->root = n2;
		n2->parent = NULL;
	}else if(leftChild == 1){
		p->left = n2;
	}else{
		p->right = n2;
	}
	n3->left = n2->right;
	n1->right = n2->left;
	n2->left = n1;
	n2->right = n3;
	/*height properties are updated again through the newly rotated nodes n1,n3*/
	updateHeight(n1);
	updateHeight(n3);
}

/*function to call on the DRotate method knowing that its an LR rotation*/
static void LRRotate(TLDList *tld,TLDNode *node){
	/*initialises nodes*/
	TLDNode *n1,*n2,*n3,*p;
	n3 = node;
	n1 = n3->left;
	n2 = n1->right;
	p = n3->parent;
	/*isLeft is created to determine whether the given node is a left child of its parent, in this case we have LR 
	rotation*/
	int isLeft;
	
	/*also ensures that p isnt NULL so there is no seg fault*/
	if(p!=NULL && (n3->parent->left == n3)){
		isLeft = 1;
	}
	
	DRotate(tld,n1,n2,n3,p,isLeft);


}

/*function to call on the DRotate method knowing that its an RL rotation*/
static void RLRotate(TLDList *tld,TLDNode *node){
	/*initialising nodes*/
	TLDNode *n1,*n2,*n3,*p;
	n1 = node;
	n3 = n1->right;
	n2 = n3->left;
	p = n1->parent;
	/*isLeft created for same reason ^*/
	int isLeft;
	/*if statement for the same reason ^*/
	if(p!=NULL && (n1->parent->left == n1)){
		isLeft = 1;
	}
	DRotate(tld,n1,n2,n3,p,isLeft);

}

/*method used to ensure tree is balanced*/
static void restoreBalance(TLDList *tld,TLDNode *node){
	
		/*checks that the left and right nodes of the given node are not NULL to prevent seg faults*/
		if(node->left!=NULL && node->right!=NULL){
		
		/*creates a new imbalanced node and assigns it to the result of finding the imbalanced node*/
		TLDNode *imbalanced = findImbalanced(node);
		if(imbalanced!=NULL){
			/*following if/else if statements check which case is required and run the following alg from there*/
			if(caseLL(imbalanced) == 1){
				LLRotate(tld,imbalanced);	
			}else if(caseLR(imbalanced) == 1){
				LRRotate(tld,imbalanced);
			}else if(caseRL(imbalanced) == 1){
				RLRotate(tld,imbalanced);
			}else if(caseRR(imbalanced) == 1){
				RRRotate(tld,imbalanced);
			}	

		}

		}
}



/*	TLD OPERATIONS		*/

/*function to return the tld from a given hostname*/

char *getTld(char *hostname){
	/*sets the Host char array to the tld of the hostname*/
	char *Host = strrchr(hostname, '.') + 1;

	/*creates a new char array with the size of the host char array*/
	char *newHost = malloc(sizeof(strlen(Host)));

	/*loops through all the characters and changes them to lower case */
	int i = 0;
	for(i; i < strlen(Host); i++){
		newHost[i] = tolower(Host[i]);
	}

	/*returns the newly extracted host*/
	return newHost;
}


/*function to create a new tldlist and return it*/
TLDList *tldlist_create(Date *begin, Date *end){
	/*initialises new tld list and creates space on heap for it*/
	TLDList *tld;
	tld = (TLDList *)malloc(sizeof(TLDList));

	/*if the malloc was successful then initialise all the fields*/
	if(tld!= NULL){
		tld->root = NULL;
		tld->beginDate = date_duplicate(begin);
		tld->endDate = date_duplicate(end);
		tld->size = 0;
		tld->count = 0;
		return tld;
	}
	/*else return a null pointer*/
	return NULL;


}




/*function to traverse the binary tree in order of smallest first i.e left subtree, followed
by right subtree and stores each node in the nodeList object for the iterator*/

void inorder_traverse(TLDNode *nodeList[],long *index, TLDNode *node){	
	if(node->left != NULL){	
		/*recursive calls to get nodes all the way down left and right subtrees*/
		
	
		inorder_traverse(nodeList,index,node->left);
	}
		/*sets the current entry in the nodeList to the node - using a pointer to a long to prevent mismatch
		during recursion*/
		nodeList[*index] = node;
		(*index)++;

	if(node->right!=NULL){
		inorder_traverse(nodeList,index,node->right);			
	}
	
}

/*creates a tld iterator and returns a pointer to it*/

TLDIterator *tldlist_iter_create(TLDList *tld){
	/*creates a new tld iterator and creates space for it on the heap*/
	TLDIterator *tldIterator;

	/*creates a new nodelist and allocates space for it on the heap*/
	TLDNode **nodeList = (TLDNode **)malloc(sizeof(TLDNode *)*tld->size);
	tldIterator = (TLDIterator *)malloc(sizeof(TLDIterator));

	/*if the malloc was successful for the iterator then initialise all the attributes*/
	if(tldIterator!=NULL){
		long *index = (long*)malloc(sizeof(long));
		*index = 0;
		/*calls the inorder traverse algorithm to obtain a list of nodes for nodeList*/
		inorder_traverse(nodeList,index,tld->root);	
		
		/*initialises rest of attributes*/
		tldIterator->next = 0L;
		tldIterator->size = tld->size;		
		tldIterator->nodeList = nodeList;
		


		/*returns the iterator*/
		return tldIterator;
	}else{
	/*returns null pointer if malloc was unsuccessful*/
	return NULL;
	}
}


/*gets the next node in the iterator and returns it*/
TLDNode *tldlist_iter_next(TLDIterator *iter){	
	//printf("next %ld, itersize %ld, content %s\n", iter->next, iter->size, iter->nodeList[iter->next]->content);
	
	/*if the end of the list is reached then return NULL pointer*/
	if(iter->next >= (iter->size)+1){
		return NULL;
	}

	/*else return the next node*/
	return iter->nodeList[iter->next++];
	
}

/*function to destroy all the iterator nodes and then destroy the iterator itself*/
void tldlist_iter_destroy(TLDIterator *iter){

	/*for loop to free all the nodes in the iter nodeList*/
	int i = 0;
	for(i;i<=iter->size;i++){
		free((iter->nodeList)[i]->content);
		free((iter->nodeList)[i]);
	}
	free(iter);
	
}

/*function to create a tldnode and return a pointer to it given a tldname*/
TLDNode *create_tldNode(char *tldname){
	/*creates a new TLDNode and assigns memory to it on the heap*/
	TLDNode *node;
	node = (TLDNode *)malloc(sizeof(TLDNode));
	
	/*if the malloc was successful then initialise all the attributes*/
	if(node != NULL){
		node->parent = NULL;
		node->left = NULL;
		node->right = NULL;
		node->content = tldname;
		node->count = 1;
		node->height =0 ;
		return node;
	}
	return NULL;

}

/*recursive method to destroy all the nodes on the tld tree*/

void iterate_nodes_destroy(TLDNode *node){
	if(node == NULL){
		return;
	}
	iterate_nodes_destroy(node->left);
	iterate_nodes_destroy(node->right);	
	
	/*gets rid of data leaks by destroy the pointer to the content and node*/
	free(node->content);
	free(node);
	
}


/*method to destroy the tldlist by calling the iterative method on the root of the tree*/
void tldlist_destroy(TLDList *tld){
	iterate_nodes_destroy(tld->root);
	free(tld);
	
}

/*returns the numbers of tld hostnames*/
long tldlist_count(TLDList *tld){
	return tld->count;
}


/*returns the content of the specified tld node*/
char *tldnode_tldname(TLDNode *node){
	return node->content;
}


/*returns how many hostnames with the corresponding tld have been read in*/
long tldnode_count(TLDNode *node){
	return node->count;

}


/*recursive method to insert into binary tree*/
static void tld_insert(char *hostname, TLDList *tld, TLDNode *node){
		
		/*result variable to compare the hostname and the hostname on the current node*/
		int result;
		result = strcmp(hostname, node->content);

		/*left hand side is iterated through if the hostname is less than the content*/
		if(result<0){

			/*to prevent seg error, make the recursive call on the left subtree to inser				t if the left node is not null*/
			if(node->left!=NULL){
				tld_insert(hostname, tld, node->left);
				
			/*else create a new tld node in that location as the node is null*/
			}else{
				node->left = create_tldNode(hostname);
				node->left->parent = node;
				(tld->size)++;
				updateHeight(node->left);
				restoreBalance(tld,node->left);
			
			}

		/*right hand sideis iterated through if the hostname is greater than the content*/
		}else if(result>0){

			/*to prevent seg error, make the recursive call on the right subtree to
			insert if the right node is not null*/
			if(node->right != NULL){
				tld_insert(hostname, tld, node->right);

			/*else create a new tld node in that location as the node is null*/
			}else{
				node->right = create_tldNode(hostname);
				node->right->parent = node;
				(tld->size)++;
				updateHeight(node->right);
				restoreBalance(tld,node->right);
			}



		}else{
			/*this case is when the tld node already exists - simply increase the count
			*/
			(node->count)++;

		
		}

}

/*method to add to the tld list, returns 1 if successful*/
int tldlist_add(TLDList *tld, char *hostname, Date *d){

	/*compares the dates of input to determine is the node will be added*/
	if((date_compare(tld->beginDate, d)<=0) && (date_compare(tld->endDate,d)>=0)){
		
		/*if the date is acceptable then add it on the root if it doesnt exist or add it
		elsewhere in the tree by tld_insert*/
		char *host = getTld(hostname);
		if(tld->root == NULL){
			tld->root = create_tldNode(host);
		}else{
			tld_insert(host, tld, tld->root);
		}

		/*after the operation is successful, increment the side of the number of tlds*/
		(tld->count)++;
		return 1;
	

	}

	return 0;
	

}
