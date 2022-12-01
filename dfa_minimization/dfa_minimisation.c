/*
   minimise the dfa using myhill-nerode theorem
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 
static int mt_table[10][10];
int num_states;
int no_trans;
int inputs[10];
int num_inputs;
int transition_table[20][3];
int num_final_states;
int final_states[10];
 
 
bool be_marked(int intial, int final){
	int first_state,second_state;
	for(int i=0;i<num_inputs;i++){
		first_state = second_state = -1;
		for(int j=0;j<no_trans;j++){
 
			if(transition_table[j][0]==intial && transition_table[j][2]==inputs[i]){
				first_state = transition_table[j][1];
			}
			if(transition_table[j][0]==final && transition_table[j][2]==inputs[i]){
				second_state = transition_table[j][1];
			}
		}
		if(first_state!=-1 && second_state!=-1){
			break;
		}
	}
	if(first_state!=-1 && second_state!=-1){
		if(mt_table[first_state][second_state]==1){
			return true;
		}
	}
	return false;
}
 
bool is_final(int state){
	for(int i=0;i<num_final_states;i++){
		if(state == final_states[i]){
			return true;
		}
	}
	return false;
}
 
int main(){
	printf("Enter the number of states: ");
	scanf("%d", &num_states);
 
	int epsilon_closure[num_states][num_states];
	int initial, final, value;
	int final_state;
	int visited[num_states];
	bool is_to_be_marked;
	printf("Enter the number of transitions : ");
	scanf("%d", &no_trans);
	printf("Enter the number of inputs: ");
	scanf("%d",&num_inputs);
	printf("Enter the inputs: ");
	for(int i=0; i<num_inputs; i++){
		scanf("%d",&inputs[i]);
	}
	printf("Enter the number of final states: ");
	scanf("%d",&num_final_states);
	printf("Enter the final states: ");
	for(int i=0; i<num_final_states; i++){
		scanf("%d",&final_states[i]);
	}
  	printf("Enter intial state | final state | input(-1 for epsilon)\n");
  	for (int i = 0; i < no_trans; i++) {
    	scanf("%d%d", &initial, &final);
    	scanf("%d", &value);
		transition_table[i][0] = initial;
	    transition_table[i][1] = final;
	    transition_table[i][2] = value;
	    is_to_be_marked = (is_final(initial) && !is_final(final)) || (!is_final(initial) && is_final(final));
	  //   if(is_to_be_marked){
			// mt_table[initial][final] = 1;
			// mt_table[final][initial] = 1;
	  //   }
    }
    for(int i=1;i<num_states;i++){
	for(int j=0;j<i;j++){
		is_to_be_marked = (is_final(i) && !is_final(j)) || (!is_final(i) && is_final(j));
		if(is_to_be_marked){
			mt_table[i][j] = 1;
			mt_table[i][j] = 1;
		}	
	}
			
    }
    int count = 0;
    while(1){
    	if(count>num_states*num_states){
    		break;
    	}
		for(int i=1;i<num_states;i++){
			for(int j=0;j<i;j++){
			count++;
				// if table not marked
				if(mt_table[i][j]!=1){
					// if table can be marked
					if(be_marked(i,j)){
						mt_table[i][j] = 1;
						count = 0;
					}
				}
			}
		}
	}
	printf("unmarked pairs(Pairs to be combined)\n");
	for(int i=1;i<num_states;i++){
		for(int j=0;j<i;j++){
				// if table not marked
				if(mt_table[i][j]!=1){
					printf("%d,%d\n",i,j);
				}
			}
		}
 
	//for(int i=0;i<no_trans;i++){
		//printf("%d %d %d\n",transition_table[i][0],transition_table[i][1],transition_table[i][2])
	//}
	return 0;
}
