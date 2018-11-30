#include "data/scripts/dc_target/config.h"

#import "data/scripts/dc_target/instance.c"

// X axis offset.
int dc_target_get_offset_x()
{
	int instance;
	int result;

	// Get instance.
	instance = dc_target_get_instance();

	// Get current value.
	result = getlocalvar(instance + DC_TARGET_VAR_KEY_OFFSET_X);

	// If the value is blank or wrong type,
	// use default instead.
	if (typeof(result) != openborconstant("VT_INTEGER"))
	{
		result = DC_TARGET_DEFAULT_OFFSET_X;
	}

	return result;
}

int dc_target_set_offset_x(int value)
{
	int instance;

	// Get instance.
	instance = dc_target_get_instance();

	// Only set the value if new value
	// is different from default. No reason 
	// to waste the memory on a default value.
	if (value != DC_TARGET_DEFAULT_OFFSET_X)
	{
		setlocalvar(instance + DC_TARGET_VAR_KEY_OFFSET_X, value);
	}	
}

// Y axis offset.
int dc_target_get_offset_y()
{
	int instance;
	int result;

	// Get instance.
	instance = dc_target_get_instance();

	// Get current value.
	result = getlocalvar(instance + DC_TARGET_VAR_KEY_OFFSET_Y);

	// If the value is blank or wrong type,
	// use default instead.
	if (typeof(result) != openborconstant("VT_INTEGER"))
	{
		result = DC_TARGET_DEFAULT_OFFSET_Y;
	}

	return result;
}

int dc_target_set_offset_y(int value)
{
	int instance;

	// Get instance.
	instance = dc_target_get_instance();

	// Only set the value if new value
	// is different from default. No reason 
	// to waste the memory on a default value.
	if (value != DC_TARGET_DEFAULT_OFFSET_Y)
	{
		setlocalvar(instance + DC_TARGET_VAR_KEY_OFFSET_Y, value);
	}
}

// Z axis offset.
int dc_target_get_offset_z()
{
	int instance;
	int result;

	// Get instance.
	instance = dc_target_get_instance();

	// Get current value.
	result = getlocalvar(instance + DC_TARGET_VAR_KEY_OFFSET_Z);

	// If the value is blank or wrong type,
	// use default instead.
	if (typeof(result) != openborconstant("VT_INTEGER"))
	{
		result = DC_TARGET_DEFAULT_OFFSET_Z;
	}

	return result;
}

int dc_target_set_offset_z(int value)
{
	int instance;

	// Get instance.
	instance = dc_target_get_instance();

	// Only set the value if new value
	// is different from default. No reason 
	// to waste the memory on a default value.
	if (value != DC_TARGET_DEFAULT_OFFSET_Z)
	{
		setlocalvar(instance + DC_TARGET_VAR_KEY_OFFSET_Z, value);
	}
}