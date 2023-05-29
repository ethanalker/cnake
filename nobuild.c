#define NOBUILD_IMPLEMENTATION
#include "./nobuild.h"

// this build assumes linux/cygwin, if you use windows, don't
// nobuild does support windows, i didn't bother

#define CLIBS "-lm"
#define CFLAGS "-Wall", "-Wextra", "-std=gnu99", "-pedantic", "-g"
#define CC "gcc"
#define SRCDIR "src"
#define OBJDIR "obj"
#define EXECNAME "cnake"

void build(void)
{
    Cmd cmd = {
        .line = cstr_array_make(CC, CFLAGS, CLIBS, "-o", EXECNAME, NULL)
    };
    int needs_built = 0;
    FOREACH_FILE_IN_DIR(file, OBJDIR, {
        if (ENDS_WITH(file, ".o")) {
            cmd.line = cstr_array_append(cmd.line, PATH(OBJDIR, file));
            if (!PATH_EXISTS(EXECNAME)) {
                needs_built = 1;
            } else {
                if (is_path1_modified_after_path2(PATH(OBJDIR, file), EXECNAME))
                    needs_built = 1;
            }
        }
    });
    if (needs_built) {
        INFO("CMD: %s", cmd_show(cmd));
        cmd_run_sync(cmd);
    } else {
        puts("Executable up-to-date");
    }
}

void build_objects(void)
{
    FOREACH_FILE_IN_DIR(file, SRCDIR, {
        if (ENDS_WITH(file, ".c")) {
            Cstr src_path = PATH(SRCDIR, file);
            Cstr hdr_path = PATH(SRCDIR, CONCAT(NOEXT(file), ".h")); 
            Cstr obj_path = PATH(OBJDIR, CONCAT(NOEXT(file), ".o")); 
            int needs_built = 0;
            if (!PATH_EXISTS(obj_path)) {
                needs_built = 1;
            } else {
                if (PATH_EXISTS(hdr_path) && is_path1_modified_after_path2(hdr_path, obj_path))
                    needs_built = 1;
                if (is_path1_modified_after_path2(src_path, obj_path))
                    needs_built = 1;
            }
            if (needs_built == 1) {
                CMD(CC, CFLAGS, CLIBS, "-c", "-o", obj_path, src_path);
            }
        }
    });
}

int main(int argc, char **argv)
{
    GO_REBUILD_URSELF(argc, argv);

    if (!PATH_EXISTS(SRCDIR))
        MKDIRS(PATH(SRCDIR));

    if (!PATH_EXISTS(OBJDIR))
        MKDIRS(PATH(OBJDIR));

    build_objects();
    build();

    return 0;
}
