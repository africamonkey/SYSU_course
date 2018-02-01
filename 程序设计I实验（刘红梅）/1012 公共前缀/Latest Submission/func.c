char * prefix(char* s1, char* s2) {
	char *s = (char*)malloc(sizeof(char) * 51);
  int n = strlen(s1), m = strlen(s2);
  if (m < n) n = m;
  for (int i=0;i<n;i++) {
    if (s1[i] == s2[i]) s[i] = s1[i];
    else {
      n = i;
      break;
    }
  }
  s[n] = 0;
  return s;
}