#include "cache.h"
#include "builtin.h"
#include "parse-options.h"

static const char * const update_server_info_usage[] = {
	"git update-server-info [--force]",
	NULL
};

int cmd_update_server_info(int argc, const char **argv, const char *prefix)
{
	int force = 0;

#ifdef USE_CPLUSPLUS_FOR_INIT
#pragma cplusplus on
#endif

	struct option options[] = {
		OPT__FORCE(&force, "update the info files from scratch"),
		OPT_END()
	};

#ifdef USE_CPLUSPLUS_FOR_INIT
#pragma cplusplus reset
#endif

	git_config(git_default_config, NULL);
	argc = parse_options(argc, argv, prefix, options,
			     update_server_info_usage, 0);
	if (argc > 0)
		usage_with_options(update_server_info_usage, options);

	return !!update_server_info(force);
}
