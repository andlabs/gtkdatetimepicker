// 12 june 2014
#include <ctype.h>
#define GLIB_VERSION_MIN_REQUIRED GLIB_VERSION_2_32
#define GLIB_VERSION_MAX_ALLOWED GLIB_VERSION_2_32
#define GDK_VERSION_MIN_REQUIRED GDK_VERSION_3_4
#define GDK_VERSION_MAX_ALLOWED GDK_VERSION_3_4
#include <gtk/gtk.h>

// for now, the format we accept is
// HH:MM

int curday = 0;
int curmonth = 0;
int curyear = 0;
int curhour = 0;
int curminute = 0;
int cursecond = 0;

int digit(int c)
{
#define I(a, b) if (c == a) return b;
	I('0', 0) I('1', 1) I('2', 2) I('3', 3)
	I('4', 4) I('5', 5) I('6', 6) I('7', 7)
	I('8', 8)
#undef I
	return 9;
}

void insert(GtkEditable *editable, gchar *new, gint n, gpointer xpos, gint data)
{
	int *pos = (int *) xpos;
	int i;

#define REJECT() g_signal_stop_emission_by_name(editable, "insert-text")
#define NOTTENS(c) ((c) == '6' || (c) == '7' || (c) == '8' || (c) == '9')
#define TENS(n, c) (((n) % 10) + (digit(c) * 10))
#define ONES(n, c) (((n) / 10) + digit(c))
	for (i = 0; i < n; i++) {
		int c;
		int newval;

		c = new[i];
		if (!isdigit(c)) {
			REJECT();
			return;
		}
		switch (*pos) {
		case 0:		// replace top digit with hour
			if (c != '0' && c != '1' && c != '2') {
				REJECT();
				return;
			}
			newval = TENS(curhour, c);
			if (newval > 23) {
				REJECT();
				return;
			}
			curhour = newval;
			break;
		case 1:
			newval = ONES(curhour, c);
			if (newval > 23) {
				REJECT();
				return;
			}
			curhour = newval;
			break;
		case 2:
			if (c != ':' && !isdigit(c)) {
				REJECT();
				return;
			}
			if (isdigit(c))		// actually put in the next place
				i--;			// TODO won't insert a :
			break;
		case 3:
			if (NOTTENS(c)) {
				REJECT();
				return;
			}
			newval = TENS(curminute, c);
			if (newval > 59) {
				REJECT();
				return;
			}
			curminute = newval;
			break;
		case 4:
			newval = ONES(curminute, c);
			if (newval > 59) {
				REJECT();
				return;
			}
			curminute = newval;
			break;
		default:
			REJECT();
			return;
		}
		(*pos)++;
	}
}

int main(void)
{
	gtk_init(NULL, NULL);

	GtkWindow *win;

	win = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));
	g_signal_connect(win, "delete-event", gtk_main_quit, NULL);

	GtkGrid *grid;

	grid = GTK_GRID(gtk_grid_new());

	GtkEntry *entry;

	entry = GTK_ENTRY(gtk_entry_new());
	gtk_entry_set_text(entry, "00:00");
	gtk_entry_set_overtype_mode(entry, TRUE);
	g_signal_connect(entry, "insert-text", G_CALLBACK(insert), NULL);
	gtk_grid_attach_next_to(grid, GTK_WIDGET(entry), NULL,
		GTK_POS_TOP, 1, 1);

	gtk_container_add(GTK_CONTAINER(win), GTK_WIDGET(grid));
	gtk_widget_show_all(GTK_WIDGET(win));

	gtk_main();
	return 0;
}