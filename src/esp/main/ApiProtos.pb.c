/* Automatically generated nanopb constant definitions */
/* Generated by nanopb-0.4.0-dev at Fri May 18 17:38:10 2018. */

#include "ApiProtos.pb.h"

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif



const pb_field_t ApiResponseApps_fields[4] = {
    PB_FIELD(  1, BOOL    , SINGULAR, STATIC  , FIRST, ApiResponseApps, success, success, 0),
    PB_FIELD(  2, STRING  , SINGULAR, STATIC  , OTHER, ApiResponseApps, message, success, 0),
    PB_FIELD(  3, MESSAGE , REPEATED, CALLBACK, OTHER, ApiResponseApps, app, message, &App_fields),
    PB_LAST_FIELD
};

const pb_field_t ApiResponseMediaImages_fields[4] = {
    PB_FIELD(  1, BOOL    , SINGULAR, STATIC  , FIRST, ApiResponseMediaImages, success, success, 0),
    PB_FIELD(  2, STRING  , SINGULAR, STATIC  , OTHER, ApiResponseMediaImages, message, success, 0),
    PB_FIELD(  3, MESSAGE , REPEATED, CALLBACK, OTHER, ApiResponseMediaImages, mediaImage, message, &MediaImage_fields),
    PB_LAST_FIELD
};

const pb_field_t App_fields[9] = {
    PB_FIELD(  1, STRING  , SINGULAR, CALLBACK, FIRST, App, id, id, 0),
    PB_FIELD(  2, STRING  , SINGULAR, STATIC  , OTHER, App, name, id, 0),
    PB_FIELD(  3, STRING  , SINGULAR, STATIC  , OTHER, App, version, name, 0),
    PB_FIELD(  4, STRING  , SINGULAR, STATIC  , OTHER, App, description, version, 0),
    PB_FIELD(  5, INT32   , SINGULAR, STATIC  , OTHER, App, release_year, description, 0),
    PB_FIELD(  6, STRING  , REPEATED, CALLBACK, OTHER, App, screenshot_url, release_year, 0),
    PB_FIELD(  7, STRING  , SINGULAR, STATIC  , OTHER, App, author, screenshot_url, 0),
    PB_FIELD(  8, MESSAGE , SINGULAR, STATIC  , OTHER, App, ext_trs80, author, &Trs80Extension_fields),
    PB_LAST_FIELD
};

const pb_field_t Trs80Extension_fields[2] = {
    PB_FIELD(  1, UENUM   , SINGULAR, STATIC  , FIRST, Trs80Extension, model, model, 0),
    PB_LAST_FIELD
};

const pb_field_t MediaImage_fields[6] = {
    PB_FIELD(  1, UENUM   , SINGULAR, STATIC  , FIRST, MediaImage, type, type, 0),
    PB_FIELD(  2, STRING  , SINGULAR, STATIC  , OTHER, MediaImage, filename, type, 0),
    PB_FIELD(  3, BYTES   , SINGULAR, CALLBACK, OTHER, MediaImage, data, filename, 0),
    PB_FIELD(  4, INT64   , SINGULAR, STATIC  , OTHER, MediaImage, uploadTime, data, 0),
    PB_FIELD(  5, STRING  , SINGULAR, STATIC  , OTHER, MediaImage, description, uploadTime, 0),
    PB_LAST_FIELD
};




/* Check that field information fits in pb_field_t */
#if !defined(PB_FIELD_32BIT)
/* If you get an error here, it means that you need to define PB_FIELD_32BIT
 * compile-time option. You can do that in pb.h or on compiler command line.
 * 
 * The reason you need to do this is that some of your messages contain tag
 * numbers or field sizes that are larger than what can fit in 8 or 16 bit
 * field descriptors.
 */
PB_STATIC_ASSERT((pb_membersize(App, ext_trs80) < 65536), YOU_MUST_DEFINE_PB_FIELD_32BIT_FOR_MESSAGES_ApiResponseApps_ApiResponseMediaImages_App_Trs80Extension_MediaImage)
#endif

#if !defined(PB_FIELD_16BIT) && !defined(PB_FIELD_32BIT)
#error Field descriptor for App.description is too large. Define PB_FIELD_16BIT to fix this.
#endif


/* @@protoc_insertion_point(eof) */