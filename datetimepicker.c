// 13 june 2014
#include "datetimepicker.h"

// TODO these don't check for underflow

// formatting pieces
enum {
	continuator,
	colon,
	space,
	hour,
	minute,
};

#define FIRSTSTOP hour

typedef struct DateTimePicker DateTimePicker;

struct DateTimePicker {
	// the widgets
	GtkWidget *entry;

	// each element of this array maps a character to its purpose
	// for thing with two or more characters, the character afterward should be continuator
	int *pos;
	gint npos;
	char *str;
	gint curpos;

	// the current elements
	int hour;
	int minute;
};

static void formatDate(DateTimePicker *d)
{
	char *pbuf;
	gint i;

	pbuf = d->str;
	for (i = 0; i < d->npos; i++)
		switch (d->pos[i]) {
		case continuator:
			g_error("unexpected continuator at pos %d", i);
		case colon:
			*pbuf++ = ':';
			break;
		case space:
			*pbuf++ = ' ';
			break;
		case hour:
			*pbuf++ = (d->hour / 10) + '0';
			i++;
			if (i >= d->npos || d->pos[i] != continuator)
				g_error("expected continuator at pos %d", i);
			*pbuf++ = (d->hour % 10) + '0';
			break;
		case minute:
			*pbuf++ = (d->minute / 10) + '0';
			i++;
			if (i >= d->npos || d->pos[i] != continuator)
				g_error("expected continuator at pos %d", i);
			*pbuf++ = (d->minute % 10) + '0';
			break;
		default:
			g_error("unknown postype %d", d->pos[i]);
		}
	*pbuf = '\0';
	gtk_entry_set_text(GTK_ENTRY(d->entry), d->str);
}

static void nearest(DateTimePicker *d, gint direction)
{
	if (direction < 0)
		direction = -1;
	else if (direction > 0)
		direction = 1;
	else
		g_error("direction == 0 in DateTimePicker.nearest()");
	while (d->curpos < d->npos && d->pos[d->curpos] < FIRSTSTOP)
		d->curpos += direction;
	if (d->curpos == d->npos)
		d->curpos--;
}

static void adjust(DateTimePicker *d)
{
	gint endpos;

	gtk_editable_set_position(GTK_EDITABLE(d->entry), d->curpos);
	endpos = d->curpos + 1;
	while (endpos < d->npos && d->pos[endpos] == continuator)
		endpos++;
	gtk_editable_select_region(GTK_EDITABLE(d->entry), d->curpos, endpos);
}

static void move_cursor(GtkEntry *entry, GtkMovementStep step, gint count, gboolean selects, gpointer data)
{
	DateTimePicker *d = (DateTimePicker *) data;
	gint pos;

	if (selects)			// allow arbitrary selection
		return;
	g_signal_stop_emission_by_name(entry, "move-cursor");
	switch (step) {		// filter out vertical movements
	case GTK_MOVEMENT_DISPLAY_LINES:
printf("LINES > ");
	case GTK_MOVEMENT_PARAGRAPHS:
printf("PARAGRAPHS > ");
	case GTK_MOVEMENT_PAGES:
printf("PAGES\n");
		return;
	}
	switch (step) {
	case GTK_MOVEMENT_LOGICAL_POSITIONS:
	case GTK_MOVEMENT_VISUAL_POSITIONS:
	case GTK_MOVEMENT_WORDS:
	case GTK_MOVEMENT_HORIZONTAL_PAGES:
		d->curpos += count;
		nearest(d, count);
		break;
	case GTK_MOVEMENT_DISPLAY_LINE_ENDS:
	case GTK_MOVEMENT_PARAGRAPH_ENDS:
	case GTK_MOVEMENT_BUFFER_ENDS:
		if (count < 0)
			d->curpos = 0;
		else if (count > 0) {
			d->curpos = d->npos - 1;
			nearest(d, count);
		} else
			g_error("count == 0 in DateTimePicker.move_cursor()");
		break;
	default:
		g_error("unknown GtkMovementType %d\n", step);
	}
	if (d->curpos == d->npos)
		d->curpos--;
	adjust(d);
}

DateTimePicker *NewDateTimePicker(void)
{
	DateTimePicker *d;

	d = (DateTimePicker *) malloc(sizeof (DateTimePicker));
	if (d == NULL)
		g_error("memory exhausted allocating DateTimePicker");
	memset(d, 0, sizeof (DateTimePicker));

	d->entry = gtk_entry_new();
	g_signal_connect(d->entry, "move-cursor", G_CALLBACK(move_cursor), d);

	// a default string
	d->npos = 5;
	d->pos = (int *) malloc(d->npos * sizeof (int));
	if (d->pos == NULL)
		g_error("memory exhausted allocating d->pos");
	d->pos[0] = hour;
	d->pos[1] = continuator;
	d->pos[2] = colon;
	d->pos[3] = minute;
	d->pos[4] = continuator;
	d->str = (char *) malloc((d->npos + 1) * sizeof (char));
	if (d->str == NULL)
		g_error("memory exhausted allocating d->str");
	formatDate(d);

	return d;
}

GtkWidget *DTPEntry(DateTimePicker *d)
{
	return d->entry;
}
