#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int SYNAPSE_COUNT = 5;

int* get_initial_weights() {
    int* weight = malloc(sizeof(int) * SYNAPSE_COUNT);
    for(int i = 0; i < SYNAPSE_COUNT; i++) {
        weight[i] = 1;
    }

    return weight;
}

int get_user_response() {
    while(1) {
        int c = getchar();
        switch(c) {
            case 'n':
                return 0;
                break;
            case 'y':
                return 1;
                break;
        }
    }
}

int* get_signals_from_user() {
    int* signal = malloc(sizeof(int) * SYNAPSE_COUNT);
    for(int i = 0; i < SYNAPSE_COUNT; i++) {
        printf("fire synapse %i? (y/n)", i);
        signal[i] = get_user_response();
        puts("");
    }

    return signal;
}

int get_sum(int* signal, int* weight) {
    int sum = 0;
    for(int i = 0; i < SYNAPSE_COUNT; i++) {
        sum += weight[i] * signal[i];
    }

    return sum;
}

int get_threshold(int* weight) {
    int sum = 0;
    for(int i = 0; i < SYNAPSE_COUNT; i++) {
        sum += weight[i];
    }

    return sum / 2;
}

void increase_weights(int* signal, int* weight) {
    for(int i = 0; i < SYNAPSE_COUNT; i++) {
        if(signal[i] == 1) {
            weight[i] += 1;
        }
    }
}

void print_synapses(int* weight) {
    for(int i = 0; i < SYNAPSE_COUNT; i++) {
        printf("%i ", weight[i]);
    }
}

int main(int argc, char** argv) {
    int* weight = get_initial_weights();
    while(1) {
        int* signal = get_signals_from_user();
        int sum = get_sum(signal, weight);
        int threshold = get_threshold(weight);
        increase_weights(signal, weight);
        print_synapses(weight);

        printf("threshold: %i\n", threshold);
        printf("sum: %i\n", sum);
        if(sum >= threshold) {
            puts("neuron fired");
        }
        
        free(signal);
    }
}
