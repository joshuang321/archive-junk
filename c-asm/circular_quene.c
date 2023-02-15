#include "essent_assets.h"

struct CIRCULAR_QUENE;
typedef struct CIRCULAR_QUENE CIRCULAR_QUENE;

struct CIRCULAR_QUENE{
	int* data;
	int front;
	int back;
	int num_size;
};

CIRCULAR_QUENE* create_circular_quene(int num_size);
_Bool circular_quene_overflow(CIRCULAR_QUENE* quene);
_Bool circular_quene_underflow(CIRCULAR_QUENE* quene);
int circular_quene_front(CIRCULAR_QUENE* quene);
CIRCULAR_QUENE* circular_quene_rear(CIRCULAR_QUENE* quene, int element);
void circular_quene_traverse(CIRCULAR_QUENE* quene);
CIRCULAR_QUENE* destroy_circular_quene(CIRCULAR_QUENE* quene);

CIRCULAR_QUENE* create_circular_quene(int num_size){
	CIRCULAR_QUENE* circular_quene = calloc(1, sizeof(CIRCULAR_QUENE));
	circular_quene->data = calloc(num_size, sizeof(int));
	circular_quene->num_size = num_size;
	
	circular_quene->front= 0;
	circular_quene->back = -1;
	
	return circular_quene;
}

_Bool circular_quene_overflow(CIRCULAR_QUENE* quene){
	if(quene->front == (quene->back  + 1)%(quene->num_size)){
		puts("CIRCULAR_QUENE OVERFLOW!");
		return 1;
	}
	
	return 0;
}

_Bool circular_quene_underflow(CIRCULAR_QUENE* quene){
	if(quene->front == quene->back){
		puts("CIRCULAR_QUENE UNDERFLOW!");
		return 1;
	}
	
	return 0;
}

int circular_quene_front(CIRCULAR_QUENE* quene){
	if(circular_quene_underflow(quene)){
		return 0;
	}
	
	int front_item = (quene->data)[quene->front];
	quene->front = (quene->front + 1)%(quene->num_size);
	
	if(quene->front == quene->back){
		quene->front = 0;
		quene->back = -1;
	}
	
	return front_item;
}

CIRCULAR_QUENE* circular_quene_rear(CIRCULAR_QUENE* quene, int element){
	if(circular_quene_overflow(quene) && quene->back != -1){
		return 0;
	}
	
	quene->back = (quene->back + 1)%(quene->num_size);
	(quene->data)[quene->back] = element;
	
	return quene;
}

void circular_quene_traverse(CIRCULAR_QUENE* quene){
	int front_cpy = quene->front;
	
	printf("[%d]", (quene->data)[front_cpy]);
	front_cpy = (front_cpy + 1)%(quene->num_size);
	
	while(front_cpy != (quene->back + 1)%(quene->num_size)){
	printf(",[%d]", (quene->data)[front_cpy]);
	front_cpy = (front_cpy + 1)%(quene->num_size);
	}
	
	printf("\n");
}

CIRCULAR_QUENE* destroy_circular_quene(CIRCULAR_QUENE* quene){
	assert(quene);
	
	free(quene->data);
	quene->data = NULL;
	
	free(quene);
	quene = NULL;
	
	return quene;
}

int main(void){
	CIRCULAR_QUENE* quene = create_circular_quene(5);
	circular_quene_underflow(quene);
	
	circular_quene_rear(quene, 1);
	circular_quene_rear(quene, 2);
	circular_quene_rear(quene, 3);
	circular_quene_rear(quene, 4);
	circular_quene_rear(quene, 5);
	
	circular_quene_overflow(quene);
	circular_quene_traverse(quene);
	
	circular_quene_front(quene);
	circular_quene_overflow(quene);
	
	circular_quene_traverse(quene);
	
	destroy_circular_quene(quene);
	
	return 0;
}

		

