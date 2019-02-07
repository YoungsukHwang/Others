#include<stdio.h>
#include<stdlib.h>

#define	MIN_X 50
#define	MAX_X 950
#define	MAX_BUILDINGS 100
#define	MAX_SKYLINES 1000
#define N 5

#define MAX(x,y) ((x)>(y) ? (x):(y))

struct Building{
	float height;
	float left, right;
} buildings[N];

typedef struct Skyline{
	int num;
	float height[MAX_SKYLINES];
	float x[MAX_SKYLINES+1];
} skyline;

void printSkyline( skyline *s )
{
	printf("[%d]", s->num);

	int i;
	for(i=0; i<s->num; i++)
		printf("%3.0f (%3.0f) ", s->x[i], s->height[i]);

	printf("%3.0f\n", s->x[i]);
}

skyline* addbuilding(skyline* s, struct Building b)
{
	skyline newsky;
	printf("Building : %3.0f %3.0f %3.0f \n", b.left, b.right, b.height); 
	
	int i=1, j=1, k=1;
	float h1=0, h2=0;
	
	skyline bsky;
	bsky.x[0]=MIN_X;
	bsky.x[1]=b.left;
	bsky.x[2]=b.right;
	bsky.x[3]=MAX_X;
	bsky.height[0]=0;
	bsky.height[1]=b.height;;
	bsky.height[2]=0;

	bsky.num = 3;

	newsky.x[0]=MIN_X;
	newsky.height[0]=0;	

	while(i < s->num && j< 3 )
	{
		if(s->x[i] < bsky.x[j])
		{
			newsky.x[k] = s->x[i];
			h1 = s->height[i];
			newsky.height[k] = MAX(h1,h2);
			i++,k++;
		}
		else
		{
			newsky.x[k] = bsky.x[j];
			h2 = bsky.height[j];
			newsky.height[k] = MAX(h1,h2);
			j++,k++;
		}
	}

	while(i < s->num)
	{
		newsky.x[k] = s->x[i];
		newsky.height[k] = s->height[i];
		i++,k++;
	}

	while(j<3)
	{
		newsky.x[k] = bsky.x[j];
		newsky.height[k] = bsky.height[j];
		k++,j++;
	}
	newsky.x[k]=MAX_X;
	newsky.height[k]=0;	
	newsky.num = k;

	s = &newsky;
	return s;
}


int main(void)
{
	int i;
	for(i=0;i<N;i++)
	{
		buildings[i].left = rand()%700+100;
		buildings[i].right = rand()%100 + 30 + buildings[i].left;
		buildings[i].height = rand()%300;
	}

	skyline s;
	
	s.x[0]=MIN_X;
	s.x[1]=MAX_X;
	s.height[0]=0;
	s.num = 2;

	skyline *p;
	for(i=0;i<N;i++)
	{
		p = addbuilding(&s,buildings[i]);
		s = *p;
	}
	printSkyline(&s);
	return 0;
}



