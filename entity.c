#include "data/scripts/dc_target/config.h"

#import "data/scripts/dc_target/instance.c"

// Acting entity.
void dc_target_get_entity()
{
	int instance;
	void result;

	// Get instance.
	instance = dc_target_get_instance();

	// Get current value.
	result = getlocalvar(instance + DC_TARGET_VAR_KEY_ENT);

	// If the value is blank or wrong type,
	// use default instead.
	if (typeof(result) != openborconstant("VT_PTR"))
	{
		result = DC_TARGET_DEFAULT_ENT;
	}

	return result;
}

void dc_target_set_entity(void value)
{
	int instance;
	void result;

	// Get instance.
	instance = dc_target_get_instance();

	// Only set the value if new value
	// is different from default. No reason 
	// to waste the memory on a default value. 
	if (value != DC_TARGET_DEFAULT_ENT)
	{
		setlocalvar(instance + DC_TARGET_VAR_KEY_ENT, value);
	}	
}