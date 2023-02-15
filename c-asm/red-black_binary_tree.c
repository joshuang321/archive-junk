#include "essent_assets.h"

enum color{ black, red };
typedef enum color color;

struct R_B_BINARY_SEARCH_TREE;
typedef struct R_B_BINARY_SEARCH_TREE R_B_BINARY_SEARCH_TREE;
typedef struct R_B_BINARY_SEARCH_TREE* R_B_BINARY_SEARCH_TREE_PTR;

struct R_B_BINARY_SEARCH_TREE_ROOT;
typedef struct R_B_BINARY_SEARCH_TREE_ROOT R_B_BINARY_SEARCH_TREE_ROOT;
typedef struct R_B_BINARY_SEARCH_TREE_ROOT* R_B_BINARY_SEARCH_TREE_ROOT_PTR;


struct R_B_BINARY_SEARCH_TREE{
	R_B_BINARY_SEARCH_TREE_PTR parent, left_child, right_child;
	int data;
	color clr;
};

struct R_B_BINARY_SEARCH_TREE_ROOT{
	R_B_BINARY_SEARCH_TREE_PTR root;
	int height;
};

R_B_BINARY_SEARCH_TREE_PTR create_red_black_binary_search_tree( int element, color clr );
R_B_BINARY_SEARCH_TREE_ROOT_PTR create_red_black_binary_search_tree_root( int element );
void red_black_binary_search_tree_insert_element( R_B_BINARY_SEARCH_TREE_ROOT_PTR tree_root, int element );
int red_black_binary_search_tree_delete_element( R_B_BINARY_SEARCH_TREE_ROOT_PTR tree_root, int element );
R_B_BINARY_SEARCH_TREE_PTR red_black_binary_search_tree_find_element( R_B_BINARY_SEARCH_TREE_ROOT_PTR tree_root, int element );
R_B_BINARY_SEARCH_TREE_PTR red_black_binary_search_tree_balance_tree( R_B_BINARY_SEARCH_TREE_PTR tree );
R_B_BINARY_SEARCH_TREE_PTR red_black_binary_search_tree_recloring( R_B_BINARY_SEARCH_TREE_PTR tree );
R_B_BINARY_SEARCH_TREE_PTR red_black_binary_search_tree_left_left_rotation( R_B_BINARY_SEARCH_TREE_PTR tree );
R_B_BINARY_SEARCH_TREE_PTR red_black_binary_search_tree_left_right_rotation( R_B_BINARY_SEARCH_TREE_PTR tree );
R_B_BINARY_SEARCH_TREE_PTR red_black_binary_search_tree_right_left_roatation( R_B_BINARY_SEARCH_TREE_PTR tree );
R_B_BINARY_SEARCH_TREE_PTR red_black_binary_search_tree_right_right_roatation( R_B_BINARY_SEARCH_TREE_PTR tree );
void red_black_binary_search_tree_display_root( R_B_BINARY_SEARCH_TREE_ROOT_PTR tree_root );
void red_black_binary_search_tree_display( R_B_BINARY_SEARCH_TREE_PTR tree );
void red_black_binary_search_tree_balance_tree_root( R_B_BINARY_SEARCH_TREE_ROOT_PTR tree_root );
R_B_BINARY_SEARCH_TREE_PTR remove_red_black_binary_search_tree( R_B_BINARY_SEARCH_TREE_ROOT_PTR tree_root, int element);
R_B_BINARY_SEARCH_TREE_PTR destroy_red_black_binary_search_tree( R_B_BINARY_SEARCH_TREE_PTR tree );
R_B_BINARY_SEARCH_TREE_ROOT_PTR destroy_red_black_binary_search_tree_root( R_B_BINARY_SEARCH_TREE_ROOT_PTR tree_root );

R_B_BINARY_SEARCH_TREE_PTR create_red_black_binary_search_tree( int element, color clr ){
	R_B_BINARY_SEARCH_TREE_PTR tree = calloc( 1, sizeof(R_B_BINARY_SEARCH_TREE) );
	
	tree->data = element;
	tree->clr = clr;
	
	return tree;
}

R_B_BINARY_SEARCH_TREE_ROOT_PTR create_red_black_binary_search_tree_root( int element ){
	R_B_BINARY_SEARCH_TREE_ROOT_PTR tree_root = calloc( 1, sizeof( R_B_BINARY_SEARCH_TREE_ROOT ) );
	tree_root->root = create_red_black_binary_search_tree( element, ( color ) NULL );
	( tree_root->height )++;
	
	return tree_root;
}

