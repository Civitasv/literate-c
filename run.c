#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

#define SV_IMPLEMENTATION
#include "sv.h"

void usage(FILE* stream) { fprintf(stream, "Usage: lit <input>\n"); }

typedef struct {
  void* content_data;
  size_t content_size;
  int fd;

  bool fd_open;  // whether this file is mapped
} Mapped_File;

bool unmap_file(Mapped_File* mf) {
  if (mf->content_data != NULL) {
    munmap(mf->content_data, mf->content_size);
  }
  if (mf->fd_open) {
    close(mf->fd);
  }
  memset(mf, 0, sizeof(*mf));
}

bool map_file(Mapped_File* mf, const char* file_path) {
  unmap_file(mf);
  // open file, it will return a file descriptor
  mf->fd = open(file_path, O_RDONLY);
  if (mf->fd < 0) {
    goto error;
  }

  mf->fd_open = true;

  // retrieve file metedata
  struct stat statbuf = {0};
  if (fstat(mf->fd, &statbuf) < 0) {
    goto error;
  }

  // retrieve file detailed info
  mf->content_size = statbuf.st_size;
  mf->content_data =
      mmap(NULL, mf->content_size, PROT_READ, MAP_PRIVATE, mf->fd, 0);
  if (mf->content_data == NULL) {
    goto error;
  }

  return true;
error:
  unmap_file(mf);
  return false;
}

int main(int argc, char** argv) {
  if (argc < 2) {
    usage(stderr);
    fprintf(stderr, "ERROR: no input file is provided!\n");
    exit(1);
  }

  const char* input_file_path = argv[1];

  Mapped_File mf = {0};
  if (!map_file(&mf, input_file_path)) {
    fprintf(stderr, "ERROR: could not read file %s: %s\n", input_file_path,
            strerror(errno));
    exit(1);
  }

  bool code_mode = false;

  String_View content = sv_from_parts(mf.content_data, mf.content_size);
  while (content.count > 0) {
    String_View line = sv_chop_by_delim(&content, '\n');

    if (code_mode) {
      if (sv_eq(sv_trim(line), SV("\\end{code}"))) {
        printf("// " SV_Fmt "\n", SV_Arg(line));
        code_mode = false;
      } else {
        printf(SV_Fmt "\n", SV_Arg(line));
      }
    } else {
      if (sv_eq(sv_trim(line), SV("\\begin{code}"))) {
        printf("// " SV_Fmt "\n", SV_Arg(line));
        code_mode = true;
      }
    }
  }

  // release resources
  unmap_file(&mf);

  return 0;
}
