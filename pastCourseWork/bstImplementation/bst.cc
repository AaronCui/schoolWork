#include <iostream>
#include <vector>
#include <iomanip>	// provides std::setw()
#include <cstdlib>	// provides atoi()
#include <cstdio>	// provides sprintf()

// #include "unit.h"  -> This is school course provided program to test our file 

/**
 * Defines the tree in a type of its own 
 */
typedef int KType;

/**
 * A tree node.
 */
struct Node {
	KType key;
	Node * left;
	Node * right;
};

/**
 * A visitor that can be used to traverse the tree. This is an abstract class;
 * you can't instantiate it directly.
 */
class Visitor {
public:
	virtual ~Visitor() { }
	virtual void visit(Node* node, int level) = 0;
};



/**
 * Creates a new Node with key=key, left=l, and right=r.
 */
Node* createNode( KType key, Node* l = NULL, Node* r = NULL ) {
	Node* result = new Node;
	result->key = key;
	result->left = l;
	result->right = r;
	return result;
}

/**
 * Deletes all nodes in the tree rooted at root and sets root to NULL.
 */
void deleteTree( Node*& root ) {
	if ( root != NULL ) {
		deleteTree( root->left );
		deleteTree( root->right );
		delete root;
		root = NULL;
	}
}

/**
 * Recursively find a node with key 'key'.
 */
Node *& find(KType key, Node *& r) {
	if (r == NULL) return r;
	if (key < r->key)
		return find(key, r->left);
	if (key > r->key)
		return find(key, r->right);
	return r;
}

/**
 * Finds the parent of node in the tree rooted at rootNode
 */
Node* find_parent(Node* rootNode, Node* node) {
	if ( rootNode == NULL || rootNode == node ) {
		return NULL;
	}
	if ( rootNode->left == node || rootNode->right == node ) {
		return rootNode;
	}
	else {
		if (node->key < rootNode->key)
			return find_parent(rootNode->left, node);
		else
			return find_parent(rootNode->right, node);
	}
}

/**
 * Deletes a node containing 'key' in the tree rooted at 'root'.
 */
bool delete_node(Node*& root, KType key) {
	Node* target;
	Node* parent;
	Node* temp;

	// find target node to delete
	target = find(key, root);

	if (!target) {
		return false;
	}

	// find parent of target
	parent = find_parent(root, target);

	// case 1: target is a leaf
	if (target->left == NULL && target->right == NULL) {
		// set parent's child pointer
		if (parent != NULL) {
			if ( parent->left == target )
				parent->left = NULL;
			else
				parent->right = NULL;
		}
		else
			root = NULL;

		// free target
		delete target;
		return true;
	}

	// case 2: target has two children
	else if (target->left != NULL && target->right != NULL) {

		parent = target;
        temp = target->left;
        while (temp->right!=NULL){
                parent = temp;
                temp = temp->right;
            }
            target->key = temp->key;
        if (parent==target && temp->left!=NULL){
            parent->left = temp->left;
        }
        else if(parent==target){
            parent->left = NULL;
        }
        else if (parent !=target && temp->left!=NULL){
            parent->right = temp->left;
        }
        else
            parent->right = NULL;
            delete temp;
            return true;
		 
		 
	}

	// case 3: target has only left child
	else if (target->left != NULL) {
		// set parent's child pointer
		if (parent != NULL) {
			if ( parent->left == target )
				parent->left = target->left;
			else
				parent->right = target->left;
		}
		else
			root = target->left;

		// free target
		delete target;
		return true;
	}

	// case 4: target has only right child
	else {
		// set parent's child pointer
		if (parent != NULL) {
			if (parent->left == target)
				parent->left = target->right;
			else
				parent->right = target->right;
		}
		else
			root = target->right;

		// free target
		delete target;
		return true;
	}
}

/**
 * Inserts key 'key' into the tree rooted at 'root'.
 */
