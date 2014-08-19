#ifndef ___LIBIM_CORE__H__
#define ___LIBIM_CORE__H__

#include "value.h"
#include "account.h"
#include "connection.h"
#include "blist.h"
#include "conversation.h"
#include "signal.h"

typedef struct
{
    void (*ui_prefs_init)(void);
    void (*debug_ui_init)(void);
    void (*ui_init)(void);
    void (*quit)(void);

    im_hash_table_int_void* (*get_ui_info)(void);
} im_core_ui_ops;



class im_core
{
	im_core_ui_ops* ops;
public:

	bool				init();
	void				quit();
	static im_core*		get_core();
	im_core_ui_ops*		get_ui_ops();
	void				set_ui_ops(im_core_ui_ops* ops);
};

extern im_core g_im_core;


#endif