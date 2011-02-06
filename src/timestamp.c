#include <stdio.h>
#include <string.h>

#include "timestamp.h"

struct event_name {
	const char* 	name;
	cmd_t	 	id;
};

#define EVENT(name)					\
	{#name "_START", TS_ ## name ## _START},	\
	{#name "_END", TS_ ## name ## _END}

static struct event_name event_table[] =
{
	EVENT(SCHED),
	EVENT(SCHED2),
	EVENT(TICK),
	EVENT(RELEASE),
	EVENT(PLUGIN_SCHED),
	EVENT(PLUGIN_TICK),
	EVENT(CXS),
	EVENT(SEND_RESCHED),
	{"RELEASE_LATENCY", TS_RELEASE_LATENCY},
};

int  str2event(const char* str, cmd_t *id)
{
	int i;

	for (i = 0; i < sizeof(event_table) / sizeof(event_table[0]); i++)
		if (!strcmp(str, event_table[i].name)) {
			*id = event_table[i].id;
			return 1;
		}
	/* try to parse it as a number */
	return sscanf(str, "%u", id);
}

const char* event2str(cmd_t id)
{
	int i;

	for (i = 0; i < sizeof(event_table) / sizeof(event_table[0]); i++)
		if (event_table[i].id == id)
			return event_table[i].name;

	return NULL;
}
