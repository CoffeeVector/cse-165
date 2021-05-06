#ifndef TETRIS_H
#define TETRIS_H
// I pretty much winged this whole thing, so expect lots of bugs. -KZ

#include <iostream>

enum Moves {
    DOWN, LEFT, RIGHT, FORWARD, BACK, PITCH, ROLL, YAW
};

struct Block {
    int r, g, b;
    bool falling;
};

enum GameState {
    PLAYING, LOSS
};

class Tetris {
    public:
    Block**** state; // state[x][y][z], where z is the falling direction. x and y is arbitrary.
    int w, l, h;

    Tetris(int w = 8, int l = 8, int h = 10) {
        this->w = w;
        this->l = l;
        this->h = h;
        // TODO: Aim to shorten this initialize-multidimensional-array-to-null code
        state = new Block***[w];
        for (int x = 0; x < w; x++) {
            state[x] = new Block**[l];
            for (int y = 0; y < l; y++) {
                state[x][y] = new Block*[h];
                for (int z = 0; z < h; z++) {
                    state[x][y][z] = NULL;
                }
            }
        }
    }

    int sub2ind(int x, int y, int z) {
        // Used for linear indexing; (x, y, z) -> i
        return x + w * y + w*l * z;
    }

    void ind2sub(int ind, int &x, int &y, int &z) {
        // For linear indexing: i -> (x, y, z)
        x = ind % w;
        y = (ind % (w*l)) / w;
        z = ind / (w*l);
    }

    GameState control(Moves move) {
        // move is a character representing a game move wasd, arrow keys, and spacebar
        // TODO fill in actual motion.
        int x, y, z;
        switch (move) {
            case DOWN:
            case LEFT:
            case RIGHT:
            case FORWARD:
            case BACK:
                translate_piece(move);
                break;
            case PITCH:
            case ROLL:
            case YAW:
                rotate_piece(move);
                break;
        }
    }

    GameState translate_piece(Moves move) {
        // check valid
        int x, y, z;
        bool valid_move = true;
        for (int i = 0; i < w*l*h; i++) {
            ind2sub(i, x, y, z);
            bool condition = state[x][y][z] && state[x][y][z]->falling;
            switch (move) {
                case DOWN:
                    // the block must be falling and below can either be the ground, or another block which is not falling.
                    condition = condition && (z == 0   || (state[x  ][y  ][z-1] && !state[x  ][y  ][z-1]->falling));
                    break;
                case LEFT:
                    condition = condition && (x == 0   || (state[x-1][y  ][z  ] && !state[x-1][y  ][z  ]->falling));
                    break;
                case RIGHT:
                    condition = condition && (x == w-1 || (state[x+1][y  ][z  ] && !state[x+1][y  ][z  ]->falling));
                    break;
                case BACK:
                    condition = condition && (y == 0   || (state[x  ][y-1][z  ] && !state[x  ][y-1][z  ]->falling));
                    break;
                case FORWARD:
                    condition = condition && (y == l-1 || (state[x  ][y+1][z  ] && !state[x  ][y+1][z  ]->falling));
                    break;
            }
            if (condition) {
                valid_move = false;
                break;
            }
        }

        GameState g = PLAYING; // be default, translate piece is fine
        if (!valid_move && move == DOWN) { // in this special case, we have to freeze the piece and spawn a new one
            for (int i = 0; i < w*l*h; i++) {
                ind2sub(i, x, y, z);
                if (state[x][y][z] && state[x][y][z]->falling) {
                    state[x][y][z]->falling = false;
                }
            }
            g = spawn_piece(); // unless if we can't spawn the piece.
        }

        // move piece
        if (valid_move) {
            int i, i_ex;
            bool up;
            switch(move) {
                case DOWN:
                case LEFT:
                case BACK:
                    i = 0;
                    i_ex = w*l*h;
                    up = true;
                    break;
                case RIGHT:
                case FORWARD:
                    i = w*l*h;
                    i_ex = 0;
                    up = false;
                    break;
            }
            for (; up ? i < i_ex : i >= i_ex; up ? i++ : i--) {
                ind2sub(i, x, y, z);
                if (state[x][y][z] && state[x][y][z]->falling) {
                    switch(move) {
                        case DOWN:
                            state[x  ][y  ][z-1] = state[x][y][z];
                            break;
                        case LEFT:
                            state[x-1][y  ][z  ] = state[x][y][z];
                            break;
                        case RIGHT:
                            state[x+1][y  ][z  ] = state[x][y][z];
                            break;
                        case FORWARD:
                            state[x  ][y+1][z  ] = state[x][y][z];
                            break;
                        case BACK:
                            state[x  ][y-1][z  ] = state[x][y][z];
                            break;
                    }
                    state[x][y][z] = NULL;
                }
            }
        }
        return g;
    }


    void rotate_piece(Moves m) {
    }

    GameState spawn_piece() {
        int r = 255, g = 0, b = 0;

        // Generalization of
        //      *
        //     ***
        // game piece
        // TODO add more
        int coords[10][3] = {
            {-1, -1, -1},
            {-1,  0, -1},
            {-1,  1, -1},
            { 0, -1, -1},
            { 0,  0, -1},
            { 0,  1, -1},
            { 1, -1, -1},
            { 1,  0, -1},
            { 1,  1, -1},
            { 0,  0,  0},
        };

        int o[] = {1, 1, 9}; // origin
        for (auto coord: coords) {
            if (state[coord[0] + o[0]][coord[1] + o[1]][coord[2] + o[2]] != NULL) { // if not null, end the game, you lose.
                return LOSS;
            }
        }

        for (auto coord: coords) {
            state[coord[0] + o[0]][coord[1] + o[1]][coord[2] + o[2]] = new Block{r, g, b, true};
        }
        return PLAYING;
    }

    GameState advance() {
        return translate_piece(DOWN);
    }

    void print() {
        int x, y, z;
        for (int i = 0; i < w*l*h; i++) {
            ind2sub(i, x, y, z);
            if (state[x][y][z]) {
                printf("(%d, %d, %d)\n", x, y, z);
            }
        }
    }
};
#endif
