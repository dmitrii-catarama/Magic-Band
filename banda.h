#ifndef BANDA_MAGICA_H
#define BANDA_MAGICA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char T;
typedef char* D;  // pentru stringuri/comenzi

typedef struct BandaNode {  // structura de definire a unui nod din banda magica
    T elem;
    struct BandaNode* next;
    struct BandaNode* prev;
} BandaNode;

typedef struct Banda {  // structura de definire banda magica
    BandaNode* sentinel;
    BandaNode* last;
    BandaNode* degetul;
} Banda;


BandaNode *createNode(T elem) {  // functia de creare a unui nod nou in lista
    BandaNode *newNode = malloc(sizeof(BandaNode));
    newNode->elem = elem;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}


Banda *createBanda() {  // functia de initializare a benzii
    // alocam memorie pentru banda
    Banda *banda = malloc (sizeof(struct Banda));
    banda->sentinel = createNode('\0');
    banda->last = createNode('#');  // ultimul nod care contine elementul '#'
    banda->sentinel->next = banda->last;
    banda->last->prev = banda->sentinel;
    banda->degetul = banda->last;

    return banda;
}

    // functia ce returneaza adresa degetului
    BandaNode *returnDegetul(Banda* banda) {
        return banda->degetul;
    return NULL;
}
// functia de dealocare a memoriei ocupata de banda
Banda *destroyBanda(Banda* banda) {
    if (banda == NULL) {
        return banda;
    }
    BandaNode *iter = NULL, *temp = NULL;  // variabile de ajutor
    iter = banda->sentinel->next;
    while (iter != NULL) {
        iter->elem = '\0';
        temp = iter;
        iter = iter->next;
        free(temp);  // eliberam memoria iteratorului
    }

    free(banda->sentinel);  // eliberam memoria santinelei
    free(banda);  // eliberam memoria bandei magice
    return NULL;
}

//--------------- Operatii de tip UPDATE ---------------------------

int moveLeft(Banda* banda) {  // functia de mutare a degetului la stanga
    if (banda->degetul->prev == banda->sentinel)
        return 1;

    banda->degetul = banda->degetul->prev;
    return 0;
}

void moveRight(Banda* banda) {  // functia de mutare a degetului la dreapta
    if (banda->degetul == banda->last) {
        banda->degetul->next = createNode('#');
        banda->degetul = banda->degetul->next;
        banda->degetul->prev = banda->last;
        banda->last = banda->degetul;
        banda->last->prev = banda->degetul->prev;
        return;
    }

    banda->degetul = banda->degetul->next;
}

// deplasarea in stanga pana la primul caracter egal cu un anumit simbol
void moveLeftChar(Banda* banda, T elem, FILE* output) {
    BandaNode* iter = banda->degetul;

    while (banda->degetul->prev != banda->sentinel && banda->degetul->elem != elem) {
        banda->degetul = banda->degetul->prev;
    }
    if (banda->degetul->elem == elem) {
        return;
    } else {
        fprintf(output, "ERROR\n");
        banda->degetul = iter;
    }
}
// deplasarea in dreapta pana la primul caracter egal cu un anumit simbol
void moveRightChar(Banda* banda, T elem) {
    while (banda->degetul->next != NULL && banda->degetul->elem != elem) {
        banda->degetul = banda->degetul->next;
    }

    if (banda->degetul->elem == elem)
        return;

    banda->degetul->next = createNode('#');
    banda->last = banda->degetul->next;
    banda->last->prev = banda->degetul;
    banda->degetul = banda->last;
}
// actualizeaza caracterul de pe pozitia degetului
int Write(Banda* banda, T elem) {
    banda->degetul->elem = elem;
    return 0;
}
// inserarea in stanga degetului
void insertLeftC(Banda* banda, T elem, FILE* output) {
    if (banda->degetul->prev == banda->sentinel) {
        fprintf(output, "ERROR\n");
    } else {
        // cream un nou nod cu elementul dat
        BandaNode* insertNew = createNode(elem);
        // cream un auxuliar de ajutor
        BandaNode* aux = banda->degetul->prev;
        aux->next = insertNew;
        insertNew->prev = aux;
        insertNew->next = banda->degetul;
        banda->degetul->prev = insertNew;
        banda->degetul = insertNew;
    }
}

void insertRightC(Banda* banda, T elem) {  // inserarea in dreapta degetului
    if (banda->degetul == banda->last) {
        banda->degetul->next = createNode(elem);
        banda->last = banda->degetul->next;
        banda->last->prev = banda->degetul;
        banda->degetul = banda->last;
        banda->degetul->prev = banda->last->prev;
        return;
    }
        // nod de ajutor
        BandaNode* aux = banda->degetul->next;
        BandaNode* insertNew = createNode(elem);
        // legatura de la nod nou la elementul deget->next
        insertNew->next = banda->degetul->next;
        // legatura de la elementul deget->next la nodul nou
        aux->prev = insertNew;
        // legatura de la deget la nodul nou
        banda->degetul->next = insertNew;
        // legatura de la insertNew->prev la deget
        insertNew->prev = banda->degetul;
        // am pus degetul la elementul nou creat
        banda->degetul = insertNew;
}

// ------------------------ Operatii de tip QUERY --------------------

void showCurrent(Banda* banda , FILE* output) {
    // afisam elementul de pe pozitia degetului
    fprintf(output, "%c\n", banda->degetul->elem);
}

void show(Banda* banda, FILE* output) {  // functie de afisare a listei
    if (banda->sentinel->next == banda->last) {
        fprintf(output, "|%c|\n", banda->degetul->elem);
        return;
    }
    BandaNode* iter = banda->sentinel->next;
    while (iter != NULL) {
        if (iter == banda->degetul) {
            fprintf(output, "|%c|", iter->elem);
            iter = iter->next;
        } else {
        fprintf(output, "%c", iter->elem);
        iter = iter->next;
        }
    }
    fprintf(output, "\n");
}

