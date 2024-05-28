#include "rmdir.h"

void removedir(char *argument, DirectTree *dirtree, Users *usertree) {
  if (argument == NULL) {
    printf("Cannot Remove Directory. Enter the argument\n");
    return;
  }

  // 삭제할 디렉토리 검색
  TreeNode *currentDir = dirtree->current;
  TreeNode *child = currentDir->child;
  TreeNode *prevChild = NULL;
  bool dirFound = false;

  // 하위 디렉토리 존재 유무 확인
  if (!(child->child == NULL)) {
    printf("Directory is not empty.\n");
    return;
  }

  // 삭제할 디렉토리 찾기
  while (!(child == NULL)) {
    if (strcmp(child->name, argument) == 0 && child->type == 'd') {
      dirFound = true;
      break;
    }
    prevChild = child;
    child = child->sib;
  }

  if (!dirFound) {
    printf("Directory not found: %s\n", argument);
    return;
  }

  // 디렉토리를 삭제후 메모리 해제
  if (!(prevChild == NULL)) {
    prevChild->sib = child->sib;
  } else {
    currentDir->child = child->sib;
  }
  free(child);
}

void *removeMultiThread(void *args) {
  ThreadArg *data = (ThreadArg *)args;
  removedir(data->argument, data->dirtree, data->userlist);
  return NULL;
}

void multi_rmdir(char **argument, int num, DirectTree *dirTree,
                 Users *userlist) {
  pthread_t *threads = malloc(sizeof(pthread_t) * num);
  ThreadArg *threadArg = malloc(sizeof(ThreadArg) * num);

  for (int i = 0; i < num; i++) {
    threadArg[i].argument = argument[i];
    threadArg[i].dirtree = dirTree;
    threadArg[i].userlist = userlist;
    if (pthread_create(&threads[i], NULL, removeMultiThread,
                       (void *)&threadArg[i])) {
      fprintf(stderr, "Error\n");
      return;
    }
  }

  for (int i = 0; i < num; i++) {
    pthread_join(threads[i], NULL);
  }
  free(threads);
  free(threadArg);
}
