#include <stdio.h>
//#include <omp.h>
#define N 5

void imprimeSolucao(int sol[N+1][N+1]){
  int i, j;
  for(i=1; i<=N; i++){
    for(j=1; j<=N; j++){
      printf("%d\t",sol[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}



// https://www.codesdope.com/course/algorithms-knights-tour-problem/
int is_valid(int i, int j, int sol[N+1][N+1]) {
  if (i>=1 && i<=N && j>=1 && j<=N && sol[i][j]==-1)
    return 1;
  return 0;
}

int knight_tour(int sol[N+1][N+1], int i, int j, int step_count, int x_move[], int y_move[]) {
  if (step_count == N*N){
    for(i=1; i<=N; i++) {
      for(j=1; j<=N; j++) {
        printf("%d\t",sol[i][j]);
      }
      printf("\n");
    }
    printf("\n");
    return 0;
    //return 1;
  }

  int k;

 // #pragma omp parallel for firstprivate(sol, i, j, step_count, x_move, y_move)
  for(k=0; k<8; k++) {
    int next_i = i+x_move[k];
    int next_j = j+y_move[k];

    if(is_valid(i+x_move[k], j+y_move[k], sol)) {
      sol[next_i][next_j] = step_count;
      
      if(!knight_tour(sol, next_i, next_j, step_count+1, x_move, y_move)){
          sol[i+x_move[k]][j+y_move[k]] = -1; // backtracking
      }
      
      /*
      if (knight_tour(sol, next_i, next_j, step_count+1, x_move, y_move)){
      /return 1;
      }
      else{
        sol[i+x_move[k]][j+y_move[k]] = -1; // backtracking
      }
      */
    }
  }

  return 0;
}


int knight_tour2(int sol[N+1][N+1], int i, int j, int step_count, int x_move[], int y_move[]) {
  if (step_count == N*N){
    imprimeSolucao(sol);
    /*
    for(i=1; i<=N; i++) {
      for(j=1; j<=N; j++) {
        printf("%d\t",sol[i][j]);
      }
      printf("\n");
    }
    printf("\n");
    */
    return 0;
  }

  int k;

 // #pragma omp parallel for firstprivate(sol, i, j, step_count, x_move, y_move)
  for(k=0; k<8; k++) {
    int next_i = i+x_move[k];
    int next_j = j+y_move[k];

    if(is_valid(i+x_move[k], j+y_move[k], sol)) {
      sol[next_i][next_j] = step_count;
      /*
      if(!knight_tour(sol, next_i, next_j, step_count+1, x_move, y_move)){
          sol[i+x_move[k]][j+y_move[k]] = -1; // backtracking
      }
      */
      
      if (!knight_tour2(sol, next_i, next_j, step_count+1, x_move, y_move)){
         sol[i+x_move[k]][j+y_move[k]] = -1; // backtracking
      }
      else{
        return 1;
      }
    }
  }

  return 0;
}

int start_knight_tour() {
  int sol[N+1][N+1];

  int i, j;
  for(i=1; i<=N; i++) {
    for(j=1; j<=N; j++) {
      sol[i][j] = -1;
    }
  }

  int x_move[] = {2, 1, -1, -2, -2, -1, 1, 2};
  int y_move[] = {1, 2, 2, 1, -1, -2, -2, -1};

  sol[1][1] = 0; // placing knight at cell(1, 1)

    knight_tour(sol, 1, 1, 1, x_move, y_move);
    /*
  if (knight_tour(sol, 1, 1, 1, x_move, y_move)) {
    for(i=1; i<=N; i++) {
      for(j=1; j<=N; j++) {
        printf("%d\t",sol[i][j]);
      }
      printf("\n");
    }
    return 1;
  }
  */
  return 0;
}

int start_knight_tour2(int x, int y) {
  int sol[N+1][N+1];

  int i, j;
  for(i=1; i<=N; i++) {
    for(j=1; j<=N; j++) {
      sol[i][j] = -1;
    }
  }

  int x_move[] = {2, 1, -1, -2, -2, -1, 1, 2};
  int y_move[] = {1, 2, 2, 1, -1, -2, -2, -1};

  sol[x][y] = 0; // placing knight at cell(1, 1)

  //knight_tour(sol, 1, x, y, x_move, y_move);
  knight_tour2(sol, 1, x, y, x_move, y_move);
  return 0;
}

int main() {
  //printf("%d\n",start_knight_tour());
  //start_knight_tour();
  int i,j;
  for(i=0; i<5; i++){
    for(j=0; j<5; j++){
      start_knight_tour2(i, j);
    }
  }
  return 0;
}
