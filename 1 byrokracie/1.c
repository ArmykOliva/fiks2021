#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE* filePointer;
    int bufferLength = 255;
    char buffer[bufferLength];

    filePointer = fopen("input1.txt", "r");
    
    //pocet uloh
    int pocet_uloh = atoi(fgets(buffer, bufferLength, filePointer));
    printf("pocet uloh: %d\n",pocet_uloh);

    int zadani[pocet_uloh+1][2000][2];

    //loop through all ulohy and get zadani
    for (int j = 0; j < pocet_uloh; j++) {
        //get specs of uloha
        fgets(buffer, bufferLength, filePointer);
        char *token = strtok(buffer," ");
        const int spec_size = 3;
        int specs[spec_size];
        for (int i = 0; i < spec_size; i++) {
            specs[i] = atoi(token);
            token = strtok(NULL," ");
        }
        int P = specs[0];
        int Z = specs[1];
        int n = specs[2];
        zadani[j][0][0] = Z;
        zadani[j][0][1] = n;

        //get smluvni podminky 
        for (int i = 1; i < Z+1; i++) {
            fgets(buffer, bufferLength, filePointer);
            char *token = strtok(buffer," ");
            zadani[j][i][0] = atoi(token);
            token = strtok(NULL," ");
            zadani[j][i][1] = atoi(token);
            token = strtok(NULL," ");
        }
    }
    fclose(filePointer);

    //debug
    for (int i = 0; i < pocet_uloh; i++) {
        //printf("uloha %d\n",i);
        for (int x = 1; x <= zadani[i][0][0]; x++) {
            for (int y = 0; y < 2; y++) {
                //printf("%d ",zadani[i][x][y]);
            }
            //printf("\n");
        }
    }

    //get vysledky
    int vysledky[pocet_uloh];
    for (int i = 0; i < pocet_uloh; i++) {
        printf("vysledek %d\n",i);
        int l1[] = { zadani[i][0][1] };
        int l2[] = {};

        if (zadani[i][0][0] == 1) { vysledky[i] = l1; }

    }

    //debug
    for (int i = 0; i < pocet_uloh; i++) { 
        printf("%d\n",vysledky[i]);
    }
}