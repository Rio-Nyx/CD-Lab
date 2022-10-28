#include <stdio.h>

static int num_states;
static int no_trans;

int new_transition_table[100][3];
static int new_no_trans = 0;

int epsilon_exists(int transition_table[][num_states], int no_trans, int k,
                   int j) {
  for (int i = 0; i < no_trans; i++) {
    if (transition_table[i][0] == k && transition_table[i][1] == j &&
        transition_table[i][2] == -1)
      return 0;
  }
  return -1;
}

int transition_exists(int transition_table[][num_states], int no_trans, int k,
                      int j, int trans_input) {
  for (int i = 0; i < no_trans; i++) {
    if (transition_table[i][0] == k && transition_table[i][1] == j &&
        (transition_table[i][2] == -1 || transition_table[i][2] == trans_input))
      return 0;
  }
  return -1;
}

void dfs(int transition_table[][num_states], int epsilon_closure[][num_states],
         int visited[], int i, int k) {
  for (int j = 0; j < num_states; j++) {
    if (visited[j] == 0 &&
        epsilon_exists(transition_table, no_trans, k, j) == 0) {
      epsilon_closure[i][j] = -1;
      visited[j] = 1;
      dfs(transition_table, epsilon_closure, visited, i, j);
    }
  }
}

void dfs_conversion(int transition_table[][num_states],
                    int epsilon_closure[][num_states], int visited[], int i,
                    int k, int trans_input) {
  for (int j = 0; j < num_states; j++) {
    if (visited[j] == 0 &&
        transition_exists(transition_table, no_trans, k, j, trans_input) == 0 &&
        (epsilon_exists(transition_table, no_trans, k, j) != 0 ||
         (new_no_trans > 0 &&
          epsilon_exists(transition_table, no_trans, k, j) == 0 &&
          new_transition_table[new_no_trans - 1][0] == i))) {
      new_transition_table[new_no_trans][0] = i;
      new_transition_table[new_no_trans][1] = j;
      new_transition_table[new_no_trans][2] = trans_input;
      // printf("%d  %d   %d\n", new_transition_table[new_no_trans][0],
      // new_transition_table[new_no_trans][1],
      // new_transition_table[new_no_trans][2]);
      new_no_trans++;
      visited[j] = 1;
      dfs_conversion(transition_table, epsilon_closure, visited, i, j,
                     trans_input);
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

int start() {
  printf("Enter the number of states: ");
  scanf("%d", &num_states);
  int transition_table[num_states][num_states];
  int epsilon_closure[num_states][num_states];
  int initial, final, value;
  int visited[num_states];

  printf("Enter the number of transitions : ");
  scanf("%d", &no_trans);
  printf("Enter intial state | final state | input(-1 for epsilon)\n");
  for (int i = 0; i < no_trans; i++) {
    scanf("%d%d", &initial, &final);
    scanf("%d", &value);
    if (transition_table[initial][final] != -1) {
      transition_table[i][0] = initial;
      transition_table[i][1] = final;
      transition_table[i][2] = value;
    }
  }
  int inputs[100];
  int no_inputs;
  printf("Enter the number of inputs: ");
  scanf("%d", &no_inputs);
  printf("Enter the inputs\n");
  for (int i = 0; i < no_inputs; i++) {
    scanf("%d", &inputs[i]);
  }
  int change = 1;
  for (int i = 0; i < num_states; i++) {
    for (int j = 0; j < num_states; j++) {
      visited[j] = 0;
    }
    epsilon_closure[i][i] = -1;
    dfs(transition_table, epsilon_closure, visited, i, i);
  }
  for (int i = 0; i < num_states; i++) {
    for (int k = 0; k < no_inputs; k++) {
      for (int j = 0; j < num_states; j++) {
        visited[j] = 0;
      }
      dfs_conversion(transition_table, epsilon_closure, visited, i, i,
                     inputs[k]);
    }
  }
  display(epsilon_closure);
  printf("printing conversions\n");
  for (int i = 0; i < new_no_trans; i++) {
    printf("%d  %d   %d\n", new_transition_table[i][0],
           new_transition_table[i][1], new_transition_table[i][2]);
  }
  // display(epsilon_closure);
  // return epsilon_closure;
}

int main() { start(); }
