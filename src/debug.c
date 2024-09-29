#include <stdio.h>
#include <errno.h>
#include <syslog.h>
#include <stdarg.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

#include "util.h"
#include "conf.h"
#include "debug.h"


static int do_log(int level, int debuglevel) {
	switch (level) {
		case LOG_EMERG:
		case LOG_ERR:
			// quiet
			return (debuglevel >= 0);
		case LOG_WARNING:
		case LOG_NOTICE:
			// default
			return (debuglevel >= 1);
		case LOG_INFO:
			// verbose
			return (debuglevel >= 2);
		case LOG_DEBUG:
			// debug
			return (debuglevel >= 3);
		default:
			debug(LOG_ERR, "Unhandled debug level: %d", level);
			return 1;
	}
}

/** @internal
Do not use directly, use the debug macro */
void
_debug(const char filename[], int line, int level, const char *format, ...)
{
	char buf[64];
	va_list vlist;
	s_config *config;
	FILE *out;
	time_t ts;
	sigset_t block_chld;

	time(&ts);

	config = config_get_config();

	if (do_log(level, config->debuglevel)) {
		sigemptyset(&block_chld);
		sigaddset(&block_chld, SIGCHLD);
		sigprocmask(SIG_BLOCK, &block_chld, NULL);

		if (config->daemon) {
			out = stdout;
		} else {
			out = stderr;
		}

		fprintf(out, "[%d][%.24s][%u](%s:%d) ", level, format_time(ts, buf), getpid(), filename, line);
		va_start(vlist, format);
		vfprintf(out, format, vlist);
		va_end(vlist);
		fputc('\n', out);
		fflush(out);

		if (config->log_syslog) {
			openlog("ultari", LOG_PID, config->syslog_facility);
			va_start(vlist, format);
			vsyslog(level, format, vlist);
			va_end(vlist);
			closelog();
		}

		sigprocmask(SIG_UNBLOCK, &block_chld, NULL);
	}
}