void insert(KType key, Node *& root) {
	Node *& target = find(key, root);
	if( target != NULL ) {
		std::cerr << "Duplicate key \"" << key << "\" not inserted." << std::endl;
	} else {
		target = createNode(key);
	}
}

/**
 * Prints out the tree sideways.
 */
void printTree( Node * r, int d = 0 ) {
	if( r == NULL ) return;
	printTree( r->right, d+1 );
	std::cout << std::setw( 3 * d ) << ""; // output 3 * d spaces
	std::cout << r->key << std::endl;
	printTree( r->left, d+1 );
}


/*
	Helper
*
int numNodesCounter ( Node* root, int totall, int totalr) {
	if ( root == NULL) {
		return totall + totalr;
		}
	else 
		total++;
		return numNodesCounter
	
	
	if ( root != NULL ) {
		total++;
		numNodesCounter( root->left, total);
		numNodesCounter( root->right, total);
	
	}
	
	return total;
}
*/

/**
 * Returns the number of nodes in the tree rooted at root.
 */
int numNodes( Node* root ) {

	int total = 1;

		if(root->left != NULL) {
			total += numNodes(root->left);
		}
 
		if(root->right != NULL) {
			total += numNodes(root->right);
		}
 
	return total;
}


/**
 * Returns the number of leaves in the tree rooted at root.
 */
int numLeaves( Node* root ) {

	int total = 0;

	if(root->left != NULL) {
		total += numLeaves(root->left);
	}

 	if(root->right != NULL) {
		total += numLeaves(root->right);
	}

	else if (root->left == NULL && root->right == NULL) {
		total++;
	}
	 
	return total;
}

/**
 * Returns the height of node x.
 */
int height( Node* x ) {
	 
	 int heightl = 0;
	 int heightr = 0;

	
		if(x->left != NULL) {
			heightl++; 
			heightl += height(x->left);
		}
 
		if(x->right != NULL) {
			heightr++;
			heightr += height(x->right);
		}
 
		if(heightl>heightr) {
			heightr = heightl;
		}
 
	return heightr; 
}

/**
 * Returns the depth of node x in the tree rooted at root.
 */
int depth( Node* x , Node* root ) {
	 
    if (root == x) return 0;
    if (x->key < root->key)
        return depth(x , root->left)+1;
    else
        return depth(x, root->right)+1;
    
	 
}

/**
 * Traverse a tree rooted at rootNode in-order and use 'v' to visit each node.
 */
void in_order( Node*& rootNode, int level, Visitor& v ) {

	if(rootNode==NULL) return;
    else {
        in_order(rootNode->left, level+1,  v);
        v.visit(rootNode,level+1);
        in_order(rootNode->right, level+1,  v);
    }
    
}

/**
 * Traverse a tree rooted at rootNode pre-order and use 'v' to visit each node.
 */
void pre_order( Node*& rootNode, int level, Visitor& v ) {

	if(rootNode==NULL) return;
    else {
        v.visit(rootNode,level+1);
        pre_order(rootNode->left, level+1,  v);
        pre_order(rootNode->right, level+1,  v);
    }
	
}

/**
 * Traverse a tree rooted at rootNode post-order and use 'v' to visit each node.
 */
void post_order( Node*& rootNode, int level, Visitor& v ) {
	 
	if(rootNode==NULL) return;
    else {
        post_order(rootNode->left, level+1,  v);
        post_order(rootNode->right, level+1,  v);
        v.visit(rootNode,level+1);
    }
	 
}

///////////////////////////////////////////////////////////////////////////////
// MAIN
///////////////////////////////////////////////////////////////////////////////

/**
 * Print out visited nodes and which level it is on 
 */
class PrintVisitor : public Visitor {
	void visit(Node* node, int level) {
		std::cout << "Level " << level << ": ( " << node->key << " )" << std::endl;
	}
};

/**
 * Insert your own custom tests and print statements here to test your
 * implementation. These will be executed if you supply the tree keys on the
 * command line. For marking, you will execute the program without arguments,
 * and it will run the automated tests.
 */
