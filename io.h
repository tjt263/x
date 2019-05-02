#ifndef IO_H_
#define IO_H_

void enumdir(void *env,void (*callback)(void *env,const char *str));
void listdir(void *env,const char *str);
void dumpdir(void *env,const char *str);

#endif // IO_H_

