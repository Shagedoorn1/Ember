#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include "build.h"

#define COLOR_RESET   "\x1b[0m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_RED     "\x1b[31m"
#define COLOR_CYAN    "\x1b[36m"

int run_pre_cmd(const EmberBuildConfig* config) {
    if (config->pre_cmd) {
        return system(config->pre_cmd);
    }
    return 0;
}

int run_post_cmd(const EmberBuildConfig* config) {
    if (config->post_cmd) {
        return system(config->post_cmd);
    }
    return 0;
}

int compile_and_link(const EmberBuildConfig* config) {
    // Create output dir if it doesn't exist
    struct stat st = {0};
    if (stat(config->out_dir, &st) == -1) {
        printf(COLOR_YELLOW "[D] %s\n" COLOR_RESET, config->out_dir);
        char mkdir_cmd[256];
        snprintf(mkdir_cmd, sizeof(mkdir_cmd), "mkdir -p %s", config->out_dir);
        system(mkdir_cmd);
    }

    char* objs[config->src_count];
    char cmd[1024];

    // Build flags string
    char all_flags[256] = "";
    for (int f = 0; f < config->flag_count; f++) {
        strcat(all_flags, config->flags[f]);
        strcat(all_flags, " ");
    }

    char include_flags[256] = "";
    for (int i = 0; i < config->include_count; i++) {
        strcat(include_flags, "-I");
        strcat(include_flags, config->includes[i]);
        strcat(include_flags, " ");
    }

    // Compile all sources
    for (int i = 0; i < config->src_count; i++) {
        const char* src = config->srcs[i];
        char* src_filename = strrchr(src, '/');
        src_filename = src_filename ? src_filename + 1 : (char*)src;
    
        char obj_path[256];
        snprintf(obj_path, sizeof(obj_path), "%s/%.*s.o", config->out_dir,
                 (int)(strrchr(src_filename, '.') - src_filename), src_filename);
        objs[i] = strdup(obj_path);
    
        // Check if object file exists and is up to date
        struct stat src_stat, obj_stat;
        int needs_compile = 1;
        if (stat(src, &src_stat) == 0 && stat(obj_path, &obj_stat) == 0) {
            if (difftime(src_stat.st_mtime, obj_stat.st_mtime) <= 0) {
                printf(COLOR_GREEN "[S] %s (up-to-date)\n" COLOR_RESET, src);
                needs_compile = 0;
            }
        }
    
        if (needs_compile) {
            snprintf(cmd, sizeof(cmd), "gcc -c %s -o %s %s %s", src, objs[i], include_flags, all_flags);
            printf(COLOR_YELLOW "[C] %s\n" COLOR_RESET, cmd);
            if (system(cmd) != 0) {
                fprintf(stderr, COLOR_RED "[X] Compilation failed: %s\n" COLOR_RESET, src);
                return 1;
            }
        }
    }

    // Final output binary path
    char output_path[256];
    snprintf(output_path, sizeof(output_path), "%s/%s", config->out_dir, config->target);

    char lib_flags[256] = "";
    for (int i = 0; i < config->lib_count; i++) {
        strcat(lib_flags, config->libs[i]);
        strcat(lib_flags, " ");
    }

    snprintf(cmd, sizeof(cmd), "gcc");
    for (int i = 0; i < config->src_count; i++) {
        strcat(cmd, " ");
        strcat(cmd, objs[i]);
    }
    strcat(cmd, " ");
    strcat(cmd, lib_flags);
    strcat(cmd, " -o ");
    strcat(cmd, output_path);

    printf(COLOR_CYAN "[L] %s\n" COLOR_RESET, cmd);
    if (system(cmd) != 0) {
        fprintf(stderr, COLOR_RED "[X] Linking failed.\n" COLOR_RESET);
        return 1;
    }

    printf(COLOR_GREEN "[B] %s\n" COLOR_RESET, output_path);
    return 0;
}