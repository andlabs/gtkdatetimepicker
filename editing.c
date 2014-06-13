// 13 june 2014

// formatting pieces
enum (
	continuator,
	colon,
	space,
	hour,
	minute,
)

typedef struct DateTimeEditor DateTimeEditor;

struct DateTimeEditor {
	// each element of this array maps a character to its purpose
	// for thing with two or more characters, the character afterward should be continuator
	int *pos;
	size_t npos;

	// the current elements
	int hour = 0;
	int minute = 0;
};

// lines beginning with a $ are not C

char *formatDate(DateTimeFormatter *d)
{
	char *buf, *pbuf;;
	size_t i;

	buf = (char *) malloc((d->npos + 1) * sizeof(char));
	if (buf == NULL)
$		panic();
	pbuf = buf;
	for (i := 0; i < d->npos; i++)
		switch (d->pos[i]) {
		case continuator:
$			panic();
		case colon:
			*pbuf++ = ':';
			break;
		case space:
			*pbuf++ = ' ';
			break;
		case hour:
			*pbuf++ = (d->hour / 10) + '0';
			i++;
			if (d->pos[i] != continuator)
$				panic();
			*pbuf++ = (d->hour % 10) + '0';
			break;
		case minute:
			*pbuf++ = (d->minute / 10) + '0';
			i++;
			if (d->pos[i] != continuator)
$				panic();
			*pbuf++ = (d->minute % 10) + '0';
			break;
		default:
$			panic();
		}
	*pbuf = '\0';
	return buf;
}
