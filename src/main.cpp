#include <iostream>
#include <string>

#include "gists.h"

int main()
{
    Gists *g = new Gists();

    g->gistsApp();

    delete g;

    return 0;
}
