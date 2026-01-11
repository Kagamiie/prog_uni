#include "stats.h"

int main(int argc, char* argv[]) {
    Data data = {0};
    
    func_opred(&data);

    if (argc > 1) {
        if (strcmp(argv[1], "-txt") == 0) {
            versiontexte(&data);
        }
        if (strcmp(argv[1], "-gr") == 0) {
            versiongraphique(&data);
        }
    } else {
        versionweb(&data);
    }

    return EXIT_SUCCESS;
}