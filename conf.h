#ifndef CONF_H_
#define CONF_H_

typedef struct {
    char *SHAREDIR;
    char *LOGFILE;
    char *MOTD;
} settings_t;

char *gethome();
char *fixpath(char *path);
void readsetconf();
settings_t settings;

// struct settings_t;
// settings_t *readsetconf();

#endif // CONF_H_
