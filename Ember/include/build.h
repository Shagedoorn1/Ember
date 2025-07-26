#ifndef BUILD_H
#define BUILD_H

#include "ember.h"

int run_pre_cmd(const EmberBuildConfig* config);
int run_post_cmd(const EmberBuildConfig* config);
int compile_and_link(const EmberBuildConfig* config);

#endif