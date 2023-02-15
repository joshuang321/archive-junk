#include "essent_assets.h"

struct LINKED_LIST;
typedef struct LINKED_LIST LINKED_LIST;

struct INT_ARRAY;
typedef struct INT_ARRAY INT_ARRAY;

struct LINKED_LIST{
	int data;
	LINKED_LIST* next;
	int num_size;
};

struct INT_ARRAY{
	int* data;
	int len;
};

LINKED_LIST* create_linked_list(int data);
_Bool linked_list_empty(LINKED_LIST* list);
int linked_list_element_search(LINKED_LIST* list, int data);
INT_ARRAY linked_list_pred_and_succ_search(LINKED_LIST* list, int data);
int linked_list_delete_element(LINKED_LIST* list, int location);
LINKED_LIST* linked_list_add_element(LINKED_LIST* list, int data, int location);
int linked_list_retrieve_element(LINKED_LIST* list, int location);
LINKED_LIST* linked_list_update_element(LINKED_LIST* list, int data, int location);
void linked_list_print(LINKED_LIST* list);
LINKED_LIST* delete_linked_list(LINKED_LIST* list);
int* destroy_array(INT_ARRAY int_array);

LINKED_LIST* create_linked_list(int data){
	LINKED_LIST* linked_list = calloc(1, sizeof(LINKED_LIST));
	linked_list->data = data;
	linked_list->num_size = 0;
	linked_list->next = NULL;
	
	return linked_list;
}

_Bool linked_list_empty(LINKED_LIST* list){
	if(list->num_size == 0){
		puts("LIST EMPTY!");
		return 1;
	}
	
	return 0;
}

int linked_list_element_search(LINKED_LIST* list, int data){
	int location, starting;
	starting = list->num_size;
	
	while(NULL != list){
		if (list->data  == data){
			location = starting - list->num_size + 1;
			break;
		}
		list = list->next;
	}
	
	if (NULL == list){
		puts("ELEMENT NOT FOUND!");
		return 0;
	}
	
	return location;
}

INT_ARRAY linked_list_pred_and_succ_search(LINKED_LIST* list, int data){
	INT_ARRAY pred_and_succ = {.len = 2};
	pred_and_succ.data = calloc(pred_and_succ.len , sizeof(int));
	
	int target_element = linked_list_element_search(list, data);
	(pred_and_succ.data)[0] = linked_list_retrieve_element(list, target_element + 1);
	
	if(target_element -1){
		(pred_and_succ.data)[1] = linked_list_retrieve_element(list, target_element - 1);
	}
	
	destroy_array(pred_and_succ);
	
	return pred_and_succ;
}

int linked_list_delete_element(LINKED_LIST* list, int location){
	LINKED_LIST* temp_linked_list;
	int linked_list_element;
	if(location == 1){
		temp_linked_list = list;
		goto skip;
	}
	
	for(int i=0; i<location - 2; i++){
		(list->num_size)--;
		list = list->next;
	}
	
	temp_linked_list = list->next;
	list->next = temp_linked_list->next;
	
	(list->num_size)--;
	
	skip:
	linked_list_element = temp_linked_list->data;
	free(temp_linked_list);
	
	return linked_list_element;
}

LINKED_LIST* linked_list_add_element(LINKED_LIST* list, int data, int location){
	LINKED_LIST* temp_linked_list;
	LINKED_LIST* new_linked_list = create_linked_list(data);
	
	for(int i=0; i<location - 1; i++){
		(list->num_size)++;
		list = list->next;
	}
	if (NULL != list->next){
		temp_linked_list = list->next;
		new_linked_list->next = temp_linked_list;
	}
	(list->num_size)++;
	
	new_linked_list->num_size = list->num_size - 1;
	list->next = new_linked_list;
	
	return new_linked_list;
}

int linked_list_retrieve_element(LINKED_LIST* list, int location){
	for(int i=0; i<location - 1; i++){
		list = list->next;
	}
	
	return list->data;
}

LINKED_LIST* linked_list_update_element(LINKED_LIST* list, int data, int location){
	for(int i=0; i<location - 1; i++){
		list = list->next;
	}
	list->data = data;
	
	return list;
}

void linked_list_print(LINKED_LIST* list){
	printf("[%d]", list->data);
	list = list->next;
	
	while(NULL != list){
		printf(",[%d]", list->data);
		list = list->next;
	}
	printf("\n");
}

LINKED_LIST* delete_linked_list(LINKED_LIST* list){
	LINKED_LIST* linked_list_iterator;
	
	while(NULL != list){
		linked_list_iterator = list;
		list = list->next;
		
		free(linked_list_iterator);
		linked_list_iterator = NULL;
	}
	
	return list;
}

int* destroy_array(INT_ARRAY int_array){
	assert(int_array.data);
	free(int_array.data);
	
	return int_array.data;
}

int main(void){
	LINKED_LIST* linked_list = create_linked_list(3);
	LINKED_LIST* temp_list = linked_list_add_element(linked_list, 2, 1);
	
	linked_list_print(linked_list);
	
	printf("%d %d\n", linked_list_delete_element(linked_list, 1), linked_list_element_search(linked_list, 3));
	delete_linked_list(temp_list);
	
	return 0;
}