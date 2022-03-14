#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define WIDTH 80
#define HEIGHT 25
#define LIVE 'O'
#define DEATH ' '

void init(int rows, int cols);
double getRandom(double min, double max);
char* create(int rows, int cols);
void render(int rows, int cols, char* simulation);
int countNeighbor(int rows, int cols, int x, int y, char* simulation);
char* step(int rows, int cols, char* prevSimulation);

int main() {
    init(HEIGHT, WIDTH);

    return 0;
}

// Функция инициализации игры
void init(int rows, int cols) {
  system("clear");
    for (int y = 0; y < rows + 2; y++) {
      if (y == 10) {
        printf("     TTTTT H  H EEEE   GGGG   A   MM MM EEEE    OO  FFFF   L   I FFFF EEEE\n");
      } else if (y == 11) {
        printf("       T   H  H E      G     A A  MM MM E      O  O F      L   I F    E\n");
      } else if (y == 12) {
        printf("       T   HHHH EEE    G GG AAAAA M M M EEE    O  O FFF    L   I FFF  EEE\n");
      } else if (y == 13) {
        printf("       T   H  H E      G  G A   A M   M E      O  O F      L   I F    E\n");
      } else if (y == 14) {
        printf("       T   H  H EEEE   GGGG A   A M   M EEEE    OO  F      LLL I F    EEEE\n");
      } else {
        printf("\n");
      }
    }
  usleep(3000000);
    char* simulation = create(rows, cols);
    if (simulation == NULL) return;
    render(rows, cols, simulation);
    while (1) {
      usleep(200000);
        char* newSim = step(rows, cols, simulation);
        if (newSim == NULL) return;
        free(simulation);
        simulation = newSim;
        render(rows, cols, simulation);
    }
}

// Функция возвращает рандомное значение в интервале от min до max
double getRandom(double min, double max) {
    return ((double)rand()/RAND_MAX)*(max - min) + min;
}

// Функция возвращает массив с игровой симуляцией,
// полученной из файла или сгенерированой рандомно
// (в случае отсутствия файла)
char* create(int rows, int cols) {
    char* simulation = (char*)calloc(rows*cols, sizeof(char));
    if (simulation == NULL) return NULL;
  char c;
  for (int y = 1; y <= rows; y++) {
      for (int x = 0; x <= cols; x++) {
        c = getchar();
        if (c != '\n') *(simulation + y*cols + x) = c;
        if (c != '\n' && c != LIVE && c != DEATH) break;
      }
    if (c != '\n' && c != LIVE && c != DEATH) break;
  }

  if (*(simulation + rows*cols) != DEATH && *(simulation + rows*cols) != LIVE) {
        for (int y = 1; y <= rows; y++) {
            for (int x = 1; x <= cols; x++) {
                if (getRandom(0.0, 1.0) <= 0.35) {
                  *(simulation + y*cols + x) = LIVE;
                } else {
                  *(simulation + y*cols + x) = DEATH;
                }
            }
        }
  }

    return simulation;
}

// Функция отрисовки на экран игровых элементов на текущем шаге
void render(int rows, int cols, char* simulation) {
            system("clear");
            for (int y = 0; y < rows + 2; y++) {
                for (int x = 0; x < cols + 2; x++) {
                    if (y == 0 && x == 0) {
                                   printf("╔");
                               } else if (y == 0 && x == cols + 1) {
                                   printf("╗");
                               } else if (y == rows + 1 && x == 0) {
                                   printf("╚");
                               } else if (y == rows + 1 && x == cols + 1) {
                                   printf("╝");
                               } else if ((y > 0 && x == 0) || (y > 0 && x == cols + 1)) {
                                   printf("║");
                               } else if ((y == 0 && x > 0) || (y == rows + 1 && x > 0)) {
                                   printf("═");
                               } else {
                                    printf("%c", *(simulation + y*cols + x));
                               }
                }
                printf("\n");
            }
            printf("\n");
}

// Функция возвращает количество "живых" клеток вокруг текущей
int countNeighbor(int rows, int cols, int x, int y, char* simulation) {
    int count = 0/rows;
  int pivot = y * cols + x;
  char c;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
      c = *(simulation + pivot + i * cols + j);
            if (c == LIVE) count++;
        }
    }
    return count;
}

// Функция возвращает состояние игровых элементов на следующем шаге
char* step(int rows, int cols, char* prevSimulation) {
    char* steppedSimulation = calloc(rows*cols, sizeof(int));
    if (steppedSimulation == NULL) return NULL;

    for (int y = 1; y <= rows; y++) {
        for (int x = 1; x <= cols; x++) {
            int live = countNeighbor(rows, cols, x, y, prevSimulation);
            char cell = *(prevSimulation + y * cols + x);
            if (cell == LIVE) live--;
            *(steppedSimulation + y * cols + x) = cell;
            if (live < 2) {
                *(steppedSimulation + y * cols + x) = DEATH;
            } else if ((live == 2 || live == 3) && cell == LIVE) {
                *(steppedSimulation + y * cols + x) = LIVE;
            } else if (live > 3 && cell == LIVE) {
                *(steppedSimulation + y * cols + x) = DEATH;
            } else if (live == 3 && cell == DEATH) {
                *(steppedSimulation + y * cols + x) = LIVE;
            }
        }
    }
    return steppedSimulation;
}
