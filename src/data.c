#include "stats.h"

const char *months_abbrev[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                                "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

int extract_date(const char *s, Data *data) {
    char day_str[3], month_str[4], year_str[5];
    int day, year, month, m;
    char *start;
    
    start = strchr(s, '[');
    if (!start) return 0;
    
    if (sscanf(start + 1, "%2s/%3s/%4s", day_str, month_str, year_str) != 3)
        return 0;

    day = atoi(day_str);
    year = atoi(year_str);
    month = -1;
    
    for (m = 0; m < 12; m++) {
        if (strncmp(month_str, months_abbrev[m], 3) == 0) {
            month = m;
            break;
        }
    }
    
    if (month == -1) return 0;

    if (!data->has_first_date) {
        data->first_day = day;
        data->first_month = month;
        data->first_year = year;
        data->has_first_date = 1;
    }
    
    data->monthly[month]++;
    return 1;
}

void func_opred(Data *data) {
    char *buffer, *new_buffer;
    size_t buffer_size, position, new_size;
    FILE *fp;
    int c;
    
    fp = fopen(LOG, "r");
    if (!fp) {
        fprintf(stderr, "Erreur : Impossible d'ouvrir %s\n", LOG);
        return;
    }

    buffer_size = 2048;
    buffer = malloc(buffer_size);
    if (!buffer) {
        fprintf(stderr, "Erreur : Allocation mémoire\n");
        fclose(fp);
        return;
    }
    
    position = 0;
    
    while ((c = fgetc(fp)) != EOF) {
        if (position >= buffer_size - 1) {
            new_size = buffer_size * 2;
            new_buffer = realloc(buffer, new_size);
            
            if (!new_buffer) {
                fprintf(stderr, "Erreur : Réallocation mémoire\n");
                free(buffer);
                fclose(fp);
                return;
            }
            
            buffer = new_buffer;
            buffer_size = new_size;
        }
        
        buffer[position] = c;
        position++;
        
        if (c == '\n') {
            buffer[position - 1] = '\0';
            if (extract_date(buffer, data))
                data->n_rq++;
            position = 0;
        }
    }
    
    free(buffer);
    fclose(fp);
}