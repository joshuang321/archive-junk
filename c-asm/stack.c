#include "essent_assets.h"

struct STACK;
typedef struct STACK STACK;

struct STACK{
	int* data;
	int top;
};

STACK* create_stack(void);
STACK* stack_push(STACK* stack, int item);
int stack_pop(STACK* stack);
_Bool stack_empty(STACK* stack);
int stack_top(STACK* stack);
int stack_peep(STACK* stack,int element);
STACK* destroy_stack(STACK* stack);

STACK* create_stack(void){
	STACK* stack = calloc(1, sizeof(STACK));
	stack->top = -1;
	return stack;
}

STACK* stack_push(STACK* stack, int item){
	(stack->top)++;
	stack->data = realloc(stack->data, sizeof(int) * (stack->top + 1));
	(stack->data)[(stack->top)] = item;
	return stack;
}

int stack_pop(STACK* stack){
	if (stack_empty(stack)){
		puts("STACK EMPTY!");
		return 0;
	}
	
	int top_item = (stack->data)[(stack->top)];
	(stack->top)--;
	stack->data = realloc(stack->data, sizeof(int) * (stack->top + 1));
	if (stack->top == -1)
		stack->data = NULL;
	
	return top_item;
}

_Bool stack_empty(STACK* stack){
	if(stack->top == -1)
		return 1;
	
	return 0;
}

int stack_top(STACK* stack){
	return (stack->data)[(stack->top)];
}

int stack_peep(STACK* stack,int element){
	if ((element < 0) || (element > stack->top)){
		puts("STACK OUT OF BOUNDS!");
		return 0;
	}
	
	return (stack->data)[element];
}

STACK* destroy_stack(STACK* stack){
	assert(stack);
	
	if (stack->data !=NULL){
		free(stack->data);
		stack->data = NULL;
	}
	
	free(stack);
	stack = NULL;
	
	return stack;
}
	

int main(void){
	STACK* stack = create_stack();
	stack_pop(stack);
	stack_push(stack, 5);
	
	printf("%d %d %d %d\n",stack_pop(stack), stack_peep(stack, 3), stack_peep(stack, 0), stack_top(stack));
	if(stack_empty(stack))
		puts("It is empty!");
	
	destroy_stack(stack);
	return 0;
}
	
