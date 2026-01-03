#include <stdio.h>
#include <stdlib.h>   // pour EXIT_SUCCESS, EXIT_FAILURE
#include "func.h"

struct Data g_data;

void versiontexte(void) {
    printf("Depuis le 01/Jan/2018 on a enregistre %d connexions.\n", g_data.n_rq);
}

void versiongraphique(void) {
    printf("Version graphique lancée\n");
}

void versionweb(void) {
    printf("Version web lancée\n");
}

int func_opred() {
    FILE *fp = fopen(LOG, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error: Cannot open file %s\n", LOG);
        return EXIT_FAILURE;
    }

    int num_requests = 0;
    int ch;
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n') num_requests++;
    }

    if (ferror(fp)) {
        fprintf(stderr, "Error reading from %s\n", LOG);
        fclose(fp);
        return EXIT_FAILURE;
    }

    g_data.n_rq = num_requests;

    printf("N: %d\n", g_data.n_rq);

    fclose(fp);
    return EXIT_SUCCESS;
}