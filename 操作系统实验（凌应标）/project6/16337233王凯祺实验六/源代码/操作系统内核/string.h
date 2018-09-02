int strlen(char *s) {
	int i = 0;
	while (s[i]) ++i;
	return i;
}

int strcmp(char *a, char *b) {
	int la = strlen(a);
	int lb = strlen(b);
	int i = 0;
	for (; i < la || i < lb; ++i)
		if (a[i] > b[i])
			return 1;
		else if (a[i] < b[i])
			return -1;
	return 0;
}

int prefix_match(char *text, char *pattern) {
	int la = strlen(pattern);
	int lb = strlen(text);
	int i = 0;
	if (la > lb) return 0;
	for (; i < la; ++i)
		if (text[i] != pattern[i]) return 0;
	return text[la] <= 32;
}