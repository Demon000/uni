#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_NODES 10000
#define INF 1<<28

int noduri, muchii;
int start, finish;

vector<int> vecini[MAX_NODES];
int capacitate[MAX_NODES][MAX_NODES];
int flux[MAX_NODES][MAX_NODES];

void citire() {
    fstream in("graf_flux.in");
    in >> noduri >> muchii;
    start = 0;
    finish = noduri - 1;

    int a, b, cap;
    for (int i = 0; i < muchii; i++) {
        in >> a >> b >> cap;

        a--;
        b--;

        vecini[a].push_back(b);
        vecini[b].push_back(a);
        cout << a << " " << b << "\n";
        capacitate[a][b] += cap;
    }
}

vector<int> noduri_dfs;
bool vizitate[MAX_NODES];

void dfs(int x) {
    if (x == finish) {
        noduri_dfs.push_back(finish);
        return;
    }

    for (int vecin : vecini[x]) {
        if (!vizitate[vecin] && capacitate[x][vecin] - flux[x][vecin] > 0) {
            vizitate[vecin] = true;
            dfs(vecin);

            if (noduri_dfs.size() > 0) {
                noduri_dfs.push_back(x);
                return;
            }
        }
    }
}

void undfs() {
    noduri_dfs.clear();
    for (int i = 0; i < noduri; i++) {
        vizitate[i] = false;
    }
}

/*
 * Algortimul de flux maxim poate fi utilizat, in viata reala, la modelarea unei reletele de transport
 * intre producator si consumator. Consumatorul nu poate consuma mai mult decat se produce,
 * iar producatorul nu poate trimite mai mult decat capacitatea de transport a retelei de drumuri.
 */
void rezolvare() {
    int total = 0;

    while (true) {
        undfs();
        dfs(start);

        if (!noduri_dfs.size()) {
            break;
        }

        reverse(noduri_dfs.begin(), noduri_dfs.end());

        int val = INF;
        int size = noduri_dfs.size() - 1;

        for (int i = 0; i < size; i++) {
            int x = noduri_dfs[i];
            int y = noduri_dfs[i + 1];

            val = min(capacitate[x][y] - flux[x][y], val);
        }

        for (int i = 0; i < size; i++) {
            int x = noduri_dfs[i];
            int y = noduri_dfs[i + 1];

            flux[x][y] += val;
            flux[y][x] -= val;
        }

        if (val == INF) {
            break;
        }

        total += val;
    }

    cout << total << "\n";
}

int main() {
    citire();
    rezolvare();

    return 0;
}
