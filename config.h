#ifndef DC_TARGET_CONFIG
#define DC_TARGET_CONFIG 1

// Dependencies
#include "data/scripts/dc_instance/main.c"
#include "data/scripts/dc_math/main.c"

// Name of library. Used mainly as a base for variable IDs. Must
// be unique vs all other libraries. Try to keep it short.
#define DC_TARGET_BASE_ID		"dctarg"

// Defaults
#define DC_TARGET_DEFAULT_ANIMATION		openborconstant("ANI_IDLE")
#define DC_TARGET_DEFAULT_ENT			getlocalvar("self")
#define DC_TARGET_DEFAULT_OFFSET_BASE	0
#define DC_TARGET_DEFAULT_OFFSET_X		0
#define DC_TARGET_DEFAULT_OFFSET_Y		0
#define DC_TARGET_DEFAULT_OFFSET_Z		0

// Variable keys.
#define DC_TARGET_MEMBER_INSTANCE		DC_TARGET_BASE_ID + 0
#define DC_TARGET_MEMBER_ANIMATION		DC_TARGET_BASE_ID + 1
#define DC_TARGET_MEMBER_ENT			DC_TARGET_BASE_ID + 2
#define DC_TARGET_MEMBER_OFFSET_BASE	DC_TARGET_BASE_ID + 3
#define DC_TARGET_MEMBER_OFFSET_X		DC_TARGET_BASE_ID + 4
#define DC_TARGET_MEMBER_OFFSET_Y		DC_TARGET_BASE_ID + 5
#define DC_TARGET_MEMBER_OFFSET_Z		DC_TARGET_BASE_ID + 6
#define DC_TARGET_MEMBER_THE_END		6			// Should always last, with a value one higher than previous key ID.

// Instance control. 
#define dc_target_get_instance()		dc_instance_get(DC_TARGET_MEMBER_INSTANCE)
#define dc_target_set_instance(value)	dc_instance_set(DC_TARGET_MEMBER_INSTANCE, value)
#define dc_target_reset_instance()		dc_instance_reset(DC_TARGET_BASE_ID, DC_TARGET_MEMBER_INSTANCE, DC_TARGET_MEMBER_THE_END)
#define dc_target_free_instance()		dc_instance_free(DC_TARGET_BASE_ID, DC_TARGET_MEMBER_INSTANCE, DC_TARGET_MEMBER_THE_END)
#define dc_target_dump_instance()		dc_instance_dump(DC_TARGET_BASE_ID, DC_TARGET_MEMBER_INSTANCE, DC_TARGET_MEMBER_THE_END)
#define dc_target_export_instance()		dc_instance_export(DC_TARGET_BASE_ID, DC_TARGET_MEMBER_INSTANCE, DC_TARGET_MEMBER_THE_END)
#define dc_target_import_instance()		dc_instance_import(DC_TARGET_BASE_ID, DC_TARGET_MEMBER_INSTANCE, DC_TARGET_MEMBER_THE_END)
#define dc_target_free_export()			dc_instance_free_export(DC_TARGET_BASE_ID, DC_TARGET_MEMBER_INSTANCE, DC_TARGET_MEMBER_THE_END)

#endif // !DC_TARGET_CONFIG
