#include "builtin.h"
#include "parse-options.h"
#include "refs.h"

static char const * const pack_refs_usage[] = {
	N_("git pack-refs [options]"),
	NULL
};

int cmd_pack_refs(int argc, const char **argv, const char *prefix)
{
	unsigned int flags = PACK_REFS_PRUNE;

#ifdef USE_CPLUSPLUS_FOR_INIT
#pragma cplusplus on
#endif

	struct option opts[] = {
		OPT_BIT(0, "all",   &flags, N_("pack everything"), PACK_REFS_ALL),
		OPT_BIT(0, "prune", &flags, N_("prune loose refs (default)"), PACK_REFS_PRUNE),
		OPT_END(),
	};

#ifdef USE_CPLUSPLUS_FOR_INIT
#pragma cplusplus reset
#endif

	if (parse_options(argc, argv, prefix, opts, pack_refs_usage, 0))
		usage_with_options(pack_refs_usage, opts);
	return pack_refs(flags);
}
