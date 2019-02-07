#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

typedef struct node{
	int n;
	struct node *nextNode;
}NODE;

NODE *makeNode(int n){
    NODE *aNode = (NODE*)malloc(sizeof(struct node));
//	memset(aNode,0, sizeof(struct node));
	aNode->n = n;

	return aNode;
}

void insert(NODE *p1, NODE *p2, NODE *q)
{
	assert(p1->nextNode ==p2);
	p1 -> nextNode = q;
	q -> nextNode = p2;
}

void insert_n(int n, NODE *head)
{
	NODE *aNode = makeNode(n);
	NODE *flow = head;
	while(1)
	{
		if(flow->nextNode !=0)
		{
			if( n > flow->nextNode->n)
			{
				flow = flow->nextNode;
			}
			else
				break;
		}
		else
			break;
	}	
	insert(flow, flow->nextNode ,aNode);
}

void find(int n, NODE *head)
{
	if(head->nextNode==NULL){
		printf("There was no entry like %d\n", n);
	}else{
		if(head->nextNode->n == n)
			printf("The entry %d found!\n", n);
		else
			find(n,head = head->nextNode);
	}
}
void delete(NODE *precedent)
{
	precedent->nextNode = precedent->nextNode->nextNode;
}

void delete_n(int n, NODE *head)
{
	if(head->nextNode==NULL){
		printf("No deletion happened for %d\n", n);
	}else{
		if(head->nextNode->n ==n)
		{
			delete(head);
			printf("Deletion happened for %d\n", n);
		}
		else
			delete_n(n, head=head->nextNode);
	}
}

void clean(NODE *head)
{
	head->nextNode = NULL;
}

int count(NODE *head)
{
	if(head->nextNode==NULL){
		return 0;
	}
	else{
		return(1+count(head->nextNode));
	}
}

void print(NODE *head)
{
	printf("Print Start\n");
	while(head->nextNode != 0)
	{
		printf("n : %d ", head->nextNode->n);
		head = head->nextNode;
	}
	printf("\nPrint Ended\n");
}

int main(void)
{
	NODE *head = (NODE*) malloc(sizeof(struct node));
	head->nextNode = NULL;
	char input[6]; int inputNum,i,match=0,casenum;
	char case1[7]="insert", case2[7]="delete", case3[6]="print",case4[6]="count",case5[6]="clean",case6[5]="quit";

	while(1)
	{
		printf("Write the command : insert, delete, print, count, clean, quit\n");
		printf("Command : ");
		scanf("%s",input);
		if(strcmp(input, case1) == 0)
			casenum = 1;
		else if(strcmp(input, case2) == 0)
			casenum = 2;
		else if(strcmp(input, case3) == 0)
			casenum = 3;
		else if(strcmp(input, case4) == 0)
			casenum = 4;
		else if(strcmp(input, case5) == 0)
			casenum = 5;
		else if(strcmp(input, case6) == 0)
			casenum = 6;
		else
			printf("%s is wrong input\n", input);
	
		switch(casenum)
		{
			case 1 :
				printf("Number for insert : ");
				scanf("%d",&inputNum);
				insert_n(inputNum, head);
				break;
			case 2 :
				printf("Number for deletion: ");
				scanf("%d",&inputNum);
				delete_n(inputNum, head);
				break;
			case 3 :
				print(head);
				break;
			case 4 :
				printf("Count number : %d\n", count(head));
				break;
			case 5 : 
				clean(head);
				printf("The list has been cleaned. ");
				break;
			case 6 :
				exit(0);
				break;
		}	
	}
}
