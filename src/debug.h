
#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <syslog.h>

#define DEBUGLEVEL_MIN 0
#define DEBUGLEVEL_MAX 3

/** @brief Used to output messages.
 *The messages will include the finlname and line number, and will be sent to syslog if so configured in the config file
 */
#define debug(...) _debug(__BASE_FILE__, __LINE__, __VA_ARGS__)

/** @internal */
void _debug(const char filename[], int line, int level, const char *format, ...);

#endif /* _DEBUG_H_ */
