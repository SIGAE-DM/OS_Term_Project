#pragma once
#ifndef CHMOD_H
#define CHMOD_H
#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int *str2int(char mode);
void chmod(DirectTree *dirtree, char *chmd);

#endif