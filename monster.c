#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main ( int argc, char* argv[] ) {

    //Read input parameters and initialize board

    for(int i=1; i<=8; i++){
        if(argv[i]==NULL){
            printf("Invalid Board\n");
            return EXIT_SUCCESS;
        }
    }

    for(int i=1; i<=8; i++){
        if(!isdigit(argv[i][0])){
            printf("Invalid Board\n");
            return EXIT_SUCCESS;
        }
    }

    int boardX = atoi(argv[1]);
    int boardY = atoi(argv[2]);
    int plrX = atoi(argv[3]);
    int plrY = atoi(argv[4]);
    int goalX = atoi(argv[5]);
    int goalY = atoi(argv[6]);
    int monX = atoi(argv[7]);
    int monY = atoi(argv[8]);

    char** board = calloc(boardY,sizeof(char*));

    for(int i=0; i<boardY; i++){

        board[i] = calloc(boardX, sizeof(char));

        for(int j=0; j<boardX; j++){
            board[i][j] = '.';
        }
    }

    if(plrX < boardX && plrY < boardY){
        board[plrY][plrX] = 'P';
    }
    else{
        printf("Invalid Board\n");
        for(int i=boardY-1; i>=0; i--){
            free(board[i]);
        }

        free(board);
        return EXIT_SUCCESS;
    }

    if(goalX < boardX && goalY < boardY){
        board[goalY][goalX] = 'G';
    }
    else{
        printf("Invalid Board\n");
        for(int i=boardY-1; i>=0; i--){
            free(board[i]);
        }

        free(board);
        return EXIT_SUCCESS;
    }

    if(monX < boardX && monY < boardY){
        board[monY][monX] = 'M';
    }
    else{
        printf("Invalid Board\n");
        for(int i=boardY-1; i>=0; i--){
            free(board[i]);
        }

        free(board);
        return EXIT_SUCCESS;
    }


    //Player moves N S E W, based on player input
    //Monster moves to reduce distance vertically or horizontally which ever is lower, or randomized if same distance
    //Ctrld for quit
    //player in monster square = monster win
    //player in goal square = player win
    //player cannot move outside border
    
    /*
    for(int i=boardY-1; i>=0; i--){
        for(int j=0; j<boardX; j++){
            printf("(%d,%d) ",i,j);
        }
        printf("\n");
    }
    */

    for(int i=boardY-1; i>=0; i--){
        for(int j=0; j<boardX; j++){
            printf("%c ",board[i][j]);
        }
        printf("\n");
    }

    int quit=0;
    char move = ' ';
    int validMove = 0;
    char buf[256];

    while (quit == 0){
        
        validMove = 0;
        move = getchar();
        fgets(buf,256,stdin);

        if(move=='N'){
            if(plrY==boardY-1){
                printf("invalid move\n");
            }
            else{
                validMove = 1;
                board[plrY][plrX] = '.';
                plrY+=1;
                board[plrY][plrX] = 'P';
            }
        }
        else if(move=='S'){
            if(plrY==0){
                printf("invalid move\n");
            }
            else{
                validMove = 1;
                board[plrY][plrX] = '.';
                plrY-=1;
                board[plrY][plrX] = 'P';
            }
        }
        else if(move=='E'){
            if(plrX==boardX-1){
                printf("invalid move\n");
            }
            else{
                validMove = 1;
                board[plrY][plrX] = '.';
                plrX+=1;
                board[plrY][plrX] = 'P';
            }
        }
        else if(move=='W'){
            if(plrX==0){
                printf("invalid move\n");
            }
            else{
                validMove = 1;
                board[plrY][plrX] = '.';
                plrX-=1;
                board[plrY][plrX] = 'P';
            }
        }

        if(validMove == 1){

            int diffX = monX-plrX;
            int diffY = monY-plrY;

            if(goalX == plrX && goalY == plrY){
                printf("player wins!\n");
                quit = 1;
            }

            else if(diffX == 0 && diffY == 0){
                printf("monster wins!\n");
                quit = 1;
            }
            else{
                if(abs(diffX) == abs(diffY)){
                    int random = rand() % 2;
                    if(random == 0){
                        //diffX
                        if(plrX<=diffX){
                            if(!(((monX-1) == goalX) && (monY == goalY)) && (monX!=0)){
                                printf("monster moves W\n");
                                board[monY][monX] = '.';
                                monX-=1;
                                board[monY][monX] = 'M';
                            }
                            else{
                                printf("monster forfeits turn\n");
                            }
                        }
                        else if(plrX>diffX){
                            if(!(((monX+1) == goalX) && (monY == goalY)) && (monX!=boardX-1)){
                                printf("monster moves E\n");
                                board[monY][monX] = '.';
                                monX+=1;
                                board[monY][monX] = 'M';
                            }
                            else{
                                printf("monster forfeits turn\n");
                            }
                        }
                    }
                    else if(random == 1){
                        //diffY
                        if(plrY<=diffY){
                            if(!(((monY-1) == goalY) && (monX == goalX)) && (monY!=0)){
                                printf("monster moves S\n");
                                board[monY][monX] = '.';
                                monY-=1;
                                board[monY][monX] = 'M';
                            }
                            else{
                                printf("monster forfeits turn\n");
                            }
                        }
                        else if(plrY>diffY){
                            if(!(((monY+1) == goalY) && (monX == goalX)) && (monY!=boardY-1)){
                                printf("monster moves N\n"); 
                                board[monY][monX] = '.';
                                monY+=1;
                                board[monY][monX] = 'M';
                            }
                            else{
                                printf("monster forfeits turn\n");
                            }
                        }
                    }
                }
                else if(abs(diffX) < abs(diffY)){
                    //diffY
                    if(plrY<=diffY){
                        if(!(((monY-1) == goalY) && (monX == goalX)) && (monY!=0)){
                            printf("monster moves S\n"); 
                            board[monY][monX] = '.';
                            monY-=1;
                            board[monY][monX] = 'M';
                        }
                        else{
                            printf("monster forfeits turn\n");
                        }
                    }
                    else if(plrY>diffY){
                        if(!(((monY+1) == goalY) && (monX == goalX)) && (monY!=boardY-1)){
                            printf("monster moves N\n"); 
                            board[monY][monX] = '.';
                            monY+=1;
                            board[monY][monX] = 'M';
                        }
                        else{
                            printf("monster forfeits turn\n");
                        }
                    }
                }
                else if(abs(diffX) > abs(diffY)){
                    //diffX
                    if(plrX<=diffX){
                        if(!(((monX-1) == goalX) && (monY == goalY) && (monX==0))){
                            printf("monster moves W\n");
                            board[monY][monX] = '.';
                            monX-=1;
                            board[monY][monX] = 'M';
                        }
                        else{
                            printf("monster forfeits turn\n");
                        }
                    }
                    else if(plrX>diffX){
                        if(!(((monX+1) == goalX) && (monY == goalY) && (monX==boardX-1))){
                            printf("monster moves E\n");
                            board[monY][monX] = '.';
                            monX+=1;
                            board[monY][monX] = 'M';
                        }
                        else{
                            printf("monster forfeits turn\n");
                        }
                    }
                }
                if(monX == plrX && monY == plrY){
                    printf("monster wins!\n");
                    quit = 1;
                }
                else{
                    for(int i=boardY-1; i>=0; i--){
                        for(int j=0; j<boardX; j++){
                            printf("%c ",board[i][j]);
                        }
                        printf("\n");
                    }
                }
            }
        }

        if(feof(stdin)){
            quit = 1;
        }
    }

    for(int i=boardY-1; i>=0; i--){
        free(board[i]);
    }

    free(board);

    return EXIT_SUCCESS;
}