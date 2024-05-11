#include "node.h"
#include <iostream>

using namespace std;
class RedBlack{
	node* root;
	int size;
	
	node* create_node(int num, node* p, bool isRed){
		node* n = new node;
		n->elem = num;
		n->left = NULL;
		n->right = NULL;
		n->parent = p;
		n->isRed = false;
		
		size++;
		
		return n;
	}
	
	public:
		RedBlack(){
			root = NULL;
			size = 0;
		}
	void insert(int num) {
    // Create a new node with the given number
    node* n = create_node(num, NULL, false);
    
    // if no root, assign the node to the root
    if (!root) {
        root = n;
        return;
    } 
    
    node* curr = root;
    while (true) {
        if (num < curr->elem) {
            if (curr->left == NULL) {
                n->parent = curr;
                n->isRed = true;
                curr->left = n;
                restructure(n);
                break; 
            } else {
                curr = curr->left;
            }
        } else {
            if (curr->right == NULL) {
                n->parent = curr;
                n->isRed = true;
                curr->right = n;
                restructure(n);
                break; 
            } else {
                curr = curr->right;
	            }
	        }
	    }
	}
	void recolor(node *curr) {
    curr->isRed = false;
    curr->left->isRed = true;
    curr->right->isRed = true;
  }
  	bool restructure(node *child) {
	    node *par = child->parent;
	    if (!par || !par->isRed || !child->isRed)
	      return true;
	    node *gp = par->parent;
	    node *sib;
	    if(gp->left == par){
	    	sib = gp->right;
		} else {
			sib = gp->left;
		}
	    if (!sib || !sib->isRed) {
	      bool ptop_right = par->left == child;
	      bool gtop_right = gp->left == par;
	      if (gtop_right && ptop_right) {
	        zigright(par);
	        recolor(par);
	      } else if (gtop_right && !ptop_right) {
	        zigleft(child);
	        zigright(child);
	        recolor(child);
	      } else if (!gtop_right && !ptop_right) {
	        zigleft(par);
	        recolor(par);
	      } else {
	        zigright(child);
	        zigleft(child);
	        recolor(child);
	      }
	    } else {
	      par->isRed = false;
	      sib->isRed = false;
	      if (gp != root)
	        gp->isRed = true;
	      return true;
	    }
	    return true;
	}
	void zigleft(node *curr) {
	    node *x = curr;
	    node *y = x->parent;
	    node *z = y->parent;
	    if (z == NULL){
	    	root = x;
		}else if (y == z->left){
			z->left = x;
		} else{
			z->right = x;	
		}
	      
	    x->parent = z;
	    y->parent = x;
	    if (x->left){
	    	x->left->parent = y;	
		}
	      
	    y->right = x->left;
	    x->left = y;
	}
  void zigright(node *curr) {
    node *x = curr;
    node *y = x->parent;
    node *z = y->parent;
    if (z == NULL){
    	root = x;
	} else if (y == z->left){
    	z->left = x;
	} else{
    	z->right = x;	
	}
      
    y->parent = x;
    x->parent = z;
    if (x->right){
    	x->right->parent = y;
	}
    y->left = x->right;
    x->right = y;
  	}
	void print(){
		cout << "Size: " << size << endl;
		print("", 'Q', root);
	}
	
	void print(string pre, char loc, node* n){
		if(!n){
			return;
		}
		cout << pre << "|--" << loc << ": " << n->elem;
		
		if(n->isRed){
			cout << "(R)"<< endl;
		} else {
			cout << "(B)" << endl;
		}
		print(pre + "    ", 'L', n->left);
		print(pre + "    ", 'R', n->right);
	}
};
