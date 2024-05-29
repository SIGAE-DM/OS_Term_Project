// mkdir 명령어 구현 헤더

#ifndef MKDIR2_H
#define MKDIR2_H

#pragma once

#include "set_header.h"
typedef struct MkdirThread {
  char dirName[50];
  DirectTree *dirtree;
  Users *user;
} MkdirThread;

void make_dir(char *filename, char Type, TreeNode *parent, DirectTree *dirtree,
              Users *usertree, int permission);
void *create_dir_thread(void *arg);
void mkdir(char *path, DirectTree *dirTree, Users *userTree);

void multi_mkdir(char *path, DirectTree *dirTree, Users *userTree);

#endif