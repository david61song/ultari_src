
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <syslog.h>

#include "debug.h"
#include "safe.h"
#include "conf.h"


static void usage(void);

/** @internal
 * @brief Print usage
 *
 * Prints usage, called when ultari is run with -h or with an unknown option
 */
static void
usage(void)
{
	printf("Usage: ultari [options]\n"
		"\n"
		"  -c <path>   Use configuration file\n"
		"  -f          Run in foreground\n"
		"  -d <level>  Debug level (%d-%d)\n"
		"  -s          Log to syslog\n"
		"  -w <path>   Ultarictl socket path\n"
		"  -h          Print this help\n"
		"  -v          Print version\n"
		"\n", DEBUGLEVEL_MIN, DEBUGLEVEL_MAX
	);
}

/** Uses getopt() to parse the command line and set configuration values
 */
void parse_commandline(int argc, char **argv)
{
	int c;

	s_config *config = config_get_config();

	while (-1 != (c = getopt(argc, argv, "c:hfd:sw:vi:r:64"))) {

		switch(c) {

		case 'h':
			usage();
			exit(1);
			break;

		case 'c':
			if (optarg) {
				strncpy(config->configfile, optarg, sizeof(config->configfile)-1);
			}
			break;

		case 'w':
			if (optarg) {
				free(config->ultarictl_sock);
				config->ultarictl_sock = safe_strdup(optarg);
			}
			break;

		case 'f':
			config->daemon = 0;
			break;

		case 'd':
			if (set_debuglevel(optarg)) {
				printf("Could not set debuglevel to %d\n", atoi(optarg));
				exit(1);
			}
			break;

		case 's':
			config->log_syslog = 1;
			break;

		case 'v':
			printf("This is ultari version " VERSION "\n");
			exit(1);
			break;

		case 'r':
			if (optarg) {
				free(config->webroot);
				config->webroot = safe_strdup(optarg);
			}
			break;

		case '4':
			config->ip6 = 0;
			break;

		case '6':
			printf("IPv6 is not supported yet\n");
			exit(1);
			config->ip6 = 1;
			break;

		default:
			usage();
			exit(1);
			break;
		}
	}
}
