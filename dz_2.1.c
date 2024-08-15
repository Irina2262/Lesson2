/*
 ЗАДАЧА 1.
Проблематика: сейчас змейка “наезжает” на свой хвост.
Написать функцию, которая будет проверять корректность выбранного
направления. Змейка не может наступать на хвост, поэтому необходимо
запретить:
● перемещение справа-налево (при движении RIGHT нажатие стрелки
влево),
● перемещение сверху-вниз (при движении UP нажатие стрелки вниз),
● перемещение слева-направо (при движении LEFT нажатие стрелки
вправо),
● перемещение снизу-вверх (при движении DOWN нажатие стрелки
вверх).
Функция должна иметь вид:
int checkDirection(snake_t* snake, int32_t key).

 */
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <stdint.h> // Подключение для использования int32_t

#define MAX_X 15
#define MAX_Y 15

typedef struct tail_t {
    int x;
    int y;
} tail_t;

typedef struct snake_t {
    int x;
    int y;
    struct tail_t *tail;
    size_t tsize;
} snake_t;

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

// Функция для проверки корректности направления
int checkDirection(snake_t *snake, int32_t key) {
    if (snake->tsize == 0) {
        return 1; // Если хвоста нет, любое направление корректно
    }

    int head_x = snake->x;
    int head_y = snake->y;

    int tail_x = snake->tail[0].x;
    int tail_y = snake->tail[0].y;

    if ((key == LEFT && head_x - 1 == tail_x && head_y == tail_y) ||
        (key == RIGHT && head_x + 1 == tail_x && head_y == tail_y) ||
        (key == UP && head_y - 1 == tail_y && head_x == tail_x) ||
        (key == DOWN && head_y + 1 == tail_y && head_x == tail_x)) {
        return 0; // Неверное направление
    }

    return 1; // Корректное направление
}

// Инициализация змейки
struct snake_t initSnake(int x, int y, size_t tsize) {
    struct snake_t snake;
    snake.x = x;
    snake.y = y;
    snake.tsize = tsize;
    snake.tail = (tail_t *)malloc(sizeof(tail_t) * 100);
    for (int i = 0; i < tsize; ++i) {
        snake.tail[i].x = x + i + 1;
        snake.tail[i].y = y;
    }
    return snake;
}

// Движение змейки влево
snake_t moveLeft(snake_t snake) {
    for (int i = snake.tsize - 1; i > 0; i--) {
        snake.tail[i] = snake.tail[i - 1];
    }
    snake.tail[0].x = snake.x;
    snake.tail[0].y = snake.y;

    snake.x = snake.x - 1;
    if (snake.x < 0) {
        snake.x = MAX_X - 1;
    }
    return snake;
}

// Движение змейки вправо
snake_t moveRight(snake_t snake) {
    for (int i = snake.tsize - 1; i > 0; i--) {
        snake.tail[i] = snake.tail[i - 1];
    }
    snake.tail[0].x = snake.x;
    snake.tail[0].y = snake.y;

    snake.x = snake.x + 1;
    if (snake.x >= MAX_X) {
        snake.x = 0;
    }
    return snake;
}

// Движение змейки вверх
snake_t moveUp(snake_t snake) {
    for (int i = snake.tsize - 1; i > 0; i--) {
        snake.tail[i] = snake.tail[i - 1];
    }
    snake.tail[0].x = snake.x;
    snake.tail[0].y = snake.y;

    snake.y = snake.y - 1;
    if (snake.y < 0) {
        snake.y = MAX_Y - 1;
    }
    return snake;
}

// Движение змейки вниз
snake_t moveDown(snake_t snake) {
    for (int i = snake.tsize - 1; i > 0; i--) {
        snake.tail[i] = snake.tail[i - 1];
    }
    snake.tail[0].x = snake.x;
    snake.tail[0].y = snake.y;

    snake.y = snake.y + 1;
    if (snake.y >= MAX_Y) {
        snake.y = 0;
    }
    return snake;
}

// Печать змейки
void printSnake(struct snake_t snake) {
    char matrix[MAX_X][MAX_Y];
    for (int i = 0; i < MAX_X; ++i) {
        for (int j = 0; j < MAX_Y; ++j) {
            matrix[i][j] = ' ';
        }
    }

    matrix[snake.x][snake.y] = '@';
    for (int i = 0; i < snake.tsize; ++i) {
        matrix[snake.tail[i].x][snake.tail[i].y] = '*';
    }

    for (int j = 0; j < MAX_Y; ++j) {
        for (int i = 0; i < MAX_X; ++i) {
            printf("%c", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    struct snake_t snake = initSnake(10, 5, 2);
    printSnake(snake);

    int32_t direction = LEFT; // Начальное направление движения

    while (1) {
        int32_t key;

        // Ожидание ввода пользователя
        if (_kbhit()) {
            key = _getch();

            // Преобразование ввода пользователя в направление
            switch (key) {
                case 'w':
                    key = UP;
                    break;
                case 's':
                    key = DOWN;
                    break;
                case 'a':
                    key = LEFT;
                    break;
                case 'd':
                    key = RIGHT;
                    break;
                default:
                    continue;
            }

            // Если направление корректно, обновляем направление движения
            if (checkDirection(&snake, key)) {
                direction = key;
            }
        }

        // Обновляем положение змейки в зависимости от текущего направления
        switch (direction) {
            case LEFT:
                snake = moveLeft(snake);
                break;
            case RIGHT:
                snake = moveRight(snake);
                break;
            case UP:
                snake = moveUp(snake);
                break;
            case DOWN:
                snake = moveDown(snake);
                break;
        }

        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); // Очистка экрана
        printSnake(snake);

        usleep(100000); // Задержка для контроля скорости змейки
    }

    return 0;
}
