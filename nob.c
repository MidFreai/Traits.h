#define NOB_IMPLEMENTATION
#include "./external/nob.h"

void append_flags(Nob_Cmd* cmd){
  nob_cmd_append(cmd, "cc", "-Wall", "-Wextra", "-Isrc");
}

int main(int argc, char* argv[]){
  NOB_GO_REBUILD_URSELF(argc, argv);
  Nob_Cmd cmd = {0};

  append_flags(&cmd);
  nob_cmd_append(&cmd, "-o", "vtable", "exemples/vtable.c");
  nob_cmd_run(&cmd);

  append_flags(&cmd);
  nob_cmd_append(&cmd, "-o", "ecs", "exemples/ecs.c");
  nob_cmd_run(&cmd);

  nob_cmd_append(&cmd, "./vtable");
  nob_cmd_run(&cmd);

  nob_cmd_append(&cmd, "./ecs");
  nob_cmd_run(&cmd);

  return 0;
}
