#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

struct snakeStructure{
    int x, y;
    struct snakeStructure *before;
};

struct mapDetail{
    int W, H, movement, x, y, reLocate;
    struct snakeStructure *snake;
};

struct mapDetail *createMap(){
    struct mapDetail *map = (struct mapDetail*)malloc(sizeof(struct mapDetail));
    map->H = 10;
    map->W = 30;
    srand(time(0));
    map->snake = (struct snakeStructure*)malloc(sizeof(struct snakeStructure));
    map->snake->x = rand() % map->W;
    map->snake->y = rand() % map->H;
    map->x = rand() % map->W;
    map->y = rand() % map->H;
    while(map->snake->x == map->x && map->snake->y == map->y){
        map->x = rand() % map->W;
        map->y = rand() % map->H;    
    }
    map->reLocate = 0;
    map->snake->before = NULL;
    map->movement = rand() % 4 + 1;
    return map;
}

void mapDrawer(struct mapDetail *detail){
    char map[detail->H][detail->W];
    for(int i = 0; i < detail->H; i++){
        for(int j = 0; j < detail->W; j++){
            map[i][j] = ' ';
        }   
    }
    struct snakeStructure *snake = detail->snake;
    map[snake->y][snake->x] = 'O';
    while(snake->before){
        snake = snake->before;
        map[snake->y][snake->x] = 'O';    
    }
    for(int i = 0; i < detail->W+2; i++){
        printf("#");
    }
    printf("\n");
    for(int i = 0; i < detail->H; i++){
        printf("#");
        for(int j = 0; j < detail->W; j++){
            printf("%c", map[i][j]);
        }
        printf("#\n");
    }
    for(int i = 0; i < detail->W+2; i++){
        printf("#");
    }
    printf("\n");
}

void popTail(struct snakeStructure* snake){
    struct snakeStructure *deleteThis = snake;
    while(deleteThis->before){
        if(deleteThis->before->before){
            deleteThis = deleteThis->before;
        } else {
            break;
        }
    }
    free(deleteThis->before);
    deleteThis->before = NULL;
}

void relocateFood(struct mapDetail *map){
    while(map->snake->x == map->x && map->snake->y == map->y){
        map->x = rand() % map->W;
        map->y = rand() % map->H;    
    }
    map->reLocate = 1;
}

void moveChar(struct mapDetail *map){
    if(kbhit()){
        if(getch() == 0){
            char h = getch();
            switch(h){
                case 72 : //up
                    map->movement = 1;
                    break;
                case 80 : //down
                    map->movement = 2;
                    break;
                case 75 : //left
                    map->movement = 3;
                    break;
                case 77 : //right
                    map->movement = 4;
                    break;
            }
        }
    }
    struct snakeStructure snake = (*map->snake);
    switch(map->movement){
        case 1:
            snake.y -= 1;
            break;
        case 2:
            snake.y += 1;
            break;
        case 3:
            snake.x -= 1;
            break;
        case 4:
            snake.x += 1;
            break;
    }
    snake.before = map->snake;
    map->snake = &snake;
    if(!map->reLocate){
        popTail(map->snake);
    }
    if(map->snake->x == map->x && map->snake->y == map->y){
        relocateFood(map);
    }
}

int main(){
    struct mapDetail *map = createMap();
    while(1){
        system("cls");
        moveChar(map);
        mapDrawer(map);
        sleep(1);
    }
}