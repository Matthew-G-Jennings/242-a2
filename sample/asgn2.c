#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>
#include <string.h>
#include "mylib.h"
#include "tree.h"

/**
 * comment
 *
 * @author Jeremy Shanks, Will Johnstone, Matthew Jennings.
 */

/**
 * Prints a help message describing how to use the program to stdout.
 */
static void help(){

    printf("Usage: ./asgn2 [OPTION]... <STDIN>\n");
    printf("\n");
    printf("Perform various operations using a binary tree.  By default, words\n");
    printf("are read from stdin and added to the tree, before being printed out\n");
    printf("alongside their frequencies to stdout.\n");
    printf("\n");
    printf(" -c FILENAME  Check spelling of words in FILENAME using words\n");
    printf("\t\t\t  read from stdin as the dictionary.  Print timing\n");
    printf("\t\t\t  info & unknown words to stderr (ignore -d & -o)\n");
    printf(" -d\t\t\t  Only print the tree depth (ignore -o)\n");
    printf(" -f FILENAME  Write DOT output to FILENAME (if -o given)\n");
    printf(" -o\t\t\t  Output the tree in DOT form to file 'tree-view.dot'\n");
    printf(" -r\t\t\t  Make the tree an RBT (the default is a BST)\n");
    printf("\n");
    printf(" -h\t\t\t  Print this message\n");
    printf("\n");

}

/**
 * Prints out words and their respecitve frequencies to stdout.
 *
 * @param freq frequency (number of occurences of that word).
 * @param word word stored at the location in tree.
 */
static void print_info(int freq, char *word){

    printf("%-4d %s\n", freq, word);

}

/**
 * Initilizes the tree and takes input from stdin.
 *
 * Command line argument interpretation happens here.
 *
 * Performs actions based on the given arguments.
 *
 * @param argc the number of arguments passed to the program.
 * @param argv a two dimensional character array with that hold the arguements
 * passed to the program.
 *
 * @return EXIT_SUCCESS if successful EXIT_FAILURE if not.
 */
int main(int argc, char **argv) {

    /* to add comments to most variables. */
    clock_t start, end;
    tree t;
    char option;
    char word[256];
    const char *optstring = "c:df:orh";
    int print_flag = 0;
    int file_flag = 0;
    int dot_flag = 0;
    char input_filename[256];
    char dot_filename[256];
    int unknown_words = 0;
    FILE *document;
    FILE *dotout;
    double fill_time;
    double search_time;


    while((option = getopt(argc, argv, optstring)) != EOF) {
        switch(option) {
            case 'c':
                /* Check the spelling of words in filename using words read from
                   stdin as the dictionary. Print all unknown words to stdout.
                   Print timing information and unknown word count to stderr.
                   When this option is given then the -d and -o options should
                   be ignored. */
                file_flag = 1;
                sscanf(optarg, "%s", input_filename);
                break;

            case 'd':
                /* Print the depth of the tree to stdout and don’t do anything
                    else. */
                print_flag = 1;
                break;

            case 'f':
                /* Write the "dot" output to filename instead of the default
                  file name if -o is also given. */
                sscanf(optarg, "%s", dot_filename);
                break;

            case 'o':
                /* Output a representation of the tree in "dot" form to the file
                ‘tree-view.dot’ using the functions given in output-dot.txt. */
                dot_flag = 1;
                strcpy(dot_filename, "tree-view.dot");
                break;

            case 'r':
                /* Make the tree an rbt instead of the default bst. */
                tree_type = RBT;
                break;

            case 'h':
                help();
                exit(EXIT_SUCCESS);

            default:
                help();
                exit(EXIT_FAILURE);
        }
    }

    if(tree_type == RBT){

        /* if the RBT flag has been set. */
        t = tree_new(RBT);

    } else {

        /* if no flag. */
        t = tree_new(BST);

    }

    /**
     * This populates the tree with words from the dictionary. We essentially
     * create a dictionary tree.
     *
     * Later, the second arguement (after -c) will be compared against the
     * dictionary tree.
     *
     * If the contents of the input file (second arguement after -c) cannot
     * be found in the dictionary tree, increment unknown_words and print the
     * unknown word to stdout.
     */
    start = clock(); /* starts timer for fill_time. */
    while (getword(word, sizeof word, stdin) != EOF) {
        t = tree_insert(t, word);
    }

    end = clock(); /* stops timer for fill_time. */
    fill_time = (end - start) / (double)CLOCKS_PER_SEC; /* calculates time taken to fill. */

    /** if the print flag is set, print the depth of the tree to stdout and don’t do anything else. */
    if(print_flag == 1){

        printf("%d", tree_depth(t));
        return EXIT_SUCCESS;

    }

    if(file_flag == 1){
        if(NULL == (document = fopen(input_filename, "r"))){
            fprintf(stderr, "Failed to open file %s\n", input_filename);
            return EXIT_FAILURE;
        } else {

            start = clock();

            while(getword(word, sizeof word, document) != EOF){

                if(tree_search(t, word) == 0){

                    fprintf(stdout, "%s\n", word);
                    unknown_words++;

                }
            }

            end = clock();
            search_time = (end - start) / (double)CLOCKS_PER_SEC;
        }

        /** timer stuff goes here. */
        fprintf(stderr, "Fill time     : %f\n", fill_time);
        fprintf(stderr, "Search time   : %f\n", search_time);

        /** this statement should only execute with the -c flag. */
        fprintf(stderr, "Unknown words = %d\n", unknown_words);
    } else if (dot_flag == 1) {
        if(NULL == (dotout = fopen(dot_filename, "w"))){
            fprintf(stderr, "Failed to open file for dot out %s\n",
                    dot_filename);
            return EXIT_FAILURE;
        } else {
            fprintf(stderr, "Creating dot file '%s'\n",
                    dot_filename);
            tree_output_dot(t, dotout);
        }
    } else {

        /** psuedo no flags zone. */
        tree_preorder(t, print_info);
    }
    tree_free(t);

    return EXIT_SUCCESS;
}
