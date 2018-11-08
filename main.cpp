#include <cstdio>

using namespace std;

int main() {
    int m[10][10][10] = {{{0}}};

    m[9][9][9] = 128;

    int x = (*(*(*(m + 9)+9)+9));
    printf("pointer: %d", x);
}