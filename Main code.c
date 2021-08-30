#include <stdio.h>
#include <stdlib.h>

/* Function to initialize the board after setting its size */
void initializeBoard(char** board, int size);

/* This function displays the current board condition after each turn */
void printBoard(char** board, int size);

/* This function frees the allocated memory of the game board */
void myfree(char** board, int size);

/* This function monitors whether a winning condition is met after each an every turn. if not, switch the active player and promt the next turn */
int turnResult(char** board, int size,char userMark, char userName); /* להוסיף פה בדיקה של תיקו */


int main()
{

    /* Variable for the rows, columns, board size, index, row+column input, game over indicator */
    int rows, columns, size, i, row, column,gameOver=0;

    /* This string represents the main game board */
    char** board;

    /* Variables for the user nicknames and their corresponding letters, initiated with A and 'X' */
    char currentUser='X', userName='A';

    /* board size input prompt */
    printf("Enter the dimensions of the board: \n");
    if(scanf("%d%d", &rows, &columns)<2)
    {
        printf("Input Error!");
        return 1;
    }

    /* Error check to make sure the board is square */
    if(rows!=columns || rows<3)
    {
        printf("Input Error!");
        return 1;
    }
    size=rows;

    /* Memory allocations and their integrity checks */
    board=(char**)malloc(rows*sizeof(char*));
    if(board==NULL)
    {
        printf("Allocation failed\n");
        return 1;
    }
    for(i=0 ; i<rows ; i++)
    {
        board[i]=(char*)malloc(columns*sizeof(char));
        if(board[i]==NULL)
        {
            printf("Allocation failed\n");
            return 1;
        }
    }
    /* Initial print of an empty game board */
    initializeBoard(board, size);

    /* Print of the first game turn before entering the main turn prompt loop */
    printBoard(board, size);

    /*Main turn-prompt loop, repeats until either a winner is declared or a tie has occured */
    do
    {


        printf("\nThe turn of %c, type your choice (row col): \n",userName);
        if(!scanf("%d%d",&row,&column))
        {
            printf("Input Error!");
            return 1;
        }
        if (row >= rows || column >= columns || board[row][column]!=' ')
        {
         printf("Input Error!");
         return 1;


        }
         board[row][column]=currentUser;
         printBoard(board, size);
         gameOver=turnResult(board,size,currentUser,userName);
        if (currentUser=='X')
            {
                currentUser='O';
                userName='B';
            }

            else
            {
                currentUser='X';
                userName='A';
            }

    }while(gameOver==0);
    myfree(board, size);



    return 0;
}




void initializeBoard(char** board, int size)
{
    /* Varibales for array indexes */
    int i,j;
    for(i=0; i<size; i++)
    {
        for(j=0; j<size; j++)
        {
            board[i][j]=' ';
        }
    }

}



void printBoard(char** board, int size)
{
    /* Varibales for array indexes */
    int i,j;
    for(i=0; i<size; i++)
    {
        for(j=0; j<size; j++)
        {
            printf("[%c] ",board[i][j]);
        }
        printf("\n");
    }
}

int turnResult(char** board, int size,char userMark, char userName)
{
    /* Varibales for array indexes */
    int i, j;

    /* A counter varibale that triggers a tie if the board is completely filled with user inputs */
    int flag=0;
    for(i=0 ;i<size; i++)
    {
        for(j=0; j<size; j++)
        {
            if(board[i][j]!=' ')
            {
                flag++;
            }
        }
    }
    if(flag==size*size)
    {
        printf("\nTIE");
        return 1;
    }

    /* This loop is checks for a victory by a backward diagonal line */
    flag=1;
    for(j=0, i=size-1 ; j<size-1 && i>=0 ; j++, i--)
    {
        if(board[i][j]==board[i-1][j+1] && board[j][i]==userMark)
        {
            flag++;
        }
    }
    if(flag==size)
    {
        printf("\nPlayer %c won the game!",userName);
        return 1;
    }

    /* This loop is checks for a victory by a forward diagonal line */
    flag=1;
    for(j=0 ; j<size-1 ; j++)
    {
        if(board[j][j]==board[j+1][j+1] && board[j][j]==userMark)
        {
            flag++;
        }
    }

    if(flag==size)
    {
        printf("\nPlayer %c won the game!",userName);
        return 1;
    }

    /* This loop is checks for a victory by a horizonal line (row) */
    for(i=0; i<size; i++)
    {
        flag=1;
        for(j=0;j<size;j++)
        {

            if(board[i][j]==userMark &&(board[i][j]==board[i][j+1]))
            {
                flag++;
            }

        }

        if(flag==size){
        printf("\nPlayer %c won the game!",userName);
        return 1;
        }
    }

    /* This loop is checks for a victory by a vertical line (column) */
    for(j=0; j<size; j++)
    {
        flag=1;
        for(i=0;i<size-1;i++)
        {

            if(board[i][j]==userMark &&(board[i][j]==board[i+1][j]))
            {
                flag++;
            }

        }

        if(flag==size)
        {
            printf("\nPlayer %c won the game!",userName);
            return 1;
        }
    }
    return 0;

}

void myfree(char** board, int size)
{
    /* Index variable */
    int i=0;
    while(i<size)

        free(board[i++]);
    free(board);
    return;
}
