#include <iostream>
#include <set>
#include <memory.h>

using namespace std;
bool visited[30][30];

long long Go(int x, int y, int steps, int N) {
    // cout << x << "," << y << endl;
    if (steps == N) {
        return 1;
    }
    visited[x][y] = true;
    long long sum = 0;
    if (x > 0 && !visited[x-1][y]) {
        sum += Go(x-1, y, steps+1, N);
    }
    if (x < N && !visited[x+1][y]) {
        sum += Go(x+1, y, steps+1, N);
    }
    if (y > 0 && !visited[x][y-1]) {
        sum += Go(x, y-1, steps+1, N);
    }
    if (y < N && !visited[x][y+1]) {
        sum += Go(x, y+1, steps+1, N);
    }
    visited[x][y] = false;
    return sum;
}

long long solveProblem2 (int N) {
    // solve for [5,25]
    visited[0][0] = true;
    visited[1][0] = true;
    long long sum = Go(1, 0, 1, N);
    visited[0][0] = false;
    visited[1][0] = false;
    return sum;
}

int main () {
    for (int i = 15; i <= 25; i++) {
        memset(visited, 0, sizeof(visited));
        cout << i << "," << solveProblem2(i) << endl;
    }
    return 0;
}
