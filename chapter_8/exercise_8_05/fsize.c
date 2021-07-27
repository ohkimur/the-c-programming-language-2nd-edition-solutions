#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#define MAX_PATH_LEN 1024

void fsize(char *name);
void dir_walk(char *dir_name, void (*func)(char *));

int main(int argc, char *argv[])
{
  if (argc == 1)
  {
    fsize(".");
  }
  else
  {
    while (--argc > 0)
    {
      fsize(*++argv);
    }
  }

  return 0;
}

void fsize(char *name)
{
  struct stat buffer;

  if (stat(name, &buffer) == -1)
  {
    fprintf(stderr, "fsize: cannot access %s\n", name);
    return;
  }

  if ((buffer.st_mode & S_IFMT) == S_IFDIR)
  {
    dir_walk(name, fsize);
  }

  /**
   * dev_t st_dev;         [XSI] ID of device containing file
   * ino_t st_ino;         [XSI] File serial number
   * mode_t st_mode;       [XSI] Mode of file (see below)
   * nlink_t st_nlink;     [XSI] Number of hard links
   * uid_t st_uid;         [XSI] User ID of the file
   * gid_t st_gid;         [XSI] Group ID of the file
   * dev_t st_rdev;        [XSI] Device ID
   * time_t st_atime;      [XSI] Time of last access
   * long st_atimensec;    nsec of last access
   * time_t st_mtime;      [XSI] Last data modification time
   * long st_mtimensec;    last data modification nsec
   * time_t st_ctime;      [XSI] Time of last status change
   * long st_ctimensec;    nsec of last status change
   * off_t st_size;        [XSI] File size, in bytes
   * blkcnt_t st_blocks;   [XSI] Blocks allocated for file
   * blksize_t st_blksize; [XSI] Optimal blocksize for I/O
   */

  printf("%s: %ld\n", name, (long)buffer.st_size);
  printf("%s: %ld\n", name, (long)buffer.st_size);
}

void dir_walk(char *dir_name, void (*func)(char *))
{
  char name[MAX_PATH_LEN];
  struct dirent *dir_entry;
  DIR *dir;

  if ((dir = opendir(dir_name)) == NULL)
  {
    fprintf(stderr, "dir_walk: cannot open %s\n", dir_name);
    return;
  }

  while ((dir_entry = readdir(dir)) != NULL)
  {
    if (strcmp(dir_entry->d_name, ".") == 0 ||
        strcmp(dir_entry->d_name, "..") == 0)
    {
      continue; // Skip self and parent.
    }

    if (strlen(dir_name) + strlen(dir_entry->d_name) + 2 > MAX_PATH_LEN)
    {
      fprintf(stderr, "dir_walk: path too long\n");
    }
    else
    {
      sprintf(name, "%s/%s", dir_name, dir_entry->d_name);
      (*func)(name);
    }
  }

  closedir(dir);
}
