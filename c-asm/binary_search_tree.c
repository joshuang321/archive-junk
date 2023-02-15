#include "essent_assets.h"

struct BINARY_SEARCH_TREE_ROOT;
typedef struct BINARY_SEARCH_TREE_ROOT BINARY_SEARCH_TREE_ROOT;

struct BINARY_SEARCH_TREE;
typedef struct BINARY_SEARCH_TREE BINARY_SEARCH_TREE;

struct STACK;
typedef struct STACK STACK;

struct BINARY_SEARCH_TREE_ARRAY;
typedef struct BINARY_SEARCH_TREE_ARRAY BINARY_SEARCH_TREE_ARRAY;

struct BINARY_SEARCH_TREE_ROOT{
	BINARY_SEARCH_TREE* root;
	int count;
};

struct BINARY_SEARCH_TREE{
	BINARY_SEARCH_TREE* left_child;
	BINARY_SEARCH_TREE* right_child;
	BINARY_SEARCH_TREE* parent;
	int data;
};

struct STACK{
	int* data;
	int front;
};

struct BINARY_SEARCH_TREE_ARRAY{
	BINARY_SEARCH_TREE** tree_data;
	int* array;
	int tree_data_len;
};

BINARY_SEARCH_TREE* create_binary_search_tree(int element);
BINARY_SEARCH_TREE_ROOT* create_binary_search_tree_root(int element);
STACK* binary_search_tree_get_elements(BINARY_SEARCH_TREE_ROOT* tree_root, STACK* stack);
BINARY_SEARCH_TREE* binary_search_tree_get_element(BINARY_SEARCH_TREE_ROOT* tree_root, int element);
void binary_search_tree_add_element(BINARY_SEARCH_TREE_ROOT* tree_root, int element);
void binary_search_tree_delete_element(BINARY_SEARCH_TREE_ROOT* tree_root, int element);
void binary_search_tree_remove_tree(BINARY_SEARCH_TREE_ROOT* tree_root, int element);
void binary_search_tree_root_print(BINARY_SEARCH_TREE_ROOT* tree_root);
void binary_search_tree_print(BINARY_SEARCH_TREE* tree);
BINARY_SEARCH_TREE* binary_search_tree_find_root(BINARY_SEARCH_TREE* tree);
BINARY_SEARCH_TREE_ROOT* destroy_binary_search_tree_root(BINARY_SEARCH_TREE_ROOT* tree_root);
BINARY_SEARCH_TREE* destroy_binary_search_tree(BINARY_SEARCH_TREE* tree);

STACK* create_stack(void);
void stack_insert(STACK* stack, int element);
int stack_pop(STACK* stack);
void stack_print(const STACK* stack);
_Bool stack_empty(const STACK* stack);
STACK* destroy_stack(STACK* stack);

BINARY_SEARCH_TREE* create_binary_search_tree(int element){
	BINARY_SEARCH_TREE* tree = calloc(1, sizeof(BINARY_SEARCH_TREE));
	tree->data = element;
	
	return tree;
}

BINARY_SEARCH_TREE_ROOT* create_binary_search_tree_root(int element){
	BINARY_SEARCH_TREE_ROOT* tree_root = calloc(1, sizeof(BINARY_SEARCH_TREE_ROOT));
	tree_root->root = create_binary_search_tree(element);
	(tree_root->count)++;
	
	return tree_root;
}

STACK* binary_search_tree_get_elements(BINARY_SEARCH_TREE_ROOT* tree_root, STACK* stack){
	return NULL;
}

BINARY_SEARCH_TREE* binary_search_tree_get_element(BINARY_SEARCH_TREE_ROOT* tree_root, int element){
	BINARY_SEARCH_TREE* tree = tree_root->root;
	
	while(NULL != tree){
		if(element == tree->data){
			return tree;
		}
		
		if (element > tree->data){
			tree = tree->right_child;
		}
		else{
			tree = tree->left_child;
		}
	}
	
	puts("ELEMENT NOT FOUND!");
	return NULL;
}

void binary_search_tree_add_element(BINARY_SEARCH_TREE_ROOT* tree_root, int element){
	BINARY_SEARCH_TREE* new_tree = create_binary_search_tree(element);
	BINARY_SEARCH_TREE* tree_iterator = tree_root->root;
	
	while(NULL != tree_iterator){
		if(element == tree_iterator->data){
			puts("ELEMENT ALREADY EXISTS!");
			free(new_tree);
			return (void)0;
		}
		
		if(element > tree_iterator->data){
			if (NULL == tree_iterator->right_child){
				new_tree->parent = tree_iterator;
				tree_iterator->right_child = new_tree;
				return (void)0;
			}
			tree_iterator = tree_iterator->right_child;
		}
		else{
			if (NULL == tree_iterator->left_child){
				new_tree->parent = tree_iterator;
				tree_iterator->left_child = new_tree;
				return (void)0;
			}
			tree_iterator = tree_iterator->left_child;
		}
	}
	
}

