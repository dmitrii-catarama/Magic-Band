/*CATARAMA DMITRII 313CD*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "banda.h"

int main() {
    Banda *banda = createBanda();  // cream banda magica
    FILE* tema = fopen("tema1.in", "rt");  // deschidem fisierul de input
    FILE* output = fopen("tema1.out", "w");
    // vectorul unde va fi stocata comanda scoasa la momentul de citire
    T buffer[20] = {0};
    Queue* coadaCuComenzi = createQueue();  // cream coada cu comenzi
    Stack* Undo = createStackUR();
    Stack* Redo = createStackUR();
    BandaNode* temp = NULL;

    if (tema == NULL) {  // daca fisierul de input nu se poate deschide
        printf("Error: unable to open the file\n");
        return -1;
    }

    /* comparam comanda stocata in "buffer" cu stringurile din functiile if
        pentru a apela functia necesara */
    while (fscanf(tema, "%[^\n] ", buffer) == 1) {
        T *str = strdup(buffer);

        if (!strcmp(buffer, "MOVE_RIGHT"))
            coadaCuComenzi = equeue(coadaCuComenzi, str);

        else if (!strcmp(buffer, "MOVE_LEFT"))
            coadaCuComenzi = equeue(coadaCuComenzi, str);

        else if (!strncmp(buffer, "MOVE_LEFT_CHAR", strlen("MOVE_LEFT_CHAR")))
            coadaCuComenzi = equeue(coadaCuComenzi, str);

        else if (!strncmp(buffer, "MOVE_RIGHT_CHAR", strlen("MOVE_RIGHT_CHAR")))
            coadaCuComenzi = equeue(coadaCuComenzi, str);

        else if (!strncmp(buffer, "INSERT_LEFT", strlen("INSERT_LEFT")))
            coadaCuComenzi = equeue(coadaCuComenzi, str);

        else if (!strncmp(buffer, "INSERT_RIGHT", strlen("INSERT_RIGHT")))
            coadaCuComenzi = equeue(coadaCuComenzi, str);

        else if (!strncmp(buffer, "WRITE", strlen("WRITE"))) {
            coadaCuComenzi = equeue(coadaCuComenzi, str);
            destroyNodesUR(Undo);
            destroyNodesUR(Redo);
        } else if (!strcmp(buffer, "EXECUTE")) {
            temp = execute(banda, coadaCuComenzi, output);
            if (temp != NULL)
                Undo = pushUR(Undo, temp);
            coadaCuComenzi = dequeue(coadaCuComenzi);
            free(str);
        } else if (!strcmp(buffer, "UNDO")) {
            temp = topUR(Undo);
            Redo = pushUR(Redo, returnDegetul(banda));
            banda->degetul = temp;
            Undo = popUR(Undo);
            free(str);
        } else if (!strcmp(buffer, "REDO")) {
            Undo = pushUR(Undo, returnDegetul(banda));
            temp = topUR(Redo);
            banda->degetul = temp;
            Redo = popUR(Redo);
            free(str);
        } else if (!strcmp(buffer, "SHOW")) {
            show(banda, output);
            free(str);
        } else if (!strcmp(buffer, "SHOW_CURRENT")) {
            showCurrent(banda, output);
            free(str);
        } else free(str);
    }

    fclose(tema);
    fclose(output);
    destroyBanda(banda);
    destroyQueue(coadaCuComenzi);
    destroyStackUR(Undo);
    destroyStackUR(Redo);

return 0;
}
