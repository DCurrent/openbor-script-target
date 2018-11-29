#ifndef DC_TARGET_CONFIG
#define DC_TARGET_CONFIG 1

// Defaults
#define DC_TARGET_DEFAULT_INSTANCE	0
#define DC_TARGET_DEFAULT_ANIMATION	openborconstant("ANI_IDLE")
#define DC_TARGET_DEFAULT_ENT		getlocalvar("self")
#define DC_TARGET_DEFAULT_OFFSET_X	0
#define DC_TARGET_DEFAULT_OFFSET_Y	0
#define DC_TARGET_DEFAULT_OFFSET_Z	0

// Variable keys.
#define DC_TARGET_VAR_KEY_BASE_ID	"dctarg"	// Base name of every var ID. Must be unique vs. all other libraries.
#define DC_TARGET_VAR_KEY_INSTANCE	DC_TARGET_VAR_KEY_BASE_ID + 0
#define DC_TARGET_VAR_KEY_ANIMATION DC_TARGET_VAR_KEY_BASE_ID + 1
#define DC_TARGET_VAR_KEY_ENT		DC_TARGET_VAR_KEY_BASE_ID + 2
#define DC_TARGET_VAR_KEY_OFFSET_X	DC_TARGET_VAR_KEY_BASE_ID + 3
#define DC_TARGET_VAR_KEY_OFFSET_Y	DC_TARGET_VAR_KEY_BASE_ID + 4
#define DC_TARGET_VAR_KEY_OFFSET_Z	DC_TARGET_VAR_KEY_BASE_ID + 5
#define DC_TAREGT_VAR_KEY_THE_END	6			// Should always last, with a value one higher than previous key ID.

#endif // !DC_TARGET_CONFIG
