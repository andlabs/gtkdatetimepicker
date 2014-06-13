// 13 june 2014
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define GLIB_VERSION_MIN_REQUIRED GLIB_VERSION_2_32
#define GLIB_VERSION_MAX_ALLOWED GLIB_VERSION_2_32
#define GDK_VERSION_MIN_REQUIRED GDK_VERSION_3_4
#define GDK_VERSION_MAX_ALLOWED GDK_VERSION_3_4
#include <gtk/gtk.h>

typedef struct DateTimePicker DateTimePicker;
struct DateTimePicker;

extern DateTimePicker *NewDateTimePicker(void);
extern GtkWidget *DTPEntry(DateTimePicker *);