void binary_search_tree_delete_element(BINARY_SEARCH_TREE_ROOT* tree_root, int element){
	BINARY_SEARCH_TREE* tree = binary_search_tree_get_element(tree_root, element);
	BINARY_SEARCH_TREE* parent_temp_tree;
	BINARY_SEARCH_TREE* temp_tree;
	
	if(NULL != tree->left_child && NULL != tree->right_child){
		temp_tree = tree->left_child;
		while(NULL != temp_tree->left_child){
			temp_tree = temp_tree->left_child;
		}
		parent_temp_tree = temp_tree->parent;
		tree->data = temp_tree->data;
		
		if (parent_temp_tree != tree){
			parent_temp_tree->left_child = NULL;
		}
		puts("YES");
		assert(temp_tree);
		destroy_binary_search_tree(temp_tree);
	}
	else{
		parent_temp_tree = tree->parent;
		if(NULL != tree->left_child){
			temp_tree = tree->left_child;
			tree->left_child = NULL;
		}
		else{
			temp_tree = tree->right_child;
			tree->right_child = NULL;
		}
		
		if(parent_temp_tree->left_child == tree){
			parent_temp_tree->left_child = temp_tree;
		}
		else{
			parent_temp_tree->right_child = temp_tree;
		}
		destroy_binary_search_tree(tree);
	}
}

void binary_search_tree_remove_tree(BINARY_SEARCH_TREE_ROOT* tree_root, int element){
	BINARY_SEARCH_TREE* tree = binary_search_tree_get_element(tree_root, element);
	BINARY_SEARCH_TREE* parent_tree = tree->parent;
	
	if(parent_tree->left_child == tree){
		parent_tree->left_child = NULL;
	}
	else{
		parent_tree->right_child = NULL;
	}
	destroy_binary_search_tree(tree);
}

void binary_search_tree_root_print(BINARY_SEARCH_TREE_ROOT* tree_root){
	BINARY_SEARCH_TREE* tree = tree_root->root;
	binary_search_tree_print(tree);
	
	printf("\n");
}

void binary_search_tree_print(BINARY_SEARCH_TREE* tree){
	if(NULL != tree->left_child){
		binary_search_tree_print(tree->left_child);
	}
	
	printf(" [%d]", tree->data);
	
	if(NULL != tree->right_child){
		binary_search_tree_print(tree->right_child);
	}
	
}

BINARY_SEARCH_TREE* binary_search_tree_find_root(BINARY_SEARCH_TREE* tree){
	while(NULL != tree->parent){
		tree = tree->parent;
	}
	return tree;
}

BINARY_SEARCH_TREE_ROOT* destroy_binary_search_tree_root(BINARY_SEARCH_TREE_ROOT* tree_root){
	destroy_binary_search_tree(tree_root->root);
	free(tree_root);
	
	tree_root = NULL;
	
	return tree_root;
}

BINARY_SEARCH_TREE* destroy_binary_search_tree(BINARY_SEARCH_TREE* tree){
	if(NULL != tree->left_child){
		destroy_binary_search_tree(tree->left_child);
	}
	else if(NULL != tree->right_child){
		destroy_binary_search_tree(tree->right_child);
	}
	
	free(tree);
	
	return tree;
}

STACK* create_stack(void){
	STACK* stack = calloc(1, sizeof(int));
	(stack->front)--;
	
	return stack;
}

void stack_insert(STACK* stack, int element){
	(stack->front)++;
	stack->data = calloc(stack->front + 1, sizeof(int));
	(stack->data)[stack->front] = element;
}

int stack_pop(STACK* stack){
	int pop_element = (stack->data)[stack->front];
	(stack->front)--;
	stack->data = realloc(stack->data, (stack->front + 1) * sizeof(int));
	
	return pop_element;
}

void stack_print(const STACK* stack){
	int front = stack->front;
	printf("[%d]", (stack->data)[front]);
	
	while(--front != -1){
		printf("[%d]", (stack->data)[front]);
	}	
}

_Bool stack_empty(const STACK* stack){
	if (stack->front == -1){
		puts("STACK EMPTY!");
		return 1;
	}
	return 0;
}

STACK* destroy_stack(STACK* stack){
	assert(stack);
	free(stack->data);
	free(stack);
	stack = NULL;
	return stack;
}

int main(void){
	BINARY_SEARCH_TREE_ROOT* tree_root = create_binary_search_tree_root(0);
	binary_search_tree_add_element(tree_root, 1);
	binary_search_tree_add_element(tree_root, 2);
	binary_search_tree_add_element(tree_root, 3);
	binary_search_tree_add_element(tree_root, 4);
	binary_search_tree_add_element(tree_root, 5);
	binary_search_tree_add_element(tree_root, 6);
	binary_search_tree_add_element(tree_root, 7);
	binary_search_tree_add_element(tree_root, 8);
	binary_search_tree_add_element(tree_root, 9);
	binary_search_tree_add_element(tree_root, 10);
	
	binary_search_tree_root_print(tree_root);
	
	binary_search_tree_remove_tree(tree_root, 2);
	binary_search_tree_get_element(tree_root, 2);
	
	binary_search_tree_delete_element(tree_root, 1);
	binary_search_tree_root_print(tree_root);
	
	destroy_binary_search_tree_root(tree_root);
	return 0;
}