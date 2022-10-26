/*
	epsilon nfa to nfa conversion
	1. find epsilon closures
	2. for each epsilon closure, find transition for each state
	
*/

#include <stdio.h>

void check_for_q_inp(int transition_table[][3],int no_trans,int input){

}

void conversion(int epsilon_closure[num_states][num_states],int transition_table[][3]){
	printf("Enter the number of inputs: ");
	scanf("%d",&num_inputs);
	int inputs[num_inputs];
	printf("Enter all inputs: ");
	for(int i=0;i<num_inputs;i++){
		scanf("%d",&inputs[i]);
	}
	for(int i=0;i<num_states;i++){
		// for each state
		// find EPSILON
		for (int j = 0; j < num_states; j++) {
      		if (epsilon_closure[i][j] == -1) {
      			// for each closure of state
      			for(int k=0;k<num_inputs;k++){
      				// for each input
      				// ABOVE
      				for(int l=0;l<no_trans;l++){
						if(transition_table[i][0]==i && transition_table[i][1]==j && transition_table[i][2]==inputs[k]){
							// if input add all EPSILON closure and for each epsilon closure check from ABOVE
							if(i!=j){
								// add to transition transition_table
							}
						}
					}

      			}
      		}
    	}
	}
}

int main(){
	conversion();

	return 0;
}