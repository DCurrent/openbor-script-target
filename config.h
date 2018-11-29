#ifndef DC_TARGET_CONFIG
#define DC_TARGET_CONFIG 1

// Defaults
#define DC_TARGET_VAR_KEY_INSTANCE	0

// Variable keys.
#define DC_TARGET_VAR_KEY_BASE_ID	"dctarg"	// Base name of every var ID. Must be unique vs. all other libraries.
#define DC_TARGET_VAR_KEY_INSTANCE	DC_TARGET_VAR_KEY_BASE_ID + 0
#define DC_TAREGT_VAR_KEY_THE_END	4			// Should always last, with a value one higher than previous key ID.

#endif // !DC_TARGET_CONFIG
