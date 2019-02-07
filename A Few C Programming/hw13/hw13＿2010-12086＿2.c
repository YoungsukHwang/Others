#include<stdio.h>
#include<stdlib.h>
typedef struct elem{
	int n;
	struct elem *next;
}ELEM;
typedef struct stack{
	int cnt;
	ELEM *top;
}STACK;

ELEM *makeElem(int n){
	ELEM *aElem = (ELEM*) malloc(sizeof(ELEM));
	aElem -> n = n;

	return aElem;
}
void initialize(STACK *stk){
	stk->cnt=0;
	stk->top = NULL;
}
void push(int n, STACK *stk){
	ELEM *aElem = makeElem(n);
	aElem->next = stk->top;
	stk->top = aElem;
	stk->cnt++;
}
int pop(STACK *stk){
	int n;
	n = stk->top->n;
	ELEM *aElem = makeElem(n);
	aElem = stk->top;
	stk->top = stk->top->next;
	stk->cnt--;
	free(aElem);
	return n;
}
int top(STACK *stk){
	return (stk->top->n);
}
void print(STACK *stk){
	int i,n;
	if(stk->top==NULL){
		n =0;
		printf("No Element in the stack\n");	
	}else{
		n = stk->top->n;
		ELEM *topElem = makeElem(n);
		topElem = stk->top;
		for(i=0;i<stk->cnt;i++)
		{
			printf("stk cnt %d : %d\n",stk->cnt-i,stk->top->n);
			stk->top = stk->top->next;
		}
		stk->top = topElem;
	}
	printf("Stack Print Done\n");	
}

int main(void){	
	printf("I CAN DO IT!\n");

	STACK *stk = (STACK*)malloc(sizeof(STACK));
	initialize(stk);

	int n;
	char multiply[2] ="*", addition[2] ="+",subtraction[2] = "-", division[2] = "/";
	char input[5];

/*	printf("input:");
	scanf("%s",input);
	n = atoi(input);
	push(n,stk);

	printf("input:");	
	scanf("%s",input);
	n = atoi(input);
	push(n,stk);
*/
	while(1)
	{
		printf("input:");
		scanf("%s",input);
		int val1, val2;
		if(strcmp(input,multiply)==0 || strcmp(input, addition)==0 ||strcmp(input, subtraction)==0 ||strcmp(input, division)==0)
		{
			val1 = stk->top->n;
			pop(stk);
			val2 = stk->top->n;
			pop(stk);
			if(strcmp(input,multiply)==0){
				push(val1*val2, stk);
			}	
			if(strcmp(input, addition)==0){
				push(val1+val2, stk);
			}
			if(strcmp(input,subtraction)==0){
				push(val2-val1, stk);
			}	
			if(strcmp(input,division)==0){
				if(val1 ==0){
					printf("You can't divide by zero.\n");
					push(val2, stk);
					push(val1, stk);
				}else
					push(val2/val1, stk);
			}	
		}else{
			n = atoi(input);
			push(n,stk);
		}
		print(stk);
	}
}
