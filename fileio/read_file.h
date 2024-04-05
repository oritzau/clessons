#define MIN_PRINTABLE 32
#define MAX_PRINTABLE 126
#define TABLE_SIZE MAX_PRINTABLE - MIN_PRINTABLE
void print_file_contents(const char *filepath);
void print_file_histogram(const char *filepath);
