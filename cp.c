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

  printf("Source file: %s\n", srcFilename);
  printf("Destination path: %s\n", destPath);

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
  TreeNode *destDirNode = NULL;

  // 목적지 경로가 디렉토리인지 파일인지 확인
  destDirNode = Find_Dir(destPath, 'd', dirtree);
  if (destDirNode != NULL && destDirNode->type == 'd') {
    // 목적지 경로가 디렉토리인 경우
    snprintf(destFilename, Name_Len, "%s", strrchr(srcFilename, '/') ? strrchr(srcFilename, '/') + 1 : srcFilename);
    printf("Destination directory found: %s\n", destPath);
  } else {
    // 목적지 경로가 파일이거나 존재하지 않는 경우
    // 디렉토리와 파일 이름 분리
    char *lastSlash = strrchr(destPath, '/');
    if (lastSlash != NULL) {
      *lastSlash = '\0'; // 디렉토리 경로와 파일 이름 분리
      strcpy(destFilename, lastSlash + 1); // 파일 이름 저장
      destDirNode = Find_Dir(destPath, 'd', dirtree);
      if (destDirNode == NULL) {
        printf("Destination directory not found: %s\n", destPath);
        return;
      }
    } else {
      strcpy(destFilename, destPath); // 파일 이름 저장
      destDirNode = dirtree->current; // 현재 디렉토리를 목적지로 설정
      printf("Destination set to current directory\n");
    }
  }

  printf("Final destination directory: %s\n", destDirNode->name);
  printf("Final destination filename: %s\n", destFilename);

  // Destination 파일이 이미 존재하는지 확인
  char fullDestPath[Name_Len * 2];
  snprintf(fullDestPath, sizeof(fullDestPath), "%s/%s", destDirNode->name, destFilename);
  TreeNode *destFileNode = Find_Dir(fullDestPath, 'f', dirtree);
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
  strncpy(newNode->name, destFilename, Name_Len);
  newNode->type = 'f';
  newNode->User = userlist->current->User;
  newNode->Group = userlist->current->Group;
  newNode->Size = srcNode->Size;
  memcpy(newNode->permission, srcNode->permission, sizeof(srcNode->permission));

  time_t timer = time(NULL);
  struct tm *t = localtime(&timer);
  newNode->Year = t->tm_year + 1900;
  newNode->Month = t->tm_mon + 1;
  newNode->Day = t->tm_mday;
  newNode->Hour = t->tm_hour;
  newNode->Minute = t->tm_min;

  // 데이터를 복사
  strncpy(newNode->data, srcNode->data, ROW_SIZE * COLUM_SIZE);

  // 새로운 노드를 목적지 디렉토리에 추가
  newNode->parents = destDirNode;
  newNode->child = NULL;
  newNode->sib = destDirNode->child;
  destDirNode->child = newNode;

  printf("File copied successfully: %s to %s/%s\n", srcFilename,
         destDirNode->name, newNode->name);
}
