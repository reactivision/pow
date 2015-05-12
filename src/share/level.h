struct level {
	float *geom;
	long ngeom;
};

int level_parse(struct level *to, const char *data);
int level_parsef(struct level *to, const char *path);

