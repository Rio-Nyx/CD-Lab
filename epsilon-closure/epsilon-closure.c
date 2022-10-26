#include <stdio.h>

static int num_states;

void dfs(int transition_table[][num_states], int epsilon_closure[][num_states],
         int visited[], int i, int k) {
  for (int j = 0; j < num_states; j++) {
    if (visited[j] == 0 && transition_table[k][j] == -1) {
      epsilon_closure[i][j] = -1;
      visited[j] = 1;
      dfs(transition_table, epsilon_closure, visited, i, j);
    }
  }
}

void display(int epsilon_closure[][num_states]) {
  printf("displaying epsilon closures: \n");
  for (int i = 0; i < num_states; i++) {
    printf("%d -> ", i);
    for (int j = 0; j < num_states; j++) {
      if (epsilon_closure[i][j] == -1) {
        printf(" %d ", j);
      }
    }
    printf("\n");
  }
}

int main() {
  printf("Enter the number of states: ");
  scanf("%d", &num_states);
  int transition_table[num_states][num_states];
  int epsilon_closure[num_states][num_states];
  int initial, final, value;
  int visited[num_states];
  int no_trans;
  printf("Enter the number of transitions : ");
  scanf("%d", &no_trans);
  printf("Enter intial state | final state | input(-1 for epsilon)\n");
  for (int i = 0; i < no_trans; i++) {
    scanf("%d%d", &initial, &final);
    scanf("%d", &value);
    if (transition_table[initial][final] != -1) {
      transition_table[initial][final] = value;
    }
  }
  int change = 1;
  for (int i = 0; i < num_states; i++) {
    for (int j = 0; j < num_states; j++) {
      visited[j] = 0;
    }
    epsilon_closure[i][i] = -1;
    dfs(transition_table, epsilon_closure, visited, i, i);
  }
  display(epsilon_closure);
}
