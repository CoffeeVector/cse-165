#include <iostream>
#include "Tetris.h"

using namespace std;

void print(const Tetris& t) {
    for (int x = 0; x < t.w; x++) {
        for (int y = 0; y < t.l; y++) {
            for (int z = 0; z < t.h; z++) {
                if (t.state[x][y][z]) {
                    printf("(%d, %d, %d)\n", x, y, z);
                }
            }
        }
    }
}

int main() {
    Tetris t(4, 4, 10);
    t.spawn_piece();
    print(t);
    while (true) {
        t.advance();
        cout << endl;
        print(t);
    }
}