void red_black_binary_search_tree_insert_element( R_B_BINARY_SEARCH_TREE_ROOT_PTR tree_root, int element ){
	color red_clr = red;
	R_B_BINARY_SEARCH_TREE_PTR tree, new_tree = create_red_black_binary_search_tree( element, red_clr );
	tree = red_black_binary_search_tree_find_element( tree_root, element );
	
	if ( element != tree->data ){
		new_tree->parent = tree;
		if ( element > tree->data ){
			tree->right_child = new_tree;
			tree = tree->right_child;
		}
		else{
			tree->left_child = new_tree;
			tree = tree->left_child;
		}
	}
	void* ptr = red_black_binary_search_tree_balance_tree( tree );
	if( NULL != ptr ){
		tree_root->root = ptr;
	}
	( tree_root->root )->clr = black;
}

int red_black_binary_search_tree_delete_element( R_B_BINARY_SEARCH_TREE_ROOT_PTR tree_root, int element ){
	return 0;
}

R_B_BINARY_SEARCH_TREE_PTR red_black_binary_search_tree_find_element( R_B_BINARY_SEARCH_TREE_ROOT_PTR tree_root, int element ){
	R_B_BINARY_SEARCH_TREE_PTR tree = tree_root->root;
	
	while( NULL != tree ){
		if( element == tree->data ){
			break;
		}
		if( element > tree->data ){
			if( NULL == tree->right_child ){
				goto skip;
			}
			tree = tree->right_child;
		}
		else{
			if( NULL == tree->left_child ){
				goto skip;
			}
			tree = tree->left_child;
		}
		
	}
	skip:
	return tree;
}

R_B_BINARY_SEARCH_TREE_PTR red_black_binary_search_tree_balance_tree( R_B_BINARY_SEARCH_TREE_PTR tree ){
	R_B_BINARY_SEARCH_TREE_PTR grandparent_tree;
	R_B_BINARY_SEARCH_TREE_PTR uncle_tree;
	
	while( NULL != tree->parent ){
		grandparent_tree = ( tree->parent )->parent;
		if( NULL == grandparent_tree){
			return NULL;
		}
		
		uncle_tree = ( grandparent_tree->right_child == tree->parent ) ? 
		( grandparent_tree->left_child ) : ( grandparent_tree->right_child );
		
		if( ( tree->parent )->clr == red ){
			if( ( ( NULL == uncle_tree ) ? black : uncle_tree->clr ) == red ){
				tree = red_black_binary_search_tree_recloring( tree );
			}
			else if( grandparent_tree->left_child == tree->parent ){
				if( ( tree->parent )->left_child == tree ){
					tree = red_black_binary_search_tree_left_left_rotation( tree );
				}
				else{
					tree = red_black_binary_search_tree_left_right_rotation( tree );
				}
			}
			else{
				if( (tree->parent )->left_child == tree ){
					tree = red_black_binary_search_tree_right_left_roatation( tree );
				}
				else{
					tree = red_black_binary_search_tree_right_right_roatation( tree );
					if ( tree->parent == NULL ){
					}
				}
			}
		}
	}
	
	return tree;
}

R_B_BINARY_SEARCH_TREE_PTR red_black_binary_search_tree_recloring(R_B_BINARY_SEARCH_TREE_PTR tree ){
	tree = ( tree->parent )->parent;
	if( NULL != tree->left_child ){
		( tree->left_child )->clr = black;
	}
	if( NULL != tree->right_child ){
		( tree->right_child )->clr = black;
	}
	if( NULL != tree->parent ){
		tree->clr = red;
	}
	
	return tree;
}
	
R_B_BINARY_SEARCH_TREE_PTR red_black_binary_search_tree_left_left_rotation( R_B_BINARY_SEARCH_TREE_PTR tree ){
	R_B_BINARY_SEARCH_TREE_PTR temp_tree = ( tree->parent )->parent;
	( tree->parent )->clr = black;
	temp_tree->clr = red;
	temp_tree->left_child = ( tree->parent )->right_child;
	if( NULL != ( tree->parent )->right_child ){
		( ( tree->parent )->right_child )->parent = ( tree->parent )->right_child;
	}
	
	temp_tree->parent = ( tree->parent )->right_child = temp_tree;
	
	return temp_tree;
}

