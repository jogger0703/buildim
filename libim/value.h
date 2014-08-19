#ifndef ___LIBIM_VALUE__H__
#define ___LIBIM_VALUE__H__

#include <iostream>
#include <hash_map>
#include <string>

typedef enum
{
	LIBIM_TYPE_UNKNOWN = 0,  /**< Unknown type.                     */
	LIBIM_TYPE_SUBTYPE,      /**< Subtype.                          */
	LIBIM_TYPE_CHAR,         /**< Character.                        */
	LIBIM_TYPE_UCHAR,        /**< Unsigned character.               */
	LIBIM_TYPE_BOOLEAN,      /**< Boolean.                          */
	LIBIM_TYPE_SHORT,        /**< Short integer.                    */
	LIBIM_TYPE_USHORT,       /**< Unsigned short integer.           */
	LIBIM_TYPE_INT,          /**< Integer.                          */
	LIBIM_TYPE_UINT,         /**< Unsigned integer.                 */
	LIBIM_TYPE_LONG,         /**< Long integer.                     */
	LIBIM_TYPE_ULONG,        /**< Unsigned long integer.            */
	LIBIM_TYPE_INT64,        /**< 64-bit integer.                   */
	LIBIM_TYPE_UINT64,       /**< 64-bit unsigned integer.          */
	LIBIM_TYPE_STRING,       /**< String.                           */
	LIBIM_TYPE_OBJECT,       /**< Object pointer.                   */
	LIBIM_TYPE_POINTER,      /**< Generic pointer.                  */
	LIBIM_TYPE_ENUM,         /**< Enum.                             */
	LIBIM_TYPE_BOXED         /**< Boxed pointer with specific type. */

} im_type;

/**
 * A wrapper for a type, subtype, and specific type of value.
 */
typedef struct
{
    im_type type;
    unsigned short flags;

    union
    {
        char char_data;
        unsigned char uchar_data;
        bool boolean_data;
        short short_data;
        unsigned short ushort_data;
        int int_data;
        unsigned int uint_data;
        long long_data;
        unsigned long ulong_data;
        __int64 int64_data;
        unsigned __int64 uint64_data;
        char *string_data;
        void *object_data;
        void *pointer_data;
        int enum_data;
        void *boxed_data;

    } data;

    union
    {
        unsigned int subtype;
        char *specific_type;

    } u;

} im_value;

typedef std::hash_map<std::string, void*> im_hash_table_string_void;
typedef std::hash_map<int, void*> im_hash_table_int_void;
typedef std::list<void*> im_list;


#endif