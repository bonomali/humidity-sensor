void postToURL(char *message);
void postToIFTTT(char *data);
void postToThingSpeak(char *data);
void postToLoggly(char *data);
size_t noop_cb(void *ptr, size_t size, size_t nmemb, void *data);