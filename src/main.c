#include <stdio.h>
#include <stdlib.h>   // pour EXIT_SUCCESS, EXIT_FAILURE
#include <string.h>   // pour strcmp
#include "func.h"

int main(int argc, char* argv[])
{
    func_opred();

    if (argc > 1) 
    {
        if (strcmp(argv[1], "-txt") == 0) versiontexte();
        if (strcmp(argv[1], "-gr")  == 0) versiongraphique();
    }
    else versionweb();

    return EXIT_SUCCESS;
}
