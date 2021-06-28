// Why the heck am i creating this??
// I should study another things... Like app dev or something

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

struct boxContent{
    int H, W, x, y, movement;
};

boxContent boxInitialization(){
    boxContent content;
    printf("input width: ");
    scanf(" %d", &content.W);
    printf("input height: ");
    scanf(" %d", &content.H);
    srand(time(NULL));
    content.x = (rand() % content.W) + 1;
    content.y = (rand() % content.H) + 1;
    content.movement = (rand()%4) + 1;
    return content;
}

void printBox(boxContent content){
    char box[content.H][content.W];
        for(int i = 0; i < content.H; i++){
        for(int j = 0; j < content.W; j++){
            box[i][j] = ' ';
        }
    }
    box[content.y - 1][content.x - 1] = 'O';
    for(int i = 0; i < content.W+2; i++){
        printf("#");
    }
    printf("\n");
    for(int i = 0; i < content.H; i++){
        printf("#");
        for(int j = 0; j < content.W; j++){
            printf("%c", box[i][j]);
        }
        printf("#\n");
    }
    for(int i = 0; i < content.W+2; i++){
        printf("#");
    }
    printf("\n");
}

boxContent updateLocation(boxContent content){
    int nextX, nextY;
    switch(content.movement){
        case 1:
            nextX = -1;
            nextY = -1;
            break;
        case 2:
            nextX = 1;
            nextY = -1;
            break;
        case 3:
            nextX = -1;
            nextY = 1;
            break;
        case 4:
            nextX = 1;
            nextY = 1;
            break;
    }

    if(content.x + nextX > content.W){
        content.movement -= 1;
        content.x -= nextX;
    } else if(content.x + nextX < 1){
        content.movement += 1;
        content.x -= nextX;
    } else {   
        content.x += nextX;
    }
    if(content.y + nextY > content.H){
        content.movement -= 2;
        content.y -= nextY;
    } else if(content.y + nextY < 1){
        content.movement += 2;
        content.y -= nextY;
    } else {   
        content.y += nextY;
    }
    return content;
}

// box structure :
// 1   2
//   O 
// 3   4

void animate(boxContent content){
    while(1){
        system("cls");
        printBox(content);
        content = updateLocation(content);
        usleep(100 * 1000);
    }
}

int main(){
    boxContent content = boxInitialization();
    animate(content);
}
