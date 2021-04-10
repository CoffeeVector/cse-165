#include <iostream>
#include "Tetris.h"

using namespace std;

int main() {
    Tetris t(4, 4, 10);
    t.spawn_piece();
    t.print();
    while (true) {
        t.advance();
        cout << endl;
        t.print();
    }
}
