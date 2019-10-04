#include <iostream>
#include <fstream>

using namespace std;

int main() {
    fstream in("graf.in");

    int no_nodes;
    in >> no_nodes;

    int graduri[no_nodes];

    for (int i = 0; i < no_nodes; i++) {
        graduri[i] = 0;
    }

    int value;
    for (int i = 0; i < no_nodes; i++) {
        for (int j = 0; j < no_nodes; j++) {
            in >> value;
            if (value == 1) {
                graduri[i]++;
                graduri[j]++;
            }
        }
    }

    bool regulat = true;
    int grad_prim = graduri[0];
    for (int i = 0; i < no_nodes; i++) {
        if (graduri[i] != grad_prim) {
            regulat = false;
        }
    }

    if (regulat) {
        cout << "Graful este regulat.\n";
    } else {
        cout << "Graful nu este regulat." << "\n";
    }

    return 0;
}
