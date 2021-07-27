#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>

#define MAX_PATH_LEN 1024

void fsize(char *name);
void dir_walk(char *dir_name, void (*func)(char *));
void print_file_size(size_t size);
void print_file_time(time_t time);

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
   * off_t st_size         File size, in bytes
   * dev_t st_dev          ID of device containing file
   * ino_t st_ino          File serial number
   * mode_t st_mode        Mode of file (see below)
   * nlink_t st_nlink      Number of hard links
   * uid_t st_uid          User ID of the file
   * gid_t st_gid          Group ID of the file
   * dev_t st_rdev         Device ID
   * time_t st_atime       Time of last access
   * time_t st_mtime       Last data modification time
   * time_t st_ctime       Time of last status change
   * blkcnt_t st_blocks    Blocks allocated for file
   * blksize_t st_blksize  Optimal blocksize for I/O
   */

  // printf("%-50s: ", name);
  // printf("%-6lld ", buffer.st_size);
  // printf("%d ", buffer.st_dev);
  // printf("%llu ", buffer.st_ino);
  // printf("%d ", buffer.st_mode);
  // printf("%d ", buffer.st_nlink);
  // printf("%d ", buffer.st_uid);
  // printf("%d ", buffer.st_gid);
  // printf("%d ", buffer.st_rdev);
  // printf("%ld ", buffer.st_atime);
  // printf("%ld ", buffer.st_mtime);
  // printf("%ld ", buffer.st_ctime);
  // printf("%-4lld ", buffer.st_blocks);
  // printf("%d\n", buffer.st_blksize);

  char time_str[32];
  strftime(time_str, sizeof(time_str), "%d %b %H:%M", localtime(&buffer.st_atime));

  print_file_size(buffer.st_size);
  print_file_time(buffer.st_atime);
  printf("%s\n", name);
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
    if (strcmp(dir_entry->d_name, ".") == 0 || strcmp(dir_entry->d_name, "..") == 0)
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

void print_file_size(size_t size)
{
  static const char *SIZES[] = {"B", "K", "M", "G"};
  size_t div = 0;
  size_t rem = 0;

  while (size >= 1024 && div < (sizeof SIZES / sizeof *SIZES))
  {
    rem = (size % 1024);
    div++;
    size /= 1024;
  }

  printf("%6.1f%s ", (float)size + (float)rem / 1024.0, SIZES[div]);
}

void print_file_time(time_t time)
{
  char time_str[32];
  strftime(time_str, sizeof(time_str), "%d %b %H:%M", localtime(&time));
  printf("%s ", time_str);
}
