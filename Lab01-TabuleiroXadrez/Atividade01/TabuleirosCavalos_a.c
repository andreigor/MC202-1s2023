#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int col_number(char value) {
    switch (value) {
    case 'A':
        return 1;
    case 'B':
        return 2;
    case 'C':
        return 3;
    case 'D':
        return 4;
    case 'E':
        return 5;
    case 'F':
        return 6;
    case 'G':
        return 7;
    case 'H':
        return 8;
    default:
        return 30;
    }
}

char col_char(int value) {
    switch (value) {
    case 1:
        return 'A';
    case 2:
        return 'B';
    case 3:
        return 'C';
    case 4:
        return 'D';
    case 5:
        return 'E';
    case 6:
        return 'F';
    case 7:
        return 'G';
    case 8:
        return 'H';
    default:
        return ' ';
    }
}

typedef struct {
    int row;
    int col;
} position;

position possible_moves[8] = {
    { .row =  2, .col = -1 },
    { .row =  2, .col =  1 },
    { .row =  1, .col =  2 },
    { .row = -1, .col =  2 },
    { .row = -2, .col =  1 },
    { .row = -2, .col = -1 },
    { .row = -1, .col = -2 },
    { .row =  1, .col = -2 },
};

bool is_position_valid(position pos) {
    if (pos.col < 1 || pos.col > 8) {
        return false;
    }

    if (pos.row < 1 || pos.row > 8) {
        return false;
    }

    return true;
}

void print_position(position pos) {
    char col = col_char(pos.col);
    printf("%c %d\n", col, pos.row);
}

void print_valid_moves(position pos) {
    for (int move = 0; move < 8; move++) {
        position current_move = possible_moves[move];
        position move_pos = {
            .row = pos.row + current_move.row,
            .col = pos.col + current_move.col
        };

        if (is_position_valid(move_pos)) {
            print_position(move_pos);
        }
    }
}

position scan_position() {
    char col = ' ';
    int row;

    scanf(" %c %d", &col, &row);
    position pos = { .row = row, .col = col_number(col) };
    return pos;
}

bool equals(position pos1, position pos2) {
    return pos1.row == pos2.row && pos1.col == pos2.col;
}

bool is_attacking(position pos1, position pos2) {
    position diff = {
        .row = pos1.row - pos2.row,
        .col = pos1.col - pos2.col
    };

    for (int move = 0; move < 8; move++) {
        if (equals(diff, possible_moves[move])) {
            return true;
        }
    }

    return false;
}

void scan_positions(position positions[], int n) {
    for (int i = 0; i < n; i++) {
        positions[i] = scan_position();
    }
}

bool check_board(position positions[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (is_attacking(positions[i], positions[j])) {
                return true;
            }
        }
    }

    return false;
}

void activity1() {
    position pos = scan_position();
    print_valid_moves(pos);
}

void activity2() {
    int n;
    scanf("%d", &n);
    position positions[64];
    scan_positions(positions, n);
    if (check_board(positions, n)) {
        printf("Os cavalos estao em guerra!\n");
    } else {
        printf("Paz no reino!\n");
    }
}

int main(void) {
    activity1();
    return EXIT_SUCCESS;
}
