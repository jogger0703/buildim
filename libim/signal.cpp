#include "signal.h"
#include "value.h"

typedef struct
{
	void *instance;

	im_hash_table_int_void *signals;
	size_t signal_count;

	unsigned long next_signal_id;

} im_instance_data;

typedef struct
{
	unsigned long id;

	im_signal_marshal_func marshal;

	int num_values;
	im_value **values;
	im_value *ret_value;

	im_list *handlers;
	size_t handler_count;

	unsigned long next_handler_id;
} im_signal_data;

static im_hash_table_int_void g_instance_table;

void im_signal_init(void)
{
	
}

unsigned long im_signal_register(void* instance, const char* sig, 
						im_signal_marshal_func marshal, 
						im_value* ret_value, int num_values, ...)
{
	return 0;
}