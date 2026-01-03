#ifndef FUNC_H
#define FUNC_H

// #define LOG "/var/log/apache2/access.log.1"
#define LOG "access_statique.log"

extern struct Data
{
    int n_rq;
};

int func_opred();
void versiontexte(void);
void versiongraphique(void);
void versionweb(void);

#endif // FUNC_H
