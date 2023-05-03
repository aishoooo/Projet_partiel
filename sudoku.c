// Ne pas oublier d'installer GCC pour compiler le programme
// Norme du code :
//-variable en anglais 
//-commentaire 
//-variable dfinir en haut des fonctions
//-type de la variable lors de ce declaration
//-écriture en camel case
//palier 1,2,3 combinés 

//Bibliotheques 
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// parrametre de la grille 
#define BASE 3
#define SIDE (BASE * BASE)


void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * melange avec un tableau deja existant
 */
void shuffle(int array[], size_t length)
{
    size_t j = 0;
    for (size_t i = 0; i < length; i++) {
        j = rand() % length;
        if (j != i) {
            array[i] ^= array[j];
            array[j] ^= array[i];
            array[i] ^= array[j];
        }
    }
}

/**
 * Initialise un tableau le long d'une plage à partir du tableau de départ.
 */
void range(int array[], int length, int offset)
{
    for (int i = 0; i < length; i++) {
        array[i] = i + offset;
    }
}

/**
 * Display the Sudoku Grid.
 */
void display(int board[SIDE][SIDE])
{
    for (int i = 0; i < SIDE; i++) {
        for (int j = 0; j < SIDE; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

/**
 * initialisation du sudoku
 */
void board_gen(int board[SIDE][SIDE], int nums[SIDE])
{
    for (int row = 0; row < SIDE; row++) {
        for (int col = 0; col < SIDE; col++) {
            board[row][col] = nums[(BASE * (row % BASE) + row / BASE + col) % SIDE];
        }
    }
}

/**
 * generer les colonnes
 */
void line_gen(int line[SIDE])
{
    int g[BASE];
    range(g, BASE, 0);
    shuffle(g, BASE);
    int k = 0;
    for (int i = 0; i < BASE; i++) {
        for (int j = g[i] * BASE; j < (g[i] + 1) * BASE; j++) {
            line[k++] = j;
        }
    }
}

/**
 * création des différents inconnu
 */
void sparse(int board[SIDE][SIDE], int empty)
{
    int squares[SIDE * SIDE];
    range(squares, SIDE * SIDE, 0);
    shuffle(squares, SIDE * SIDE);
    for (int i = 0; i < empty; i++) {
        int row = squares[i] / SIDE;
        int col = squares[i] % SIDE;
        board[row][col] = 0;
    }
}

/**
 * Generer le sudoku
 */
void generate(int board[SIDE][SIDE])
{
    // Ligne aléatoire
    int nums[SIDE];
    range(nums, SIDE, 1);
    shuffle(nums, SIDE);

    //Lignes
    int rows[SIDE];
    line_gen(rows);

    //Colonnes
    int cols[SIDE];
    line_gen(cols);

    // base du tableau
    int _board[SIDE][SIDE];
    board_gen(_board, nums);

    // Terminer le tableau
    for (int i = 0; i < SIDE; i++) {
        for (int j = 0; j < SIDE; j++) {
            board[i][j] = _board[rows[i]][cols[j]];
        }
    }
}

int main()
{
    // Savoir si le tableau est vide
    int empty = 0;
    int seed = time(0);

    // Initialiser un nouveau tableau
    srand(seed);

    // Generer le tableau
    int board[SIDE][SIDE];
    generate(board);

    // Suprimer des cases
    if (empty > 0) {
        sparse(board, empty);
    }

    // Affichage du tableau dans le terminale
    display(board);
}