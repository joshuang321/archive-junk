#include "essent_assets.h"

struct PRIORITY_QUENE;
typedef struct PRIORITY_QUENE PRIORITY_QUENE;

struct PRIORITY_QUENE{
	int* data;
	int front;
	int back;
	int num_size;
};

PRIORITY_QUENE* create_priority_quene(int num_size);
_Bool priority_quene_overflow(PRIORITY_QUENE* quene);
_Bool priority_quene_underflow(PRIORITY_QUENE* quene);
int priority_quene_front(PRIORITY_QUENE* quene);
PRIORITY_QUENE* priority_quene_rear(PRIORITY_QUENE*, int element);
void priority_quene_traverse(PRIORITY_QUENE* quene);
PRIORITY_QUENE* destroy_priority_quene(PRIORITY_QUENE* quene);


PRIORITY_QUENE* create_priority_quene(int num_size){
	PRIORITY_QUENE* priority_quene = calloc(1, sizeof(PRIORITY_QUENE));
	priority_quene->data = calloc(num_size, sizeof(int));
	priority_quene->num_size = num_size;
	
	priority_quene->front = 0;
	priority_quene->back = -1;
	
	return priority_quene;
}

_Bool priority_quene_overflow(PRIORITY_QUENE* quene){
	int num_size = (quene->back + 1) - quene->front;
	if (num_size == quene->num_size){
		puts("QUENE OVERFLOW!");
		return 1;
	}
	
	return 0;
}

_Bool priority_quene_underflow(PRIORITY_QUENE* quene){
	if(quene->front > quene->back){
		puts("QUENE UNDERFLOW!");
		return 1;
	}
	
	return 0;
}

int priority_quene_front(PRIORITY_QUENE* quene){
	if(priority_quene_underflow(quene)){
		return 0;
	}
	
	int front_item = (quene->data)[quene->front];
	(quene->front)++;
	
	if (quene->front > quene->back){
		quene->front = 0;
		quene->back = -1;
	}
	
	return front_item;
}

PRIORITY_QUENE* priority_quene_rear(PRIORITY_QUENE* quene, int element){
	if(priority_quene_overflow(quene)){
		return 0;
	}
	
	(quene->back)++;
	int temp_element;
	int back_cpy = quene->back;
	
	(quene->data)[quene->back] = element;
	
	while(--back_cpy != quene->front - 1){
		if((quene->data)[back_cpy] > (quene->data)[back_cpy + 1]){
			temp_element = (quene->data)[back_cpy];
			(quene->data)[back_cpy] = (quene->data)[back_cpy + 1];
			(quene->data)[back_cpy + 1] = temp_element;
		}
		else{
			break;
		}
	}
	
	return quene;
}

void priority_quene_traverse(PRIORITY_QUENE* quene){
	int front_cpy = quene->front;
	
	printf("[%d]", (quene->data)[front_cpy]);
	
	while(++front_cpy != quene->back + 1){
		printf(",[%d]", (quene->data)[front_cpy]);
	}
	printf("\n");
}

PRIORITY_QUENE* destroy_priority_quene(PRIORITY_QUENE* quene){
	assert(quene);
	free(quene->data);
	quene->data = NULL;
	
	free(quene);
	quene = NULL;
	
	return quene;
}

int main(void){
	PRIORITY_QUENE* priority_quene = create_priority_quene(5);
	
	priority_quene_rear(priority_quene, 5);
	priority_quene_rear(priority_quene, 4);
	priority_quene_rear(priority_quene, 3);
	priority_quene_rear(priority_quene, 2);
	priority_quene_rear(priority_quene, 1);
	priority_quene_rear(priority_quene, 0);
	
	priority_quene_traverse(priority_quene);
	
	priority_quene_front(priority_quene);
	priority_quene_traverse(priority_quene);
	priority_quene_front(priority_quene);
	priority_quene_traverse(priority_quene);
	priority_quene_front(priority_quene);
	priority_quene_traverse(priority_quene);
	
	destroy_priority_quene(priority_quene);
	
	return 0;
}