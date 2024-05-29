#ifndef CD_H
#define CD_H

#include "set_header.h"

#define NAME_LENGTH 1000

#pragma once
void cd(char *dirname, DirectTree *dirtree);
void printDirectory(TreeNode *current);
#endif