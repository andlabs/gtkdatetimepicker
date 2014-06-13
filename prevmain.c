// 21 april 2014
#define GLIB_VERSION_MIN_REQUIRED GLIB_VERSION_2_32
#define GLIB_VERSION_MAX_ALLOWED GLIB_VERSION_2_32
#define GDK_VERSION_MIN_REQUIRED GDK_VERSION_3_4
#define GDK_VERSION_MAX_ALLOWED GDK_VERSION_3_4
#include <gtk/gtk.h>

int main(void)
{
	gtk_init(NULL, NULL);

	GtkWidget *popup;
	GtkWidget *popuplayout;
	GtkWidget *calendar;

	popup = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title((GtkWindow *) popup, "Main Window");
	g_signal_connect(popup, "delete-event", gtk_main_quit, NULL);

	popuplayout = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

	calendar = gtk_calendar_new();
	gtk_box_pack_start((GtkBox *) popuplayout, calendar,
		TRUE, FALSE, 0);		// expand but don't fill

	GtkWidget *timelayout;
	GtkWidget *hspin;
	GtkWidget *colon1;
	GtkWidget *mspin;
	GtkWidget *colon2;
	GtkWidget *sspin;

	timelayout = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
#define PACKTIME(x) gtk_box_pack_start((GtkBox *) timelayout, x, FALSE, FALSE, 0);			// no expand or fill
	hspin = gtk_spin_button_new_with_range(0, 23, 1);
	gtk_spin_button_set_wrap((GtkSpinButton *) hspin, TRUE);
	PACKTIME(hspin);
	colon1 = gtk_label_new(":");
	PACKTIME(colon1);
	mspin = gtk_spin_button_new_with_range(0, 59, 1);
	PACKTIME(mspin);
	colon2 = gtk_label_new(":");
	PACKTIME(colon2);
	sspin = gtk_spin_button_new_with_range(0, 59, 1);
	PACKTIME(sspin);

	gtk_box_pack_start((GtkBox *) popuplayout, timelayout,
		TRUE, FALSE, 0);		// expand but don't fill

	gtk_container_add((GtkContainer *) popup, popuplayout);
	gtk_widget_show_all(popup);

	gtk_main();
	return 0;
}
