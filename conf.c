#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pwd.h>
#include <sys/types.h>
#include "logger.h"
#include "io.h" 
#include "conf.h"
#include "menu.h"

/*
typedef struct {
    char *SHAREDIR;
    char *LOGFILE;
    char *MOTD;
} settings_t;
*/

char *slashmerge(char *path) {
    if (path) {
        const char *src = path;
        char *dst = path;
        while ((*dst = *src) != '\0') {
            do {
                src++;
            } while ((*dst == '/') && (*src == '/'));
            dst++;
        }
    }
    return path;
}

char *fixpath(char *path) {
    char *homedir = gethome();
    char *fixedpath;
    if (path[0] == '~') {
        fixedpath = calloc(strlen(homedir) + strlen(path) + 4, sizeof(char));
        sprintf(fixedpath, "%s/%s", homedir, path + 1);
    } else {
        fixedpath = strdup(path);
    }
    free(homedir);
    fixedpath = slashmerge(fixedpath);
    return(fixedpath);
}

char *gethome() {
    struct passwd *user;
    uid_t userid;
    char *homedir = strdup(getenv("HOME"));

    if (homedir) {
        return homedir;
    } else {
        userid = getuid();
        user = getpwuid(userid);
        if (user) {
            return strdup(user->pw_dir);
        } else {
            return homedir;
        }
    }
}

// settings_t 
void readsetconf() {
    FILE* fp;
    char *homedir = gethome();
    char setconf[256], line[256];
    char* key;

    strcpy(setconf, homedir);
    strcat(setconf, "/settings.conf");

    fp = fopen(setconf, "r");
    if(!fp) {
        switch(errno) {
            case ENOENT: {
                perror("File ~/settings.conf not found");
                printf("%s\n", "Creating ~/settings.conf with default values");
                fp = fopen(setconf, "w+");
                if(!fp) {
                    perror("Failed to create ~/settings.conf");
                    exit(1);
                }
                // write default file contents here //
                fprintf(fp, "SHAREDIR=~/share\n");
                fprintf(fp, "LOGFILE=~/file.log\n");
                fprintf(fp, "MOTD= Message of the day!\n");
                // LOG THIS! //
                break;
            }
            default:
                perror("Failed to open file");
                exit(1);
        }
    }
    // read existing config here //
    // settings = (settings_t*) malloc(sizeof(settings_t));
    // memset(settings,0,sizeof(settings_t));
   
    fseek(fp, 0, SEEK_SET);
    while(fgets(line, 256, fp) != NULL) {
        line[strlen(line)-1] = '\0';
        key = strtok(line, "=");
        if(key != NULL && key[0] != '#') {
            if(strcmp(key, "SHAREDIR") == 0) {
                settings.SHAREDIR = fixpath(strtok(NULL, "="));
                strcat(settings.SHAREDIR, "/");
            }
            else if(strcmp(key, "LOGFILE") == 0) {
                settings.LOGFILE = fixpath(strtok(NULL, "="));
            }
            else if(strcmp(key,"MOTD") == 0) {
                settings.MOTD = fixpath(strtok(NULL, "="));
            }
        }
    }
    // printf("%s\n", settings.SHAREDIR);
    // printf("%s\n", settings.LOGFILE);
    // printf("%s\n", settings.MOTD);
    return;
}