void runMain(Node* tree, std::vector<int> keys) {
	/*
	 * CHANGE THIS CODE ALL YOU LIKE. This is your test space.
	 */
	std::cout << "Full Tree:" << std::endl;
	printTree(tree);
	std::cout << std::endl;

	std::cout << "number of Nodes  = " << numNodes(tree) << std::endl;
	std::cout << "number of Leaves = " << numLeaves(tree) << std::endl;
	std::cout << "height of tree   = " << height(tree) << std::endl;
	std::cout << std::endl;
	for (unsigned int i = 0; i < keys.size(); ++i) {
		std::cout << "height(" << keys[i] << ") = " << height(find(keys[i], tree)) << std::endl;
		std::cout << "depth(" << keys[i] << ") = " << depth(find(keys[i], tree), tree) << std::endl;
	}
	std::cout << std::endl;

	PrintVisitor v;
	std::cout << "In-order traversal:" << std::endl;
	in_order(tree, 0, v);
}



///////////////////////////////////////////////////////////////////////////////
// DO NOT ALTER BEYOND THIS POINT
///////////////////////////////////////////////////////////////////////////////
#ifdef SCHOOLTEST
/** values to use for tests */
int keysArr[] =		{5, 3, 2, 1, 6, 8, 4, 7, 9};
int heightArr[] =	{3, 2, 1, 0, 2, 1, 0, 0, 0};
int depthArr[] =	{0, 1, 2, 3, 1, 2, 2, 3, 3};
int inArr[] =		{1, 2, 3, 4, 5, 6, 7, 8, 9};
int preArr[] =		{5, 3, 2, 1, 4, 6, 8, 7, 9};
int postArr[] =		{1, 2, 4, 3, 7, 9, 8, 6, 5};
std::vector<int> keys(keysArr, keysArr + sizeof(keysArr) / sizeof(int));
std::vector<int> heights(heightArr, heightArr + sizeof(heightArr) / sizeof(int));
std::vector<int> depths(depthArr, depthArr + sizeof(depthArr) / sizeof(int));
std::vector<int> inOrder(inArr, inArr + sizeof(inArr) / sizeof(int));
std::vector<int> preOrder(preArr, preArr + sizeof(preArr) / sizeof(int));
std::vector<int> postOrder(postArr, postArr + sizeof(postArr) / sizeof(int));

class TestVisitor : public Visitor {
public:
	std::vector<int> q;
	void visit(Node* node, int level) {
		q.push_back(node->key);
	}
};


// -> I used ifdef to take out the hardcoded test from school .
/**
 * Runs the tests for marking. You can run it yourself to check your solution.
 */
