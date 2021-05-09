#ifndef TETRIS_H
#define TETRIS_H
// I pretty much winged this whole thing, so expect lots of bugs. -KZ

#include <iostream>
#include <utility>
#include <vector>

using namespace std;

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

    Tetris(int w = 6, int l = 6, int h = 10) {
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
                return translate_piece(move);
                break;
            case PITCH:
            case ROLL:
            case YAW:
                rotate_piece(move);
                break;
        }

        handle_tetris();
        return PLAYING;
    }

    void handle_tetris() {
        for (int z = 0; z < h; z++) {
            bool tetris = true;
            for (int x = 0; x < w; x++) {
                for (int y = 0; y < l; y++) {
                    if (state[x][y][z] == NULL || state[x][y][z]->falling) {
                        tetris = false;
                    }
                }
            }

            if (tetris) {
                for (int zp = z; zp < h; zp++) {
                    for (int x = 0; x < w; x++) {
                        for (int y = 0; y < l; y++) {
                            if (zp == h-1) {
                                state[x][y][zp] = NULL;
                            } else {
                                state[x][y][zp] = state[x][y][zp + 1];
                            }
                        }
                    }
                }
                z--;
            }
        }
    }

    GameState translate_piece(Moves move) {
        // check valid
        int x, y, z;
        bool valid_move = true;
        for (int i = 0; i < w*l*h; i++) {
            ind2sub(i, x, y, z);
            bool condition = state[x][y][z] != NULL && state[x][y][z]->falling;
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
                    i = w*l*h-1;
                    i_ex = 0;
                    up = false;
                    break;
            }
            for (; up ? i < i_ex : i >= i_ex; up ? i++ : i--) {
                ind2sub(i, x, y, z);
                if (state[x][y][z] != NULL && state[x][y][z]->falling) {
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


    void rotate_piece(Moves move) {
        int x, y, z;
        vector<pair<Block, int*>> t; // translations, formatted as <Block, {x', y', z'}>

        int min_x=w, min_y=l, min_z=h;
        int max_x=0, max_y=0, max_z=0;
        for (int i = 0; i < w*l*h; i++) {
            ind2sub(i, x, y, z);
            if (state[x][y][z] != NULL && state[x][y][z]->falling) {
                if (x > max_x) {
                    max_x = x;
                }
                if (x < min_x) {
                    min_x = x;
                }
                if (y > max_y) {
                    max_y = y;
                }
                if (y < min_y) {
                    min_y = y;
                }
                if (z > max_z) {
                    max_z = z;
                }
                if (z < min_z) {
                    min_z = z;
                }
                t.push_back(make_pair(*(state[x][y][z]), new int[3]{x, y, z}));
            }
        }

        int cen_x=(max_x + min_x)/2;
        int cen_y=(max_y + min_y)/2;
        int cen_z=(max_z + min_z)/2;
        bool valid_move = true;
        for (int i = 0; i < t.size(); i++) {
            int* pos = t[i].second;
            int* new_pos = new int[3]{-1, -1, -1};
            switch(move) {
                case PITCH:
                    new_pos[0] =   pos[0];
                    new_pos[1] = -(pos[2] - cen_z) + cen_y;
                    new_pos[2] =   pos[1] - cen_y  + cen_z;
                    break;
                case ROLL:
                    new_pos[0] =   pos[2] - cen_z  + cen_x;
                    new_pos[1] =   pos[1];
                    new_pos[2] = -(pos[0] - cen_x) + cen_z;
                    break;
                case YAW:
                    new_pos[0] = -(pos[1] - cen_y) + cen_x;
                    new_pos[1] =   pos[0] - cen_x  + cen_y;
                    new_pos[2] =   pos[2];
                    break;
            }
            if (new_pos[0] < 0 || new_pos[0] >= w || new_pos[1] < 0 || new_pos[1] >=l || new_pos[2] < 0 || new_pos[2] >=h) {
                valid_move = false;
                break;
            }
            if (state[new_pos[0]][new_pos[1]][new_pos[2]] != NULL && !state[new_pos[0]][new_pos[1]][new_pos[2]]->falling) {
                valid_move = false;
                break;
            }
            t[i].second = new_pos;
        }

        if (valid_move) {
            for (int i = 0; i < w*l*h; i++) {
                ind2sub(i, x, y, z);
                if (state[x][y][z] != NULL && state[x][y][z]->falling) {
                    state[x][y][z] = NULL;
                }
            }
            for (auto i:  t) {
                int* pos = i.second;
                state[pos[0]][pos[1]][pos[2]] = new Block;
                *(state[pos[0]][pos[1]][pos[2]]) = i.first;
            }
        }
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

        int o[] = {w/2, l/2, h-1}; // origin
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
        GameState ret = translate_piece(DOWN);
        handle_tetris();
        return ret;
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
