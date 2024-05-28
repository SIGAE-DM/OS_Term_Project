#include "cp.h"

// 파일 복사 함수
void cp(char *argument, DirectTree *dirtree, Users *userlist) {
  if (argument == NULL) {
    printf("No argument provided.\n");
    return;
  }

  int argc = 0;
  char *argv[100];
  char *token = strtok(argument, " ");
  while (token != NULL) {
    argv[argc++] = token;
    token = strtok(NULL, " ");
  }

  if (argc != 2) {
    printf("Usage: cp sourceFile destinationFile/directory\n");
    return;
  }

  char *srcFilename = argv[0];
  char *destPath = argv[1];

  // Source 파일을 찾음
  TreeNode *srcNode = Find_Dir(srcFilename, 'f', dirtree);
  if (srcNode == NULL) {
    printf("Source file not found: %s\n", srcFilename);
    return;
  }

  // Source 파일 권한 확인
  if (!Permission(srcNode, userlist, 'r')) {
    printf("Permission Denied: %s\n", srcFilename);
    return;
  }

  char destFilename[Name_Len];
  TreeNode *destDirNode = Find_Dir(destPath, 'd', dirtree);

  if (destDirNode != NULL && destDirNode->type == 'd') {
    // destPath가 디렉토리인 경우
    snprintf(destFilename, Name_Len, "%s/%s", destPath,
             strrchr(srcFilename, '/') ? strrchr(srcFilename, '/') + 1
                                       : srcFilename);

    // Destination 파일이 이미 존재하는지 확인
    TreeNode *destFileNode = Find_Dir(destFilename, 'f', dirtree);
    if (destFileNode != NULL) {
      printf("Destination file already exists: %s\n", destFilename);
      return;
    }

    // 새로운 노드 생성 및 초기화
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    if (!newNode) {
      printf("Memory allocation failed\n");
      return;
    }
    strncpy(newNode->name,
            strrchr(srcFilename, '/') ? strrchr(srcFilename, '/') + 1
                                      : srcFilename,
            Name_Len);
    newNode->type = 'f';
    newNode->User = userlist->current->User;
    newNode->Group = userlist->current->Group;
    newNode->Size = srcNode->Size;
    memcpy(newNode->permission, srcNode->permission,
           sizeof(srcNode->permission));

    time_t timer = time(NULL);
    struct tm *t = localtime(&timer);
    newNode->Year = t->tm_year + 1900;
    newNode->Month = t->tm_mon + 1;
    newNode->Day = t->tm_mday;
    newNode->Hour = t->tm_hour;
    newNode->Minute = t->tm_min;

    strncpy(newNode->data, srcNode->data, ROW_SIZE * COLUM_SIZE);

    // 새로운 노드를 목적지 디렉토리에 추가
    newNode->parents = destDirNode;
    newNode->child = NULL;
    newNode->sib = destDirNode->child;
    destDirNode->child = newNode;

    printf("File copied successfully: %s to %s\n", srcFilename, destFilename);
  } else {
    // destPath가 파일명인 경우
    TreeNode *srcNode = Find_Dir(srcFilename, 'f', dirtree);
    if (srcNode == NULL){
      printf("Source file not found: %s\n", srcFilename);
      return;
    }

    if(!Permission(srcNode, userlist, 'r')){
      printf("Permissio")
    }
  }
}
