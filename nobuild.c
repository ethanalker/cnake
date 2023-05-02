#define NOBUILD_IMPLEMENTATION
#include "./nobuild.h"

// this build assumes linux/cygwin, if you use windows, don't

#define CLIBS "-lm", "-lncurses"
#define CFLAGS "-Wall", "-Wextra", "-std=c99", "-pedantic"
#define CC "gcc"
#define SRCDIR "src"
#define OBJDIR "obj"
#define EXECNAME "cnake"

void build(void)
{
    Cstr_Array objs = cstr_array_make("");
    FOREACH_FILE_IN_DIR(file, OBJDIR, {
        if (ENDS_WITH(file, ".o")) {
            objs = cstr_array_append(objs, PATH(OBJDIR, file));
        }
    });
    CMD(CC, CFLAGS, CLIBS, "-o", EXECNAME, cstr_array_join("", objs));
}

void build_object(const char *file)
{
    Cstr src_path = PATH(SRCDIR, file);
    Cstr obj_path = PATH(OBJDIR, CONCAT(NOEXT(file), ".o")); 
    if (!PATH_EXISTS(obj_path) || is_path1_modified_after_path2(src_path, obj_path)) {
        CMD(CC, CFLAGS, CLIBS, "-c", "-o", obj_path, src_path);
    }
}

void build_objects(void)
{
    FOREACH_FILE_IN_DIR(file, SRCDIR, {
        if (ENDS_WITH(file, ".c")) {
            build_object(file);
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
