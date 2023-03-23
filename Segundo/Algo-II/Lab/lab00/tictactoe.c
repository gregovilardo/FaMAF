#include <stdlib.h>  /* exit() y EXIT_FAILURE */
#include <stdio.h>   /* printf(), scanf()     */
#include <stdbool.h> /* Tipo bool             */

#include <assert.h>  /* assert() */


#define BOARD_TAM 5
#define CELL_MAX (BOARD_TAM * BOARD_TAM - 1)

void print_sep(int length) {
    printf("\t ");
    for (int i=0; i < length;i++) printf("................");
    printf("\n");

}

void print_board(char board[BOARD_TAM][BOARD_TAM])
{
    int cell = 0;

    print_sep(BOARD_TAM);
    for (int row = 0; row < BOARD_TAM; ++row) {
        for (int column = 0; column < BOARD_TAM; ++column) {
            printf("\t | %d: %c ", cell, board[row][column]);
            ++cell;
        }
        printf("\t | \n");
        print_sep(BOARD_TAM);
    }
}

bool check_columna(int n, char board[BOARD_TAM][BOARD_TAM], char a) {
    bool res = true;
    for (int i = 0; i < BOARD_TAM-1; i++)
    {
        if (board[i][n] == board[i+1][n] && board[i][n] == a){
            res = res && true;
        } else {
            res = false;
        }
    }
    return res;    
} 

bool check_fila(int n, char board[BOARD_TAM][BOARD_TAM], char a) {
    bool res = true;
    for (int i = 0; i < BOARD_TAM-1; i++)
    {
        if (board[n][i] == board[n][i+1] && board[n][i] == a){
            res = res && true;
        } else {
            res = false;
        }
    }
    return res;    
}

bool check_diagonal(char board[BOARD_TAM][BOARD_TAM], char a) {
    bool res = true;
    for (int i = 0; i < BOARD_TAM-1; i++)
    {
        if (board[i][i] == board[i+1][i+1] && board[i][i] == a){
            res = res && true;
        } else {
            res = false;
        }
    }
    return res;    
}


bool check_diagonal_opuesta(char board[BOARD_TAM][BOARD_TAM], char a) {
    bool res = true;
    int i = 0;
    int j = BOARD_TAM-1;
    while (i < BOARD_TAM)
    {
        if (board[i][j] == board[j][i] && board[i][j] == a){
            res = res && true;
        } else {
            res = false;
        }
        i++;
        j--;
    }
    return res;    
}


bool check_winner(char a, char board[BOARD_TAM][BOARD_TAM]) {
    bool res = false;
    if (check_diagonal_opuesta(board, a)) {
        res = true;
    }
    if (check_diagonal(board, a)) {
        res = true;
    }

    for (int i = 0; i < BOARD_TAM; i++)
    {
        if (check_fila(i, board, a)) {
            res = true;
        }
        if (check_columna(i, board, a)) {
            res = true;
        }
    }
    return res;
    
}

char get_winner(char board[BOARD_TAM][BOARD_TAM])
{
    char winner = '-';
    //
    // TODO: COMPLETAR

    if (check_winner('X', board)) {
        winner = 'X';
    }
    if (check_winner('O', board)) {
        winner = 'O';
    }
    
    //
    return winner;
}

bool has_free_cell(char board[BOARD_TAM][BOARD_TAM])
{
    bool free_cell=false;
    //
    // TODO: COMPLETAR
    for (int i = 0; i < BOARD_TAM; i++)
    {
        for (int j = 0; i < BOARD_TAM; j++)
        {
            if (board[i][j] == '-') {
                free_cell = true;
                return free_cell;
            }
        }
    }
    
    //
    return free_cell;
}



int main(void)
{
    printf("TicTacToe [InCoMpLeTo :'(]\n");

    char board[BOARD_TAM][BOARD_TAM];
    for (int i = 0; i < BOARD_TAM; i++) {
      for (int j = 0; j < BOARD_TAM ; j++) {
        board[i][j] = '-';
      }
    } 

    char turn = 'X';
    char winner = '-';
    int cell = 0;
    while (winner == '-' && has_free_cell(board)) {
        print_board(board);
        printf("\nTurno %c - Elija posición (número del 0 al %d): ", turn,
               CELL_MAX);
        int scanf_result = scanf("%d", &cell);
        if (scanf_result <= 0) {
            printf("Error al leer un número desde teclado\n");
            exit(EXIT_FAILURE);
        }
        if (cell >= 0 && cell <= CELL_MAX) {
            int row = cell / BOARD_TAM;
            int colum = cell % BOARD_TAM;
            if (board[row][colum] == '-') {
                board[row][colum] = turn;
                turn = turn == 'X' ? 'O' : 'X';
                winner = get_winner(board);
            } else {
                printf("\nCelda ocupada!\n");
            }
        } else {
            printf("\nCelda inválida!\n");
        }
    }
    print_board(board);
    if (winner == '-') {
        printf("Empate!\n");
    } else {
        printf("Ganó %c\n", winner);
    }
    return 0;
}
