unsigned int hash(char *name);

void init_hash_table();

void print_table();

bool hash_table_insert(struct event_content *p);

Event_content *hash_table_lookup(char *name);

Event_content *hash_table_delete(char *name);