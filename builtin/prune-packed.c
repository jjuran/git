#include "builtin.h"
#include "cache.h"
#include "progress.h"
#include "parse-options.h"

static const char * const prune_packed_usage[] = {
	N_("git prune-packed [-n|--dry-run] [-q|--quiet]"),
	NULL
};

static struct progress *progress;

static int prune_subdir(int nr, const char *path, void *data)
{
	int *opts = data;
	display_progress(progress, nr + 1);
	if (!(*opts & PRUNE_PACKED_DRY_RUN))
		rmdir(path);
	return 0;
}

static int prune_object(const unsigned char *sha1, const char *path,
			 void *data)
{
	int *opts = data;

	if (!has_sha1_pack(sha1))
		return 0;

	if (*opts & PRUNE_PACKED_DRY_RUN)
		printf("rm -f %s\n", path);
	else
		unlink_or_warn(path);
	return 0;
}

void prune_packed_objects(int opts)
{
	if (opts & PRUNE_PACKED_VERBOSE)
		progress = start_progress_delay(_("Removing duplicate objects"),
			256, 95, 2);

	for_each_loose_file_in_objdir(get_object_directory(),
				      prune_object, NULL, prune_subdir, &opts);

	/* Ensure we show 100% before finishing progress */
	display_progress(progress, 256);
	stop_progress(&progress);
}

int cmd_prune_packed(int argc, const char **argv, const char *prefix)
{
#ifdef USE_CPLUSPLUS_FOR_INIT
#pragma cplusplus on
#endif

	int opts = isatty(2) ? PRUNE_PACKED_VERBOSE : 0;
	const struct option prune_packed_options[] = {
		OPT_BIT('n', "dry-run", &opts, N_("dry run"),
			PRUNE_PACKED_DRY_RUN),
		OPT_NEGBIT('q', "quiet", &opts, N_("be quiet"),
			   PRUNE_PACKED_VERBOSE),
		OPT_END()
	};

#ifdef USE_CPLUSPLUS_FOR_INIT
#pragma cplusplus reset
#endif

	argc = parse_options(argc, argv, prefix, prune_packed_options,
			     prune_packed_usage, 0);

	prune_packed_objects(opts);
	return 0;
}
