#define _DEFAULT_SOURCE
#include <errno.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include "logger.h"
#include "io.h" 
#include "conf.h"
#include "menu.h"

void enumdir(void *env, void (*callback)(void *env, const char *str)) {
    logger("Enumerating directory", logfile);

    struct dirent **eps;
    int n = scandir (settings.SHAREDIR, &eps, NULL, alphasort);
 
    if(n >= 0) {
        int count;
        for (count = 2; count < n; ++count) {
            (*callback)(env, (eps[count]->d_name));
        }
    }
    else {
        logger(strerror(errno), logfile);
    }
}

void listdir(void *env, const char *str) {
    puts(str);
}

void dumpdir(void *env, const char *str) {
    char f_name[strlen(settings.SHAREDIR) + strlen(str) + 1];
    snprintf(f_name, sizeof f_name, "%s%s", settings.SHAREDIR, str);
    // char *f_name = strcat(settings.SHAREDIR, str);
    FILE *fp;
    // printf("\n%s:\n", f_name);
    printf("\n%s:\n", str);
    fp = fopen(f_name, "r");
    if(fp) {
        char line[2];
        while (fgets(line, 2, fp) != NULL) {
            printf("%s", line);
        }
        fclose(fp);
    }
    else {logger(strerror(errno), logfile);
    }
}

/*
int main(void) {
    enumdir(NULL,&listdir);
    enumdir(NULL,&dumpdir);
    return 0;
}
*/
