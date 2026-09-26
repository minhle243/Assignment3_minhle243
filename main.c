#include<stdio.h>
#include<stdlib.h>
#include"array.h"

void output_array(Array *a);
void shift_array(Array *a);
Array *average_adjacent(Array *a);

int main(int arg_count, char *arg_vector[]){
	if(arg_count != 2){
		printf("Error: missing size argument \n");
		printf("Usage example: ./ 10 \n");
		
		return 1;
	}
	
	int size = atoi(arg_vector[1]);
	
	if(size <= 0){
		printf("ERROR: Size must be a positive \n");
		return 1;
	}
	
	//Allocate memory for structure
	Array *input_array = (Array *)malloc(sizeof(Array));
	if(input_array == NULL){
		fprintf(stderr, "Memory allocation failed. \n");
		return 1;
	}
	
	input_array->size = size;
	input_array->data = (double *)malloc(size * sizeof(double));
	
	if(input_array->data == NULL){
		fprintf(stderr, "Memory allocation failed. \n");
		free(input_array); 
		return 1;
	} //cleanup 
	
	
	for(int i = 0; i < size; i++){
		input_array-> data[i] = (double)(i + 1);
	}
	
	//step 4.a
	printf("Initial state: \n");
	output_array(input_array);
	
	
	printf("\nShift left: \n");
	shift_array(input_array);
	output_array(input_array);
	
	
	printf("\nAverage adjacent:");
	Array *averaged_array = average_adjacent(input_array);
	
	
	printf("\nOriginal array: ");
	output_array(input_array);
	
	
	printf("Averaged array (new size: %d): ",averaged_array->size);
	output_array(averaged_array);
	
	
	//free all allocated memory
	free(input_array->data);
	free(input_array);
	
	if(averaged_array != NULL){
		free(averaged_array->data);
		free(averaged_array);
	}
	

	printf("\nRun Successful!");
	
	return 0;
}


void output_array(Array *a){
	if(a == NULL || a->data == NULL){
		printf("empty array! \n");
		return;
	}
	printf("[");
	for(int i = 0; i < a->size; i++){
		printf(" %.2f ", a->data[i]);
	}
	printf("] \n");
}

void shift_array(Array *a){
	if(a == NULL || a->size <= 1){
		return;
	}
	double first_val = a->data[0];
	
	for(int i = 0; i < a->size - 1; i++){
		a->data[i] = a->data[i + 1];
	}
	
	a->data[a->size - 1] = first_val;
}

Array *average_adjacent(Array *a){
	if(a == NULL)return NULL;
	
	 int new_size = a->size / 2;
	 
	 Array *result = (Array *)malloc(sizeof(Array));
	 if(result == NULL)return NULL;
	 
	 result->size = new_size;
	 result->data = (double *)malloc(new_size * sizeof(double));
	 
	 
	 if(result->data == NULL){
	 	free(result);
	 	return NULL;
	 }
	 
	 
	for(int i = 0; i < new_size; i++){
		double val1 = a->data[2 * i];
		double val2 = a->data[(2 * i) + 1];
		
		result->data[i] = (val1 + val2) / 2.0;
	}
	return result;
}

