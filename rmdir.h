#ifndef RMDIR_H
#define RMDIR_H

#pragma once
#include "set_header.h"

typedef struct {
  char *argument;
  DirectTree *dirtree;
  Users *userlist;
} ThreadArg;

void *removeMultiThread(void *arg);
void multi_rmdir(char **argument, int num, DirectTree *dirtree,
                 Users *userlist);
void removedir(char *argument, DirectTree *dirtree, Users *userlist);
#endif