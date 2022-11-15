#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
// helper function
int heightPaths(Node* root){	
	// Base case when do we return
	if(root->left == nullptr && root->right == nullptr){
		return 1;
	}
	// iterate three options for each node
	int leftheight, rightheight;
	if(root->left != nullptr && root->right != nullptr){
		leftheight = heightPaths(root->left);
		rightheight = heightPaths(root->right);
	}
	else if(root->left == nullptr){
		rightheight = heightPaths(root->right);
		leftheight = rightheight;
	}
	else if(root->right == nullptr){
		leftheight = heightPaths(root->left);
		rightheight = leftheight;
	}
	else{
		rightheight = heightPaths(root->right);
		leftheight = rightheight;
	}
	
	if(leftheight != rightheight || leftheight == 0 || rightheight == 0){
		return 0;
	}
	else{
		return leftheight + 1;
	}
}

bool equalPaths(Node * root)
{
	// Add your code below
	// Base case: an empty tree is always equalPaths
	if (root == nullptr) return true;
	// use helper function to determine whether equal
	return heightPaths(root);
}
