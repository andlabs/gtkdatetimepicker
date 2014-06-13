// 12 june 2014
#include "datetimepicker.h"

int main(void)
{
	gtk_init(NULL, NULL);

	GtkWindow *win;

	win = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));
	g_signal_connect(win, "delete-event", gtk_main_quit, NULL);

	GtkGrid *grid;

	grid = GTK_GRID(gtk_grid_new());

	DateTimePicker *d;

	d = NewDateTimePicker();
	gtk_grid_attach_next_to(grid, DTPEntry(d), NULL,
		GTK_POS_TOP, 1, 1);

	gtk_container_add(GTK_CONTAINER(win), GTK_WIDGET(grid));
	gtk_widget_show_all(GTK_WIDGET(win));

	gtk_main();
	return 0;
}