#ifndef CHECK_TAGS_H
#define CHECK_TAGS_H

/* Program argument options */
struct {
	const char *file_name;
	bool verbose;
	bool quiet;
	bool pound;
	bool slash;
	bool asterisk;
	bool s_quote;
	bool d_quote;
} options;

/* Print to screen */
#define PRINT(...) printf(__VA_ARGS__);

/* Print to stderr */
#define PRINTE(...) fprintf(stderr, "Error: "); fprintf(stderr, __VA_ARGS__);

/* Print verbose messages */
#define PRINTV(...) if (options.verbose) PRINT(__VA_ARGS__);

#endif /* CHECK_TAGS_H */
