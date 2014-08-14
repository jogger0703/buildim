#ifndef ___LIBIM_SIGNAL__H__
#define ___LIBIM_SIGNAL__H__

#include <stdarg.h>
#include "value.h"

typedef void (*im_callback)(void);
typedef void (*im_signal_marshal_func)(im_callback cb, va_list args, void *data, void **return_val);

void im_signal_init(void);
unsigned long im_signal_register(void* instance, const char* sig, im_signal_marshal_func marshal, im_value* ret_value, int num_values, ...);

void im_marshal_VOID(
	im_callback cb, va_list args, void *data, void **return_val);
void im_marshal_VOID__INT(
	im_callback cb, va_list args, void *data, void **return_val);
void im_marshal_VOID__INT_INT(
	im_callback cb, va_list args, void *data, void **return_val);
void im_marshal_VOID__POINTER(
	im_callback cb, va_list args, void *data, void **return_val);
void im_marshal_VOID__POINTER_UINT(
	im_callback cb, va_list args, void *data, void **return_val);
void im_marshal_VOID__POINTER_INT_INT(
	im_callback cb, va_list args, void *data, void **return_val);
void im_marshal_VOID__POINTER_INT_POINTER(
	im_callback cb, va_list args, void *data, void **return_val);
void im_marshal_VOID__POINTER_POINTER(
	im_callback cb, va_list args, void *data, void **return_val);
void im_marshal_VOID__POINTER_POINTER_UINT(
	im_callback cb, va_list args, void *data, void **return_val);
void im_marshal_VOID__POINTER_POINTER_UINT_UINT(
	im_callback cb, va_list args, void *data, void **return_val);
void im_marshal_VOID__POINTER_POINTER_POINTER(
	im_callback cb, va_list args, void *data, void **return_val);
void im_marshal_VOID__POINTER_POINTER_POINTER_POINTER(
	im_callback cb, va_list args, void *data, void **return_val);
void im_marshal_VOID__POINTER_POINTER_POINTER_POINTER_POINTER(
	im_callback cb, va_list args, void *data, void **return_val);
void im_marshal_VOID__POINTER_POINTER_POINTER_UINT(
	im_callback cb, va_list args, void *data, void **return_val);
void im_marshal_VOID__POINTER_POINTER_POINTER_POINTER_UINT(
	im_callback cb, va_list args, void *data, void **return_val);
void im_marshal_VOID__POINTER_POINTER_POINTER_UINT_UINT(
	im_callback cb, va_list args, void *data, void **return_val);

void im_marshal_INT__INT(
	im_callback cb, va_list args, void *data, void **return_val);
void im_marshal_INT__INT_INT(
	im_callback cb, va_list args, void *data, void **return_val);
void im_marshal_INT__POINTER_POINTER(
	im_callback cb, va_list args, void *data, void **return_val);
void im_marshal_INT__POINTER_POINTER_POINTER(
	im_callback cb, va_list args, void *data, void **return_val);
void im_marshal_INT__POINTER_POINTER_POINTER_POINTER_POINTER(
	im_callback cb, va_list args, void *data, void **return_val);

void im_marshal_BOOLEAN__POINTER(
	im_callback cb, va_list args, void *data, void **return_val);
void im_marshal_BOOLEAN__POINTER_POINTER(
	im_callback cb, va_list args, void *data, void **return_val);
void im_marshal_BOOLEAN__POINTER_BOOLEAN(
	im_callback cb, va_list args, void *data, void **return_val);
void im_marshal_BOOLEAN__POINTER_POINTER_POINTER(
	im_callback cb, va_list args, void *data, void **return_val);
void im_marshal_BOOLEAN__POINTER_POINTER_UINT(
	im_callback cb, va_list args, void *data, void **return_val);
void im_marshal_BOOLEAN__POINTER_POINTER_POINTER_UINT(
	im_callback cb, va_list args, void *data, void **return_val);
void im_marshal_BOOLEAN__POINTER_POINTER_POINTER_POINTER(
	im_callback cb, va_list args, void *data, void **return_val);
void im_marshal_BOOLEAN__POINTER_POINTER_POINTER_POINTER_POINTER(
	im_callback cb, va_list args, void *data, void **return_val);
void im_marshal_BOOLEAN__POINTER_POINTER_POINTER_POINTER_UINT(
	im_callback cb, va_list args, void *data, void **return_val);
void im_marshal_BOOLEAN__POINTER_POINTER_POINTER_POINTER_POINTER_POINTER(
	im_callback cb, va_list args, void *data, void **return_val);

void im_marshal_BOOLEAN__INT_POINTER(
	im_callback cb, va_list args, void *data, void **return_val);

void im_marshal_POINTER__POINTER(
	im_callback cb, va_list args, void *data, void **return_val);
void im_marshal_POINTER__POINTER_INT(
	im_callback cb, va_list args, void *data, void **return_val);
void im_marshal_POINTER__POINTER_INT64(
	im_callback cb, va_list args, void *data, void **return_val);
void im_marshal_POINTER__POINTER_INT_BOOLEAN(
	im_callback cb, va_list args, void *data, void **return_val);
void im_marshal_POINTER__POINTER_INT64_BOOLEAN(
	im_callback cb, va_list args, void *data, void **return_val);
void im_marshal_POINTER__POINTER_POINTER(
	im_callback cb, va_list args, void *data, void **return_val);


#endif