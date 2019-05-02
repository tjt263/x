#define _DEFAULT_SOURCE                             // prevents warnings on some systems
                                                    // because of dirent.h (GNU/BSD/POSIX)
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <errno.h>
#include "logger.h"
#include "io.h" 
#include "conf.h"
#include "menu.h"

void draw_menu();                                   // the menu prototype
void checkinput();                                   // main logic - input parser and validator
void opt1(int a);                                   // option 1 prototype
void opt2(int b);                                   // option 2 prototype
void opt3(int c);                                   // option 3 prototype
void freedom();                                     // freedom! prototype

int main(void) {                                    // start main()

    readsetconf();                                  // read settings configuration
    draw_menu();                                    // display the menu for the first time
    printf("\n");                                   // skip a line
    logfile = fopen(settings.LOGFILE, "a");         // create FILE pointer object: "logfile"
    logger("Program starts", logfile);              // log program start
    checkinput();                                   // input validation loop
    logger("Program ends", logfile);                // log program end // just in case some bad // will probably
    freedom();                                      // free settings   // input sneaks through  // never happen
}                                                   // end main

void draw_menu() {                                  // main menu function
    system("clear");                                // bash builtin clear
    printf("=====================\n");              // draw the main menu
    printf("  M A I N   M E N U  \n");              // """"""""""""""""""
    printf("=====================\n");              // """"""""""""""""""
    printf("%s\n", settings.MOTD);                  // message of the day
    printf("                     \n");              // draw the main menu
    printf("1. List shared files.\n");              // """"""""""""""""""
    printf("2. Dump shared files.\n");              // """"""""""""""""""
    printf("3. Quit.             \n");              // """"""""""""""""""
    printf("=====================\n");              // """"""""""""""""""
}                                                   // end main menu func

void checkinput() {
    void (*f[3])(int) = {opt1, opt2, opt3};         // initialize array of pointers to functions
    size_t choice;                                  // variable to hold user's choice

    while(1) {                                      // start while loop
        char buf[3];                                // fgets is the key to getting this right
        if (fgets(buf, sizeof(buf), stdin) == 0) {  // get user input with fgets()
            logger(strerror(errno), logfile);       // log any errors - will probably never happen
        } else {                                    // this whole block validates input
            draw_menu();                            // redraw menu
            int choice;                             // and keeps the menu running smoothly
            if (sscanf(buf, "%d", &choice) != 1) {  // extract the number from fgets() with sscanf()
                logger(strerror(errno), logfile);   // log any errors - will probably never happen
                printf("\n");                       // skip a line on bad input for consistent layout
            } else {                                // more input validation
                if (choice >= 1 && choice <= 3) {   // valid inputs are 1,2,3
                    (*f[choice-1])(choice);         // invoke function at location of choice in array
                }                                   // parse choice as an argument
            }
        }
    }                                               // end while loop
}

void opt1(int a) {                                  // list directory - output list of shared filenames
    printf("\n");                                   // skip a line
    logger("Listing directory", logfile);           // log action
    enumdir(NULL,&listdir);                         // enumerate and list
    printf("\n");                                   // skip a line
}                                                   // end option 1

void opt2(int b) {                                  // dump directory - output contents of shared files
    logger("Dumping directory", logfile);           // log action
    enumdir(NULL,&dumpdir);                         // enumerate and dump
    printf("\n");                                   // skip a line
}                                                   // end option 2

void opt3(int c) {                                  // quit program
    printf("\n");                                   // skip a line
    logger("Program quit", logfile);                // log action
    freedom();                                      // free settings
    system("clear");                                // clear screen for clean finish upon exit
    exit(0);                                        // exit successfuly
}                                                   // end option 3

void freedom() {                                    // free memory allocated for settings struct
    free(settings.SHAREDIR);                        // free SHAREDIR
    free(settings.LOGFILE);                         // free LOGFILE
    free(settings.MOTD);                            // free MOTD
}                                                   // end freedom!

