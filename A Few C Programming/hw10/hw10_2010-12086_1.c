#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char*        word;
    struct node* nextNode ;
} NODE;

NODE* makeNode(char* word){
    NODE * aNode = (NODE*)malloc(sizeof(struct node));
    memset(aNode, 0, sizeof(struct node));
    aNode->word = word;
    return aNode;
}

int isPosition(NODE* precedNode,NODE* aNode){
    int val1 = strcmp(precedNode->word, aNode->word);
    
    if (precedNode->nextNode) {
        int val2 = strcmp(precedNode->nextNode->word, aNode->word);
        if (val1 <= 0 & val2 > 0) {
            return 1;
        }else{
            return 0;
        }
    }else{
        return 1;
    }
}

void insertNode(NODE* precedent, NODE* aNode){
    aNode->nextNode = precedent->nextNode;
    precedent->nextNode = aNode;
}

void print(NODE* rootNode){
    NODE* currentNode = rootNode;
    
    while (1) {
        if (currentNode->nextNode) {
            printf("%s\n",currentNode->nextNode->word);
            currentNode=currentNode->nextNode;
        }else{
            break;
        }
    }
}

void histogram(NODE* rootNode){
    char* currentString = "";
    int count = 1;

    NODE* currentNode = rootNode->nextNode;
    
    while (1) {
        if (currentNode) {
            currentString = currentNode->word;
            if (!currentNode->nextNode || strcmp(currentString, currentNode->nextNode->word)!=0){
                printf("%s : %d\n",currentString,count);
                count=1;
                currentString=currentNode->word;
                
            }else{
                count++;
            }
            currentNode=currentNode->nextNode;
        }else{
            break;
        }
    }
}

int main(int argc, const char * argv[]) {
    
    NODE* rootNode = makeNode("");
    
    const char s[6] = ".,!? ";

    char c;
    int i=0;
    char text[3000];
    while((c=getchar())!=EOF)
    {
        text[i++] = c;
    }
    text[i] = '\0';
    
    char* token;
    
    token = strtok(text, s);
    while(token != NULL)
    {
        char * aString = token;
        
        NODE* insertionNode = makeNode(aString);
        NODE* currentNode=rootNode;
        while (1) {
            if (isPosition(currentNode, insertionNode)){
                insertNode(currentNode, insertionNode );
                break;
            }else{
                currentNode = currentNode->nextNode;
            }
        }
        token = strtok(NULL, s);
    }

    histogram(rootNode);

    return 0;
}