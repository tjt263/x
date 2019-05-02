#include <stdio.h>
#include <time.h>
#include "logger.h"
#include "io.h" 
#include "conf.h"
#include "menu.h"

char *timestamp()
{
    time_t ltime;
    ltime = time(NULL);
    return asctime(localtime(&ltime));
}

void logger(char *message, FILE *logfile)
{
    
    fprintf(logfile, "%s - %s\n\n", timestamp(), message);
    fflush(logfile);
}

/*
int main()
{
    FILE *logfile = fopen("./file.log", "a");
    logger("test message", logfile);
}
*/
