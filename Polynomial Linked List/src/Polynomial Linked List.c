/*
 ============================================================================
 Name        : Polynomial.c
 Author      : Somshubra Majumdar
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int power, coefficient;
	struct Node *next;
}Node;

int main(void) {

	int choice = -1, power, coefficient;
	Node *p = NULL, *q = NULL, *r = NULL;

	void createPoly(Node **, int coeff, int pow);
	Node* addPoly(Node *, Node *);
	Node* multiplyPoly(Node*, Node*);
	void displayPoly(Node *);
	void listDestructor(Node **);

	setbuf(stdout, NULL);

	printf("Enter choice : \n1 for add to 1st polynomial\n2 for add to 2nd polynomial\n3 for calculate polynomial\n4 for display polynomial representation\n5 to multiply poly\n6 to delete all poly\n");

	do{
		printf("Enter choice : ");
		scanf("%d", &choice);

		switch (choice) {
			case 1:
				//Add to first polynomial
				printf("Enter a coefficient and power\n");
				scanf("%d%d", &coefficient, &power);

				createPoly(&p, coefficient, power);

				break;

			case 2:
				//Add to second polynomial

				printf("Enter a coefficient and power\n");
				scanf("%d%d", &coefficient, &power);

				createPoly(&q, coefficient, power);

				break;

			case 3:
				//Calculate Polynomial

				//r = mergeSortPoly(p, q);

				r = addPoly(p, q);


				break;

			case 4:
				//Display Polynomial

				displayPoly(p);
				displayPoly(q);
				displayPoly(r);

				break;
			case 5:{
				//Multiply 2 poly

				r = multiplyPoly(p, q);

				break;
			}
			case 6:{

				listDestructor(&p);
				listDestructor(&q);
				listDestructor(&r);

				break;
			}
			default:{
				choice = -1;
			}

		}

	}while(choice != -1);

	listDestructor(&p);
	listDestructor(&q);
	listDestructor(&r);

	printf("End");

	return EXIT_SUCCESS;
}

void createPoly(Node **p, int coeff, int pow){

	Node *temp = *p, *previous;

	while(temp != NULL){
		if(temp->power <= pow){
			break;
		}

		previous = temp;
		temp = temp->next;
	}

	if(temp == NULL || temp->power != pow){
		Node *newNode = NULL;
		newNode = (Node*) calloc(1, sizeof(Node));
		newNode->coefficient = coeff;
		newNode->power = pow;

		if(*p == temp){
			newNode->next = *p;
			*p = newNode;
		}
		else{
			newNode->next = previous->next;
			previous->next = newNode;
		}

	}
	else{
		temp->coefficient += coeff;
	}

}

Node* addPoly(Node *p, Node *q){

	Node *result = NULL;

	while(p != NULL){

		createPoly(&result, p->coefficient, p->power);
		p = p->next;

	}

	while(q != NULL){

		createPoly(&result, q->coefficient, q->power);
		q = q->next;

	}

	return result;

}

Node* multiplyPoly(Node *p, Node *q){

	Node *t = q;
	Node *result = NULL;

	while(p != NULL){

		while(q != NULL){

			createPoly(&result, p->coefficient * q->coefficient, p->power + q->power);
			q = q->next;

		}

		p = p->next;
		q = t;

	}

	return result;

}


Node* mergeSortAddPoly(Node *p, Node *q){

	Node *r = NULL;
	Node *t;

	while(p != NULL || q != NULL){

		if(p != NULL && q != NULL){

			if(r == NULL){
				r = (Node*) calloc(1, sizeof(Node));
				t = r;

			}
			else{
				r->next = (Node*) calloc(1, sizeof(Node));
				r = r->next;
			}

			if(p->power < q->power){

				r->power = p->power;
				r->coefficient = p->coefficient;
				p = p->next;

			}
			else if(p->power == q->power){

				r->power = p->power;
				r->coefficient = p->coefficient + q->coefficient;
				p = p->next;
				q = q->next;
			}
			else{

				r->power = q->power;
				r->coefficient = q->coefficient;
				q = q->next;

			}


		}
		else if(p != NULL){

			while(p != NULL){

				r->next = (Node*) calloc(1, sizeof(Node));
				r = r->next;
				r->next = NULL;

				r->power = p->power;
				r->coefficient = p->coefficient;
				p = p->next;

			}
		}
		else if(q != NULL){

			while(q != NULL){
				r->next = (Node*) calloc(1, sizeof(Node));
				r = r->next;
				r->next = NULL;

				r->power = q->power;
				r->coefficient = q->coefficient;
				q = q->next;

			}

		}

	}

	r->next = NULL;

	return t;
}


Node* mergeSortSubtractPoly(Node *p, Node *q){

	Node *r = NULL;
	Node *t;

	while(p != NULL || q != NULL){

		if(p != NULL && q != NULL){

			if(r == NULL){
				r = (Node*) calloc(1, sizeof(Node));
				t = r;

			}
			else{
				r->next = (Node*) calloc(1, sizeof(Node));
				r = r->next;
			}

			if(p->power < q->power){

				r->power = p->power;
				r->coefficient = p->coefficient;
				p = p->next;

			}
			else if(p->power == q->power){

				r->power = p->power;
				r->coefficient = p->coefficient - q->coefficient;
				p = p->next;
				q = q->next;
			}
			else{

				r->power = -q->power;
				r->coefficient = -q->coefficient;
				q = q->next;

			}


		}
		else if(p != NULL){

			while(p != NULL){

				r->next = (Node*) calloc(1, sizeof(Node));
				r = r->next;
				r->next = NULL;

				r->power = p->power;
				r->coefficient = p->coefficient;
				p = p->next;

			}
		}
		else if(q != NULL){

			while(q != NULL){
				r->next = (Node*) calloc(1, sizeof(Node));
				r = r->next;
				r->next = NULL;

				r->power = -q->power;
				r->coefficient = -q->coefficient;
				q = q->next;
			}
		}

	}

	r->next = NULL;

	return t;
}




/*Node* mergeSortMultiplyPoly(Node *p, Node *q){
	Node *r = NULL;
	Node *t;

	Node *result = NULL;

	while(p != NULL){

		while(q != NULL){
			createPoly(&result, p->coefficient * q->coefficient, p->power + q->power);
			q = q->next;

		}

		p = p->next;
		q = t;

	}

	p = result;
	q = result +

	while(p != NULL || q != NULL){

		if(p != NULL && q != NULL){

			if(r == NULL){
				r = (Node*) calloc(1, sizeof(Node));
				t = r;

			}
			else{
				r->next = (Node*) calloc(1, sizeof(Node));
				r = r->next;
			}

			if(p->power < q->power){

				r->power = p->power;
				r->coefficient = p->coefficient;
				p = p->next;

			}
			else if(p->power == q->power){

				r->power = p->power + q->power;
				r->coefficient = p->coefficient * q->coefficient;
				p = p->next;
				q = q->next;
			}
			else{

				r->power = q->power;
				r->coefficient = q->coefficient;
				q = q->next;

			}


		}
		else if(p != NULL){

			while(p != NULL){

				r->next = (Node*) calloc(1, sizeof(Node));
				r = r->next;
				r->next = NULL;

				r->power = p->power;
				r->coefficient = p->coefficient;
				p = p->next;

			}
		}
		else if(q != NULL){

			r->next = (Node*) calloc(1, sizeof(Node));
			r = r->next;
			r->next = NULL;

			r->power = q->power;
			r->coefficient = q->coefficient;
			q = q->next;

		}

	}

	r->next = NULL;

	return t;
}
*/


void displayPoly(Node *p){

	while(p != NULL){

		if(p->power == 0){
			printf("%d",p->coefficient);
		}
		else{
			printf("%dx^%d",p->coefficient,p->power);
		}

		p = p->next;

		if(p != NULL)
			printf(" + ");

	}

	printf("\n");

}


void listDestructor(Node **p){

	Node *next;

	while(*p != NULL){
		next = (*p)->next;
		free(*p);
		(*p) = next;
	}

	free(p);

}