R_B_BINARY_SEARCH_TREE_PTR red_black_binary_search_tree_left_right_rotation( R_B_BINARY_SEARCH_TREE_PTR tree ){
	R_B_BINARY_SEARCH_TREE_PTR temp_tree = ( tree->parent )->left_child;
	int temp_int = tree->data;
	tree->parent = ( tree->parent )->left_child = tree;
	tree->data = ( tree->parent )->data;
	( tree->parent )->data = temp_int;
	
	( tree->right_child )->parent = ( tree->parent )->right_child = tree->right_child;
	tree->right_child = tree->left_child;
	tree->left_child = temp_tree;
	
	temp_tree = red_black_binary_search_tree_left_left_rotation( tree );
	
	return temp_tree;
}

R_B_BINARY_SEARCH_TREE_PTR red_black_binary_search_tree_right_left_roatation( R_B_BINARY_SEARCH_TREE_PTR tree ){
	R_B_BINARY_SEARCH_TREE_PTR temp_tree = ( tree->parent )->right_child;
	int temp_int = tree->data;
	( tree->parent )->right_child = tree;
	tree->data = ( tree->parent )->data;
	( tree->parent )->data = temp_int;
	
	( tree->parent )->left_child = tree->left_child;
	
	if( NULL != ( tree->left_child ) ){
	( tree->left_child )->parent = tree->left_child;
	}
	
	tree->left_child = tree->right_child;
	tree->right_child = temp_tree;
	
	temp_tree = red_black_binary_search_tree_right_right_roatation( tree );
	
	return temp_tree;
}

R_B_BINARY_SEARCH_TREE_PTR red_black_binary_search_tree_right_right_roatation( R_B_BINARY_SEARCH_TREE_PTR tree ){
	R_B_BINARY_SEARCH_TREE_PTR temp_tree = ( tree->parent )->parent;
	( tree->parent )->clr = black;
	temp_tree->clr = red;
	temp_tree->right_child = ( tree->parent )->left_child;
	( tree->parent )->parent = temp_tree->parent;
	
	if ( NULL != temp_tree->parent ){
		if ( ( temp_tree->parent )->left_child == temp_tree ){
			( temp_tree->parent )->left_child = tree->parent;
		}
		else{
			( temp_tree->parent )->right_child = tree->parent;
		}
	}
	
	( tree->parent )->left_child = temp_tree;
	temp_tree->parent = tree->parent;
	
	temp_tree = tree->parent;
	return temp_tree;
}

void red_black_binary_search_tree_display_root( R_B_BINARY_SEARCH_TREE_ROOT_PTR tree_root ){
	red_black_binary_search_tree_display( tree_root->root );
	puts( "" );
}

void red_black_binary_search_tree_display( R_B_BINARY_SEARCH_TREE_PTR tree ){
	if( NULL != tree->left_child ){;
		red_black_binary_search_tree_display( tree->left_child );
	}
	
	printf( "[%d] ", tree->data );
	
	if( NULL != tree->right_child ){
		red_black_binary_search_tree_display( tree->right_child );
	}
}

R_B_BINARY_SEARCH_TREE_PTR remove_red_black_binary_search_tree( R_B_BINARY_SEARCH_TREE_ROOT* tree_root, int element){
	R_B_BINARY_SEARCH_TREE_PTR tree = tree_root->root;
	
	while( element != tree->data ){
		if ( element > tree->data ){
			tree = tree->right_child;
		}
		else{
			tree = tree->left_child;
		}
	}
	destroy_red_black_binary_search_tree( tree );
	return tree;
}

R_B_BINARY_SEARCH_TREE_PTR destroy_red_black_binary_search_tree( R_B_BINARY_SEARCH_TREE_PTR tree ){
	if( NULL != tree->left_child ){
		destroy_red_black_binary_search_tree( tree->left_child );
	}
	
	if( NULL != tree->right_child ){
		destroy_red_black_binary_search_tree( tree->right_child );
	}
	free( tree );
	return tree;
}

R_B_BINARY_SEARCH_TREE_ROOT_PTR destroy_red_black_binary_search_tree_root( R_B_BINARY_SEARCH_TREE_ROOT_PTR tree_root ){
	destroy_red_black_binary_search_tree( tree_root->root );
	free( tree_root );
	return tree_root;
}

int main(void){
	 R_B_BINARY_SEARCH_TREE_ROOT_PTR tree_root = create_red_black_binary_search_tree_root( 4 );
	 red_black_binary_search_tree_insert_element( tree_root, 5 );
	 red_black_binary_search_tree_insert_element( tree_root, 6 );
	 red_black_binary_search_tree_insert_element( tree_root, 7 );
	 red_black_binary_search_tree_insert_element( tree_root, 8 );
	 
	 red_black_binary_search_tree_display_root( tree_root );
	 destroy_red_black_binary_search_tree_root( tree_root );
	 return 0;
}