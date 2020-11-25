#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char **argv) {

  char input[128];
  DIR *d;

  if (argc == 2) {
    strncpy(input, argv[1], sizeof(input));
    d = opendir(input);
    if (!d) {
      printf("error: %s\n", strerror(errno));
    }
  }

  else {
    printf("what directory would you like to get information for? \n");
    char buffer[128];
    fgets(buffer, sizeof(buffer)-1, stdin);
    d = opendir(buffer);
    if (!d) {
      printf("error: %s\n", strerror(errno));
    }
  }

  struct dirent *entry;
  entry = readdir(d);
  printf("statistics for directory: %s\n", entry->d_name);

  int directory_size = 0;
  struct stat file;
  while(entry) {
    stat(entry->d_name, &file);
    directory_size += file.st_size;
    entry = readdir(d);
  }
  printf("total directory size: %d bytes\n", directory_size);

  printf("directories: \n");
  rewinddir(d);
  entry = readdir(d);
  while (entry) {
    if (entry->d_type == DT_DIR) {
      printf("\t%s\n", entry->d_name);
    }
    entry = readdir(d);
  }

  printf("files: \n");
  rewinddir(d);
  entry = readdir(d);
  while (entry) {
    if (entry->d_type != DT_DIR) {
      printf("\t%s", entry->d_name);
      stat(entry->d_name, &file);
      printf("\t%lld bytes\n", file.st_size);
    }
    entry = readdir(d);
  }
  closedir(d);
  return 0;
}
