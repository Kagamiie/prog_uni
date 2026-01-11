#include "stats.h"

const char *months_full[] = {"Janvier", "Fevrier", "Mars", "Avril", "Mai", "Juin",
                              "Juillet", "Aout", "Septembre", "Octobre", "Novembre", "Decembre"};

void lecture_style(void) {
    FILE *fd;
    char str[1024];
    
    fd = fopen("aecrire.html", "r");
    if (!fd) {
        fprintf(stderr, "ERREUR DE CHARGEMENT DE FICHIER\n");
        return;
    }
    
    while (fgets(str, 1024, fd)) {
        printf("%s", str);
    }
    
    fclose(fd);
}

void versiontexte(Data *data) {
    int m;
    int count;
    float percent;
    
    if (data->n_rq == 0) {
        printf("Aucune donnée à afficher.\n");
        return;
    }

    printf("Depuis le %02d/%s/%d on a enregistre %d connexions.\n", 
           data->first_day, 
           months_abbrev[data->first_month], 
           data->first_year, 
           data->n_rq);

    for (m = 0; m < 12; m++) {
        count = data->monthly[m];
        percent = (float)count * 100.0f / data->n_rq;
        printf("%10s : %4.1f%%\n", months_full[m], percent);
    }
}

void versiongraphique(Data *data) {
    int height, x_pos, y_pos;
    int m, count;
    char msg[256], label[4];
    float percent;
    Point p;

    if (data->n_rq == 0) {
        printf("Aucune donnée à afficher.\n");
        return;
    }
    
    ouvrir_fenetre(430, 350);
    dessiner_rectangle((Point){0, 0}, 430, 350, blanc);
    
    sprintf(msg, "Depuis le %02d/%s/%d on a enregistre %d connexions.",
            data->first_day, 
            months_abbrev[data->first_month], 
            data->first_year, 
            data->n_rq);
    
    p.x = 30;
    p.y = 50;
    afficher_texte(msg, 12, p, noir);
    
    p.y = 300;
    afficher_texte(" Jan  Fev  Mar  Avr  Mai  Juin  Juil  Aou  Sep  Oct  Nov  Dec", 14, p, vert);
    
    for (m = 0; m < 12; m++) {
        count = data->monthly[m];
        percent = (float)count * 100.0f / data->n_rq;
        height = (int)(percent * 10.0f);
        x_pos = 30 + (m * 31);
        y_pos = 300 - height;
        
        dessiner_rectangle((Point){x_pos, y_pos}, 30, height, orange);
        
        if (height >= 25) {
            sprintf(label, "%d", (int)(percent + 0.3f));
            afficher_texte(label, 14, (Point){x_pos + 8, y_pos + 8}, blanc);
        }
    }
    
    actualiser();
    attendre_clic();
    fermer_fenetre();
}

void versionweb(Data *data) {
    int height, left_pos;
    int m, count;
    float percent;
    
    printf("Content-type: text/html\n\n");
    printf("<!doctype html>\n");
    printf("<html lang=\"fr\">\n");
    printf("<body>\n");
    
    lecture_style();
    
    printf("<p>Depuis le %02d/%s/%d on a enregistr&eacute; %d connexions.</p>\n", 
           data->first_day, 
           months_abbrev[data->first_month], 
           data->first_year, 
           data->n_rq);

    if (data->n_rq == 0) {
        printf("Aucune donnée à afficher.\n");
        return;
    }
    
    printf("<div id=\"vertgraph\">\n");
    printf("<ul>\n");
    
    for (m = 0; m < 12; m++) {
        count = data->monthly[m];
        percent = (float)count * 100.0f / data->n_rq;
        height = (int)(percent * 10.0f);
        left_pos = 10 + (m * 31);
        
        if (height >= 25) {
            printf("<li style=\"left:%dpx;height:%dpx\" title=\"%s\">%d</li>\n",
                   left_pos, height, months_abbrev[m], (int)(percent + 0.3f));
        } else {
            printf("<li style=\"left:%dpx;height:%dpx\" title=\"%s\"></li>\n",
                   left_pos, height, months_abbrev[m]);
        }
    }
    
    printf("</ul>\n");
    printf("</div>\n");
    printf("</body>\n");
    printf("</html>\n");
}