#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Trie{
	int count;
	struct Trie *letters[26];
};

//this function helps initalize a new node for trie
struct Trie* newNode(){
    struct Trie* node = (struct Trie*)malloc(sizeof(struct Trie));
	//every node starts at count = 0;
	node->count = 0;
    for (int i = 0; i < 26; i++) {
        node->letters[i] = NULL;
    }
 
    return node;
}

void insert(struct Trie **ppTrie, char *word){
	struct Trie* current = *ppTrie;
	while(*word != '\0' /*|| *word != NULL*/){
		//if letter hasn't been added to the trie then create a new node for the letter
		if(current->letters[*word - 'a'] == NULL){
			current->letters[*word - 'a'] = newNode();
		}
		//go to the next letter
		current = current->letters[*word - 'a'];
		
		word++;
	}
	//reached the end of the word in the trie make count of this node = 1 since this is a complete word
	current->count = 1;
}

int numberOfOccurances(struct Trie *pTrie, char *word){
	//if trie is empty return 0
	if(pTrie == NULL){
		return 0;
	}
	
	struct Trie* current = pTrie;
	while(*word != '\0' /*|| *word != NULL*/){
		//traverse the word to the bottom of trie
		current = current->letters[*word - 'a'];
		//if the trie cannot go further due to a null node then the word isn't in the trie(return 0)
		if(current == NULL){
			return 0;
		}
		
		word++;
	}
	//if the while loop runs to the end of the word then this return should return 1
	return current->count;
}

struct Trie *deallocateTrie(struct Trie *pTrie){
	
	if(pTrie){
		for (int i = 0; i < 26; i++) {
			if(pTrie->letters[i]){
				deallocateTrie(pTrie->letters[i]);
			}
			
		}
		free(pTrie);
	}
	
	return NULL;
}


int main(void){
    //read the number of the words in the dictionary
    // parse line  by line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	
	struct Trie *head = newNode();
	for(int i = 0; i < 5; i++){
		insert(&head, pWords[i]);
	}
	
    for (int i=0;i<5;i++){
        printf("\t%s : %d\n",pWords[i], numberOfOccurances(head, pWords[i]));
    }
    head = deallocateTrie(head);
    if (head != NULL){
		printf("There is an error in this program\n");
	}
    return 0;
}