// ------------------------ Coada Cu Comenzi --------------------------

typedef struct qnode {  // structura nodului din coada
    D data;
    struct qnode* next;
} Qnode;

typedef struct queue {  // structura cozii
    Qnode *front;
    Qnode *rear;
} Queue;

Qnode* createQnode(D data) {  // functia de creare a unui nou nod in coada
    Qnode* newQnode = malloc(sizeof(Qnode));
    newQnode->next = NULL;
    newQnode->data = data;
    return newQnode;
}

Queue* createQueue() {  // functia de creare a cozii
    Queue* newQ = malloc(sizeof(Queue));
    newQ->front = NULL;
    newQ->rear = NULL;

    return newQ;
}

int queEmpty(Queue* q) {  // functia de verificare daca coada e vida
    if (q->front == NULL || q == NULL)
        return 1;
    
    return 0;
}

// functia de introducere a noului element in coada
Queue* equeue(Queue* q, D data) {
    Qnode* newNode = createQnode(data);
	if (q == NULL)
        return NULL;

    if (queEmpty(q)) {
        q->front = newNode;
        q->rear = newNode;
        return q;
    }

    q->rear->next = newNode;
    q->rear = newNode;
    return q;
}

Queue* dequeue(Queue* q) {  // functia de extragere a elementului din coada
    if (queEmpty(q))
        return q;

    if (!queEmpty(q)) {
        Qnode* aux = q->front;
        q->front = q->front->next;
        if (q->front == NULL) {
            q->rear = NULL;
        }
        free(aux->data);
        free(aux);
    }
    return q;
}

D front(Queue* q) {  // functia de afisare a primului element din coada
    if (!queEmpty(q)) {
        return q->front->data;
    } else 
        exit(1);
}

Queue* destroyQueue(Queue* q) {  // functia de dealocare a memoriei ocupate de coada
    while (!queEmpty(q)) {
        q = dequeue(q);
    }
    free(q);

    return NULL;
}

// --------------- Stiva pentru operatii de tip UNDO/REDO --------------------

typedef struct SNode {  // structura pentru un nod din stiva undo
    BandaNode* elem;
    struct SNode *next;
} SNode;

typedef struct Stack {  // strucura pentru stiva
    SNode* head;  // Varful stivei
} Stack;

Stack* createStackUR(void) {  // functia de creare a stivei
    Stack* stiva = malloc(sizeof(Stack));
    stiva->head = NULL;

    return stiva;
}

SNode* createNodeUR(BandaNode* elem) {  // functia de creare a nodului
    SNode* newNode = malloc(sizeof(SNode));
    newNode->next = NULL;
    newNode->elem = elem;
    return newNode;
}


int isStackEmptyUR(Stack* stack) {  // verificare daca stiva e goala
    if (stack == NULL || stack->head == NULL)
        return 1;
    return 0;
}

Stack* pushUR(Stack* stack, BandaNode* elem) {  // adaugarea noului nod in stiva
    if (isStackEmptyUR(stack)) {
        stack->head = createNodeUR(elem);
        return stack;
    }

    SNode* iter = NULL;
    iter = createNodeUR(elem);

    iter->next = stack->head;
    stack->head = iter;
    return stack;
}

BandaNode* topUR(Stack *stack) {  // returnam elementul head din stiva
    return stack->head->elem;
}

Stack* popUR(Stack *stack) {  // extrage elementul head din stiva
    if (isStackEmptyUR(stack))
        return stack;
    SNode* aux = stack->head;
    stack->head = stack->head->next;
    free(aux);
    return stack;
}

Stack* destroyNodesUR(Stack *stack) {  // distrugem toate elementele stivei
    while (!isStackEmptyUR(stack)) {
        stack = popUR(stack);
    }
    return stack;
}

void destroyStackUR(Stack *stack) {  // dealocam memorie pentru stiva
    stack = destroyNodesUR(stack);
    if (stack) {
        free(stack);
        return;
    }
}

// ---------------------- Functia pentru EXECUTE ----------------------

// functia de executare
BandaNode* execute(Banda* banda, Queue* q, FILE* output) {
    T *str = front(q);
    BandaNode* pozDeget = NULL;
    int mlc = strlen("MOVE_LEFT_CHAR");
    int mrc = strlen("MOVE_RIGHT_CHAR");
    int ilc = strlen("INSERT_LEFT");
    int irc = strlen("INSERT_RIGHT");
    int write = strlen("WRITE");

    if (!strcmp(str, "MOVE_RIGHT")) {
        pozDeget = returnDegetul(banda);
        moveRight(banda);
        return pozDeget;
    } else if (!strcmp(str, "MOVE_LEFT")) {
        pozDeget = returnDegetul(banda);
        if (!moveLeft(banda))
            return pozDeget;
        return NULL;
    } else if (!strncmp(str, "MOVE_LEFT_CHAR", mlc)) {
        moveLeftChar(banda, str[mlc + 1], output);
    } else if (!strncmp(str, "MOVE_RIGHT_CHAR", mrc)) {
        moveRightChar(banda, str[mrc + 1]);
    } else if (!strncmp(str, "INSERT_LEFT", ilc)) {
        insertLeftC(banda, str[ilc + 1], output);
    } else if (!strncmp(str, "INSERT_RIGHT", irc)) {
        insertRightC(banda, str[irc + 1]);
    } else if (!strncmp(str, "WRITE", write)) {
        Write(banda, str[write + 1]);
    }

    return NULL;
}


#endif  // BANDA_MAGICA_H
