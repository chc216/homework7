#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;	//노드 구조체 선언



typedef struct Head {
	struct Node* first;
}headNode;	//헤드를 가리킬 구조체 선언

int initialize(headNode** h);
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	printf("[-----[최 현 철]	[2022078014]-----]"); //학번, 이름 출력

	do{	//커맨드에 따라 호출 함수를 달리한다.
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);	//headnode의 값을 변경하기 위해 headnode의 주소를 인수로 전달한다.
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (headNode*)malloc(sizeof(headNode)); //리스트를 가리킬 headnode포인터에 headNode의 메모리 공간을 할당받아 주소를 저장한다.
	//포인터 headnode@main의 값을 변경하므로 매개변수를 이중 포인터로 선언했다.
	(*h)->first = NULL;	//headnode의 first에 null값을 저장한다.
	//h->headnode->headnode.fisrt = null인 상황이다.
	return 1;
}

int freeList(headNode* h){
	listNode* p = h->first;	//리스트를 가리킬 포인터 p선언

	listNode* prev = NULL;	//p의 이전 노드를 가리킬 포인터 prev선언
	while(p != NULL) {		//p가 마지막 NULL값을 가리킬 때 까지 반복한다.
		prev = p;			//prev가 p의 뒤를 따라간다.
		p = p->rlink;		//포인터 p 오른쪽 한 칸 이동
		free(prev);			//prev가 가리키는 노드 할당 해제
	}
	free(h);				//마지막으로 리스트를 가리켰던 헤드포인터를 할당 해제한다.
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {		//리스트가 존재하지 않을 경우
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;		//p가 리스트를 가리키도록 한다.

	while(p != NULL) {	//리스트 전체를 돌며 key값을 출력한다.
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;	//리스트 노드 갯수 카운트
	}

	printf("  items = %d\n", i);	//리스트의 노드 갯수 출력
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listnode에 대한 공간을 할당 받아 포인터 node에 리턴
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;	//node가 가리키는 listnode에 키 값을 집어넣고 각 포인터 필드엔 null값을 집어넣는다.

	if (h->first == NULL)	//headnode가 가리키는 리스트가 없다면 headnode가 node를 가리키도록 한다.
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first; 
	while(n->rlink != NULL) { //포인터 n이 리스트를 가리키도록 하고 포인터 n이 리스트의 마지막 노드를 가리킬 때 까지 이동시킨다.
		n = n->rlink;
	}
	n->rlink = node;	//마지막 노드의 rlink가 node를 가리키도록 한다.
	node->llink = n;	//node의 llink가 n이 가리키는 노드를 가리키도록 한다.(마지막 노드와 node 양방향 연결)
	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	if (h->first == NULL)	//리스트가 존재하지 않음
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;	//포인터 n이 리스트를 가리키도록 한다.
	listNode* trail = NULL;	//양방향 연결을 끊기 위해 포인터 n을 뒤따라 올 포인터 trail을 선언한다.

	
	if(n->rlink == NULL) { //리스트의 첫 노드의 오른쪽 링크가 비었을 경우, 즉 노드가 하나만 있는 경우
		h->first = NULL;	//헤드포인터와 리스트의 연결 해제
		free(n);	//n이 가리키고 있는 노드(유일한 노드)를 할당 해제한다.
		return 0;
	}

	
	while(n->rlink != NULL) {	//n이 가리키는 노드가 마지막 노드일 때 까지 옮긴다.
		trail = n;		
		n = n->rlink;
	}

	
	trail->rlink = NULL; 	//마지막 노드와 이전 노드의 링크를 끊는다.
	free(n);	//마지막 노드의 할당을 해제한다.

	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));	//listnode에 대한 공간을 할당 받아 포인터 node에 리턴
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	if(h->first == NULL)	//리스트가 존재하지 않을 때
	{
		h->first = node;	//노드를 헤드노드와 연결한다.
		return 1;
	}

	node->rlink = h->first;	//노드의 오른쪽 링크가 원래 리스트의 첫번째 노드를 가리키도록 한다.
	node->llink = NULL;	//노드의 왼쪽 링크는 NULL값을 가리켜 더 이상 이동하지 못하도록 한다.

	listNode *p = h->first;	//node를 가리킬 포인터 p선언
	p->llink = node;		//노드의 왼쪽 링크가 자신을 가리키도록 한다.
	h->first = node;		//헤드가 노드를 가리키도록 한다.

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL)	//리스트가 존재하지 않는 경우
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first;	//리스트를 가리킨 포인터 n 선언
	h->first = n->rlink;	//헤드가 두번째 노드를 가리키도록 한다.

	free(n); //삭제할 노드 할당 해제

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {


	if(h->first == NULL) { 	//리스트가 없을 경우
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;	//리스트를 가리키는 포인터 N
	listNode *trail = NULL;	
	listNode *middle = NULL;

	while(n != NULL){	//n이 마지막 노드를 가리킬 때 까지 반복
		trail = middle;	//
		middle = n;		//middle포인터는 포인터 n을 뒤따라 간다
		n = n->rlink;	//포인터 n 오른쪽 이동
		middle->rlink = trail;	//middle이 가리키는 노드의 왼쪽 오른쪽을 각각 N,trail이 가리키는 노드로 연결한다 -->한칸씩 역순으로 연결해나간다.
		middle->llink = n;
	}

	h->first = middle;	//최종적으로 헤드포인터가 마지막 노드를 가리키도록 한다.

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));	//listnode에 대한 공간을 할당 받아 포인터 node에 리턴
	node->key = key;
	node->llink = node->rlink = NULL;

	if (h->first == NULL)	//리스트가 존재하지 않을 때
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;	//리스트를 가리킬 포인터 n선언

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {		//포인터 n이 마지막 노드를 가리킬 때 까지 반복
		if(n->key >= key) {	//가리키는 노드의 key가 삽입할 key보다 크면 바로 이전에 삽입
			if(n == h->first) {	//가리키는 노드가 첫 노드일 경우
				insertFirst(h, key);	//함수 호출
			} else { 		//삽입할 위치가 처음이 아니면
				node->rlink = n;		//노드의 오른쪽 링크를 n이 가리키는 노드로 연결
				node->llink = n->llink;	//n이 가리키는 노드의 이전 노드를 node의 llink에 연결
				n->llink->rlink = node;	//이전 노드가 node를 가리키도록 한다. ==> 양방향 연결이 된다.
			}
			return 0;
		}

		n = n->rlink;
	}

	insertLast(h, key);	//n이 마지막까지 검사했을 경우 마지막에 삽입하는 함수 호출
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL)	//리스트가 존재하지 않을 때
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* n = h->first;	//리스트를 가리킬 노드 N 선언

	while(n != NULL) {		//n이 마지막 NULL을 가리킬 때 까지 검사한다
		if(n->key == key) {	//삭제할 Key값과 일치할 때
			if(n == h->first) { 	//삭제할 노드가 첫번째 노드라면
				deleteFirst(h);		//함수 호출
			} else if (n->rlink == NULL){ 	//삭제할 노드가 마지막 노드라면
				deleteLast(h);				//함수 호출
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink;	//그렇지 않으면 n의 왼쪽 노드가 n의 오른쪽 노드를 가리키도록한다.
				n->rlink->llink = n->llink;	//n의 오른쪽 노드가 n의 왼쪽 노드를 가리키도록 한다.	--> 연결을 끊는다.
				free(n);	//삭제할 노드 할당 해제
			}
			return 1;
		}

		n = n->rlink;
	}

	printf("cannot find the node for key = %d\n", key);	//값을 찾지 못한 경우
	return 1;
}