void runTests(Node* tree, std::vector<int> keys) {
	Unit unit;
	TestVisitor v;

	std::cout << "Testing Tree:" << std::endl;
	printTree(tree);
	std::cout << std::endl;

	unit.assertEquals("Number of nodes", 9, numNodes(tree));
	unit.assertEquals("Number of leaves", 4, numLeaves(tree));
	unit.assertEquals("Height", 3, height(tree));

	char* s = new char[8];
	std::string h("height");
	std::string d("depth");
	for (unsigned int i = 0; i < keys.size(); ++i) {
		// C++ makes it almost impossible to concatenate a std::string and an integer.
		// This is better in C++11, but I'll do it the old way for now.
		sprintf(s, "(%d)", keys[i]);
		unit.assertEquals(h+s, heights[i], height(find(keys[i], tree)));
		unit.assertEquals(d+s, depths[i], depth(find(keys[i], tree), tree));
	}
	delete s;

	v.q.clear();
	in_order(tree, 0, v);
	unit.assertvectorEquals("In-order traversal", inOrder, v.q);
	v.q.clear();
	pre_order(tree, 0, v);
	unit.assertvectorEquals("Pre-order traversal", preOrder, v.q);
	v.q.clear();
	post_order(tree, 0, v);
	unit.assertvectorEquals("Post-order traversal", postOrder, v.q);

	//Delete a leaf
	unit.assertNonNull("Finding 9 (a leaf)", find(9, tree));
	delete_node(tree, 9);
	unit.assertNull("Deleting 9 (a leaf)", find(9, tree));
	unit.assertEquals("Number of nodes", 8, numNodes(tree));
	unit.assertEquals("Number of leaves", 3, numLeaves(tree));
	unit.assertEquals("Height", 3, height(tree));

	//Delete a node with one child
	unit.assertNonNull("Finding 2 (a node with one child)", find(2, tree));
	delete_node(tree, 2);
	unit.assertNull("Deleting 2 (a node with one child)", find(2, tree));
	unit.assertEquals("Number of nodes", 7, numNodes(tree));
	unit.assertEquals("Number of leaves", 3, numLeaves(tree));
	unit.assertEquals("Height", 3, height(tree));

	//Delete a node with two children
	unit.assertNonNull("Finding 3 (a node with two children)", find(3, tree));
	delete_node(tree, 3);
	unit.assertNull("Deleting 3 (a node with two children)", find(3, tree));
	unit.assertEquals("Number of nodes", 6, numNodes(tree));
	unit.assertEquals("Number of leaves", 2, numLeaves(tree));
	unit.assertEquals("Height", 3, height(tree));

	//Delete root
	unit.assertNonNull("Finding 5 (the root)", find(5, tree));
	delete_node(tree, 5);
	unit.assertNull("Deleting 5 (the root)", find(5, tree));
	unit.assertEquals("Number of nodes", 5, numNodes(tree));
	unit.assertEquals("Number of leaves", 2, numLeaves(tree));
	unit.assertEquals("Height", 3, height(tree));
	
	//Additional tests for delete, height, depth
	
	Node* tree2 = NULL;
	insert(7, tree2);
	insert(9, tree2);
	insert(5, tree2);
	insert(1, tree2);
	
	//Test height, depth
	Node* node_9 = find(9, tree2);
	unit.assertEquals("Height of 9", 0, height(node_9));
	unit.assertEquals("Depth of 9", 1, depth(node_9, tree2));
	Node* node_1 = find(1, tree2);
	unit.assertEquals("Height of 1", 0, height(node_1));
	unit.assertEquals("Depth of 1", 2, depth(node_1, tree2));
	
	// delete root with 2 children, left child of root is predecessor with 1 child
	delete_node(tree2, 7);
	unit.assertEquals("Number of nodes", 3, numNodes(tree2));
	unit.assertEquals("Number of leaves", 2, numLeaves(tree2));
	unit.assertEquals("Height", 1, height(tree2));
	
    // delete root with 2 children, left child of root is not predecessor, predecessor has 1 child
	insert(4, tree2);
	insert(2, tree2);
	delete_node(tree2, 5);
	unit.assertEquals("Number of nodes", 4, numNodes(tree2));
	unit.assertEquals("Number of leaves", 2, numLeaves(tree2));
	unit.assertEquals("Height", 2, height(tree2));

	std::cout << std::endl;
	unit.printResults();
}
#endif 

/**
 * Runs custom code if given command line arguments, otherwise runs tests.
 */
int main( int argc, char *argv[] ) {
	std::vector<int> keys;
	Node *tree = NULL;

	bool custom = argc > 1;
	if (custom) {	// if keys given on command line, run tests
		keys.clear();
		for (int i=0; i < argc-1; ++i) {
			keys.push_back(atoi(argv[i+1]));
		}
	}

	for (unsigned int i=0; i < keys.size(); ++i) {
		insert(keys[i], tree);
	}

	if (custom) {
		runMain(tree, keys);
		
	} else {
	    std::cout << "No input" << std::endl;
		//runTests(tree, keys);
	}

	// Free up allocated memory
	deleteTree(tree);
	return 0;
}
