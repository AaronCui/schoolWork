#include <iostream>
#include <vector>
#include <iomanip>	
#include <cstdlib>	
#include <cstdio>	

/**
 * Defines the tree value in a type of its own 
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
 * Print out visited nodes 
 */
class PrintVisitor : public Visitor {
	void visit(Node* node, int level) {
		std::cout << "Visited node: ( " << node->key << " )" << std::endl;
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
	/*
	for (unsigned int i = 0; i < keys.size(); ++i) {
		std::cout << "height(" << keys[i] << ") = " << height(find(keys[i], tree)) << std::endl;
		std::cout << "depth(" << keys[i] << ") = " << depth(find(keys[i], tree), tree) << std::endl;
	}
	std::cout << std::endl;
    */
    
	PrintVisitor v;
	std::cout << "In-order traversal:" << std::endl;
	in_order(tree, 0, v);
	
	PrintVisitor v2;
	std::cout << "pre-order traversal:" << std::endl;
	pre_order(tree, 0, v2);
	
	PrintVisitor v3;
	std::cout << "post-order traversal:" << std::endl;
	post_order(tree, 0, v3);
	
}


class TestVisitor : public Visitor {
public:
	std::vector<int> q;
	void visit(Node* node, int level) {
		q.push_back(node->key);
	}
};



/**
 * Runs input values if given command line arguments, otherwise indicates no input 
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
