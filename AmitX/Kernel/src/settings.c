#include "fs.h"
#include "settings.h"
#include "string.h"
#include "screen.h"

#define MAX_SETTINGS 16

typedef struct {
    const char* key;
    const char* value;
} Setting;

static Setting settings[MAX_SETTINGS];
static int setting_count = 0;

void settings_load() {
    const char* raw = fs_read("/Saved/settings.cfg");
    if (!raw) {
        screen_puts("[settings] Failed to load file.\n");
        return;
    }

    screen_puts("[settings] Raw settings file loaded:\n");
    screen_puts(raw);

    char line[64];
    int i = 0, j = 0;

    while (*raw && setting_count < MAX_SETTINGS) {
        if (*raw == '\n' || *raw == '\0') {
            line[j] = '\0';
            screen_puts("[settings] Line parsed: ");
            screen_puts(line);
            screen_putc('\n');
    
            char* eq = strchr(line, '=');
            
            if (eq) {
                *eq = '\0';
                settings[setting_count].key = strdup(line);
                
                settings[setting_count].value = strdup(eq + 1);

                screen_puts("[settings] Key = ");
                screen_puts(settings[setting_count].key);
                screen_puts(", Value = ");
                screen_puts(settings[setting_count].value);
                screen_putc('\n');

                setting_count++;
            } else {
                screen_puts("[settings] Skipping invalid line (no '=')\n");
            }
            j = 0;
        } else {
            if (j < sizeof(line) - 1) {
                line[j++] = *raw;
            }
            
        }
        raw++;
    }
    screen_puts("[settings] Total settings loaded: ");
    screen_putint(setting_count);
    screen_putc('\n');
}

const char* settings_get(const char* key) {
    //screen_puts("[settings_get] Looking for key: ");
    //screen_puts(key);
    //screen_putc('\n');
    for (int i = 0; i < setting_count; i++) {
        //screen_puts("[settings_get] Comparing to: ");
        //screen_puts(settings[i].key);
        //screen_putc('\n');

        if (strcmp(settings[i].key, key) == 0) {
            //screen_puts("[settings_get] Match found. Value: ");
            //screen_puts(settings[i].value);
            //screen_putc('\n');
            return settings[i].value;
        }
    }
    //screen_puts("[settings_get] No match found.\n");
    return NULL;
}