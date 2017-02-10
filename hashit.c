// Jordana Approvato, Jennifer Cafiero, and Catherine Javadian
// We pledge our honor that we have abided by the Stevens Honor System

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define TABLE_SIZE 101

typedef struct {
    char* keys[TABLE_SIZE];
    int num_keys;
} hash_set;

char * EMPTY = NULL;

void clear_table(hash_set *set) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (set->keys[i] != NULL && set->keys[i] != EMPTY) {
			set->keys[i] = NULL;
		}
	}
	return;
}

int hash(char *key) {
	int ch = 0;
	int hash = 0;
	int check = 0;
	while(key[check]) {
		ch += (key[check])*(check+1);
		check++;
	}
	ch *= 19;
	hash = (ch % TABLE_SIZE);
	return hash;
}

int insert_key(hash_set *set, char *key) {
	int hashk = hash(key);
	int count = 1;
	while (set->keys[hashk] != NULL) {
		if (strcmp(key, set->keys[hashk]) == 0) {
			return -1;
		}
		hashk += (count*count) + (count*23);
		count++;
		if (count == 19) {
			return -1;
		}
	}
	set->keys[hashk] = key;
	return 0;
}

int delete_key(hash_set *set, char *key) {
	int hashk = hash(key);
	int k = hashk;
	int count = 1;
	while (count != 20) {
		if (set->keys[k] == NULL) {
			return -1;
		}
		if (strcmp(key, set->keys[k]) == 0) {
			free(set->keys[k]);
			char * EMPTY = NULL;
			set->keys[k] = EMPTY;
			return 0;
		}
		k = (hashk + (count*count) + (count*23))%TABLE_SIZE;
		count++;
	}
	return 0;
}

void display_keys(hash_set *set) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (set->keys[i] != NULL) {
			printf("%i:",i);
			printf("%s\n",set->keys[i]);
		}
	}
	return;
}

int main() {
	int lines;
	int ops;
	hash_set * hash = (hash_set *)malloc(sizeof(hash_set));
	for (int i = 0; i > TABLE_SIZE; i++) {
		hash->keys[i] = NULL;
	}
	scanf("%d", &lines);
	while (lines > 0) {
		scanf("%d", &ops);
		while (ops > 0) {
			char * input = (char *)malloc(sizeof(char)*19);
			scanf("%s", input);
			char *key = (char *)malloc(sizeof(char)*15);
			char check = input[0];
			strncpy(key, input+4, 15);
			if (check == 'A') {
				insert_key(hash, key);
				hash->num_keys++;
			} else {
				delete_key(hash, key);
				hash->num_keys--;
			}
			ops--;
		}
		printf("%i\n", hash->num_keys);
		display_keys(hash);
		clear_table(hash);
		lines--;
	}
	return 0;
}



