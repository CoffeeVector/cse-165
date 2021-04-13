#ifndef TETRIS_H
#define TETRIS_H
// I pretty much winged this whole thing, so expect lots of bugs. -KZ

enum Moves {
    UP, DOWN, LEFT, RIGHT, PITCH, ROLL, YAW
};

struct Block {
    int r, g, b;
    bool falling;
};

class Tetris {
    public:
    Block**** state; // state[x][y][z], where z is the falling direction. x and y is arbitrary.
    int w, l, h;

    Tetris(int w, int l, int h) {
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

    void control(Moves move) {
        // move is a character representing a game move wasd, arrow keys, and spacebar
        // TODO fill in actual motion.
        switch (move) {
            case UP:
                break;
            case DOWN:
                break;
            case LEFT:
                break;
            case RIGHT:
                break;
            case PITCH:
                break;
            case ROLL:
                break;
            case YAW:
                break;
        }
    }

    void spawn_piece() {
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
            state[coord[0] + o[0]][coord[1] + o[1]][coord[2] + o[2]] = new Block{r, g, b, true};
        }
    }

    void advance() {
        // makes the natural advancement in the game state (falling blocks and tetris)
        int x, y, z;

        bool landed = false; // as in, as the shape "landed" and touched the ground
        for (int i = 0; i < w*l*h; i++) {
            ind2sub(i, x, y, z);
            if (state[x][y][z] && state[x][y][z]->falling && (z == 0 || (state[x][y][z-1] && !state[x][y][z-1]->falling))) {
                // the block must be falling and below can either be the ground, or another block which is not falling.
                landed = true;
                break;
            }
        }

        if (landed) {
            // freeze the blocks, and begin a new shape
            for (int i = 0; i < w*l*h; i++) {
                ind2sub(i, x, y, z);
                if (state[x][y][z] && state[x][y][z]->falling) {
                    state[x][y][z]->falling = false;
                }
            }

            // TODO: begin new shape. should be a new function.
        } else {
            // move all the falling shapes down by one
            for (int i = 0; i < w*l*h; i++) {
                ind2sub(i, x, y, z);
                if (state[x][y][z] && state[x][y][z]->falling) {
                    state[x][y][z-1] = state[x][y][z];
                    state[x][y][z] = NULL;
                    // this should not introduce complications so long that
                    // we are computing this from z = 0 to z = l, which the
                    // linear indexing should do.
                }
            }
        }
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
