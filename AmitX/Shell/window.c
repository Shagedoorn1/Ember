#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../amitx_info.h"

#define PROMPT AMITX_SHELL_PROMPT

GtkTextBuffer *buffer;

void boot_sequence() {
    sleep(1);
    printf("Booting ");
    fflush(stdout);
    for (int i = 0; i < 3; i++) {
        sleep(1);
        printf(". ");
        fflush(stdout);
    }
    printf("\n");
}

void insert_text(const char *text) {
    GtkTextIter iter;
    gtk_text_buffer_get_end_iter(buffer, &iter);
    gtk_text_buffer_insert(buffer, &iter, text, -1);
}

void insert_prompt() {
    insert_text(PROMPT);
}

void startup_msg() {
    insert_text(AMITX_BOOT_MSG);
    insert_text("\n");
}


void run_command(const char *cmd) {
    if (strcmp(cmd, "clear") == 0) {
        gtk_text_buffer_set_text(buffer, "", -1);
        startup_msg();
        insert_prompt();
    } else if (strncmp(cmd, "hoot ", 5) == 0) {
        insert_text("\n");
        insert_text(cmd + 5);  // print the text after "hoot "
        insert_text("\n");
        insert_prompt();
    } else if (strncmp(cmd, "why", 3) == 0){
        FILE *file = fopen("../MOTIVE.md", "r");
        if (file) {
            char line[512];
            insert_text("\n");
            while (fgets(line, sizeof(line), file)) {
                insert_text(line);
            }
            fclose(file);
        } else {
            insert_text("\nCould not load MOTIVE.md\n");
        }
        insert_prompt();
        
    } else {
        insert_text("\nUnknown command\n");
        insert_prompt();
    }
}

gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data) {
    if (event->keyval == GDK_KEY_Return) {
        GtkTextIter start, end;
        gtk_text_buffer_get_end_iter(buffer, &end);
        start = end;

        while (!gtk_text_iter_starts_line(&start)) {
            gtk_text_iter_backward_char(&start);
        }

        gchar *line = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
        if (g_str_has_prefix(line, PROMPT)) {
            const char *cmd = line + strlen(PROMPT);
            run_command(cmd);
        }
        g_free(line);
        return TRUE;
    }
    return FALSE;
}

int main(int argc, char *argv[]) {
    boot_sequence();

    sleep(1);

    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), AMITX_SHELL_TITLE);
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
    gtk_window_move(GTK_WINDOW(window), 800, 400);

    GtkWidget *text_view = gtk_text_view_new();
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD_CHAR);
    gtk_text_view_set_monospace(GTK_TEXT_VIEW(text_view), TRUE);

    GtkWidget *scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scroll), text_view);
    gtk_container_add(GTK_CONTAINER(window), scroll);

    // Apply style
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
        "window, textview text, scrolledwindow, viewport {\n"
        "   background-color: #1e1e1e;\n"
        "   color: #ffffff;\n"
        "   font-family: monospace;\n"
        "   font-size: 14px;\n"
        "   border: none;\n"
        "}\n"
        "textview {\n"
        "   padding: 10px;\n"
        "   border: none;\n"
        "}\n"
        "viewport {\n"
        "   background-color: #1e1e1e;\n"
        "}\n",
        -1, NULL);

    GtkWidget *viewport = gtk_bin_get_child(GTK_BIN(scroll));
    GtkStyleContext *viewport_context = gtk_widget_get_style_context(viewport);
    gtk_style_context_add_provider(viewport_context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    
    GtkStyleContext *context;
    context = gtk_widget_get_style_context(window);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    context = gtk_widget_get_style_context(text_view);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    context = gtk_widget_get_style_context(scroll);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    
    startup_msg();

    insert_prompt();

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(text_view, "key-press-event", G_CALLBACK(on_key_press), NULL);

    gtk_widget_show_all(window);
    gtk_widget_grab_focus(text_view);

    gtk_main();
    return 0;
}
