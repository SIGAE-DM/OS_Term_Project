//이 헤더set을 main.c에서 불러오기 --> main.c에서 set_header.h 한 줄로 불러오기

#include <dirent.h> // 디렉토리 엔트리
#include <fcntl.h>
#include <pthread.h> // 멀티스레딩
#include <stdbool.h>
#include <stdio.h>  // 기본 입출력
#include <stdlib.h> // malloc, exit 등
#include <string.h> // 문자열 처리
#include <string.h>
#include <time.h>
#include <unistd.h> // UNIX 표준 API
#include <utime.h>

#include "ChMod.h"
#include "Initial.h"
#include "Permission.h"
#include "cat.h"
#include "cd.h"
#include "cp.h"
#include "grep.h"
#include "head.h"
#include "ls.h"
#include "mkdir.h"
#include "option.h"
#include "rmdir.h"
#include "struct.h"
#include "tail.h"
#include "touch.h"

#include "Save_Status.h"
