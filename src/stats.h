#ifndef STATS_H
#define STATS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgraphique.h>

#define LOG "/var/log/apache2/access.log"

typedef struct {
    int n_rq;
    int monthly[12];
    int first_day;
    int first_month;
    int first_year;
    int has_first_date;
} Data;

extern const char *months_abbrev[];
extern const char *months_full[];

int extract_date(const char *s, Data *data);
void func_opred(Data *data);
void lecture_style(void);
void versiontexte(Data *data);
void versiongraphique(Data *data);
void versionweb(Data *data);

#endif