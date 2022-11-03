
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

void execute(char** args){
    if (strcmp(args[0], "cd") == 0){
        
        chdir(args[1]);
        printf("Changing directories to: %s\n", args[1]);

    }else if (strcmp(args[0], "quit") == 0){
        printf("Quitting...\n");
        exit(0);

    }else {
        if (fork() == 0){
            int status_code = execvp(args[0], args);

            if (status_code == -1){
                printf("Your Command Failed\n");
            }
        }
    }
}


char** parse(char* input){
    // Parsing the input by breaking it up by spaces. FOr Example, parsing `Hello World` would return `[Hello, World]`

    int all_tokens_buffer = 100;
    char** all_tokens = malloc(all_tokens_buffer * sizeof(char*));
    int all_tokens_counter = 0;

    int current_token_buffer = 1024;
    char* current_token = malloc(current_token_buffer * sizeof(char));
    int current_token_counter = 0;


    for (int i = 0; i < strlen(input); i++){
        
        char character = input[i];

        if (all_tokens_buffer + 1 > all_tokens_buffer){
            all_tokens_buffer += 100;
            all_tokens = realloc(all_tokens, all_tokens_buffer * sizeof(char*));
        

        if (all_tokens_buffer + 1 > all_tokens_buffer){
            all_tokens_buffer += 1024;
            all_tokens = realloc(current_token, current_token_buffer);
        }

        all_tokens[all_tokens_counter] = current_token;
        all_tokens_counter++;

        current_token = malloc(current_token_buffer * sizeof(char*));
        current_token_counter = 0;
    }

     else if (character == '\n'){
        if(all_tokens_counter + 2 > all_tokens_buffer){
            all_tokens_buffer += 100;
            all_tokens = realloc(all_tokens, all_tokens_buffer * sizeof(char*));
        }

        if(all_tokens_counter + 1 > current_token_buffer){
            all_tokens_buffer += 1024;
            all_tokens = realloc(current_token, current_token_buffer);
        }

        all_tokens[all_tokens_counter] = current_token;
        all_tokens_counter++;

        all_tokens[all_tokens_counter] = NULL;
        break;

    } else {
        if (current_token_counter + 1 > current_token_buffer){
            current_token_buffer += 1024;
            current_token = realloc(current_token, current_token_buffer);
        }

        current_token[current_token_counter] = character;
        current_token_buffer++;
    }
    
    }

    return all_tokens;
}


char* read_line(){
    //Taking input from stdin with the getline() function

    char* buffer;
    size_t buffsize = 100;
    size_t line;

    buffer = (char*) malloc(buffsize * sizeof(char));

    if (buffer == NULL){
        printf("Error: Couldn't allocate Memory\n");
        exit(1);
    }

    line = getline(&buffer, &buffsize, stdin);

    return buffer;
}

int main(){
    // This is the main loop of our shell
    printf("Welcome to the Shell\n");
    printf("Made by Dev Nderitu\n");
    printf("\n");

    while(true){
        char* input  = read_line();

        char** parsed = parse(input);

        execute(parsed);

        free(input);
        free(parsed);
    }

    return 0;
}
