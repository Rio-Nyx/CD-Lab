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

void handle_transitions() {}

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
    transition_table[i][0] = initial;
    transition_table[i][1] = final;
    transition_table[i][2] = value;
  }
  int inputs[100];
  int no_inputs;
  printf("Enter the number of inputs: ");
  scanf("%d", &no_inputs);
  printf("Enter the inputs\n");
  for (int i = 0; i < no_inputs; i++) {
    scanf("%d", &inputs[i]);
  }
  int dfa_table[100][100][100];
  // for each transition
  for (int i = 0; i < no_trans; i++) {
    if (transition_table[i][0] == 0) {
      for (int j = 0; j < no_inputs; j++) {
        if (transition_table[i][2] == inputs[j]) {
          dfa_table[0][0][0] = 1;
          dfa_table[0][0][1] = 0;
          dfa_table[0][j + 1][0]++;
          int len = dfa_table[0][j + 1][0];
          dfa_table[0][j + 1][len] = transition_table[i][1];
        }
      }
    }
  }
  for (int i = 0; i < no_trans; i++) {
    if (transition_table[i][0] == 0) {
      for (int j = 0; j < no_inputs; j++) {
      }
    }
    handle_transitions();
  }

  int main() { start(); }
