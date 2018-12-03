#include "data/scripts/dc_target/config.h"

#import "data/scripts/dc_target/animation.c"
#import "data/scripts/dc_target/entity.c"
#import "data/scripts/dc_target/offset.c"

// Caskey, Damon V.
// 2018-12-01
//
// Find total distance from acting enity to
// target.
float dc_target_find_total_distance_to_target(void target)
{
	float result;
	void ent;

	ent = dc_target_get_entity();

	if (typeof(target) != openborconstant("VT_PTR"))
	{
		//target = dc_target_get_target();
		return 0.0;
	}

	// Start with 0, and add the difference between acting
	// entity and target for each axis.
	result = 0.0;
	result += dc_math_difference_float(getentityproperty(target, "x"), getentityproperty(ent, "x"));
	result += dc_math_difference_float(getentityproperty(target, "y"), getentityproperty(ent, "y"));
	result += dc_math_difference_float(getentityproperty(target, "z"), getentityproperty(ent, "z"));

	// Return final result.
	return result;
}

// Caskey, Damon V.
// 2018-11-30
//
// Return true if:
//
// A) Acting entity has acing animation.
// B) Target entity is within acting
// animation range.
//
// Logic is more or less a copy of OpenBOR's own
// check_range_target_x() function.
int dc_target_check_target_in_range_x(void target)
{
	int target_pos;

	// Must have a target.
	if (typeof(target) != openborconstant("VT_PTR"))
	{
		//target = dc_target_get_target();
		return 0;
	}

	// Get position.
	target_pos = getentityproperty(target, "x");

	//  Run the range function using target's
	// position as target position.
	return dc_target_check_position_in_range_x(target_pos);
}

// Caskey, Damon V.
// 2018-11-29 (breakdown of orginal from 2017-03-18)
//
// Return true if target position is 
// within animation's X range.
int dc_target_check_position_in_range_x(float target_pos)
{
	void ent;			// Acting entity.
	int range_min;		// Minimum range.
	int range_max;		// Maximum range.
	float ent_pos;	// Current entity position.
	int animation;		// Animation to use.

	// Get action ent and position.
	ent = dc_target_get_entity();
	ent_pos = getentityproperty(ent, "x");

	// Get animation and verify entity has it.
	animation = dc_target_get_animation();

	if (!getentityproperty(ent, "animvalid", animation))
	{
		return 0;
	}

	// Use library offset if no target position provided.
	if (typeof(target_pos) != openborconstant("VT_DECIMAL"))
	{
		// Get target position.
		target_pos = dc_target_get_offset_x();
	}

	// Return true if final target location is
	// within range X min and max. Range comparison
	// is reversed when entity faces left.
	if (getentityproperty(ent, "direction") == openborconstant("DIRECTION_RIGHT"))
	{
		// Add animation range to entity X position
		// for final X range coordinates.
		range_min = ent_pos + getentityproperty(ent, "range", "xmin", animation);
		range_max = ent_pos + getentityproperty(ent, "range", "xmin", animation);

		return (target_pos >= range_min
			&& target_pos <= range_max);
	}
	else
	{
		// Subtract animation range from entity X
		// position for final X range coordinates.
		range_min = ent_pos - getentityproperty(ent, "range", "xmin", animation);
		range_max = ent_pos - getentityproperty(ent, "range", "xmin", animation);

		return (target_pos <= range_min
			&& target_pos >= range_max);
	}
}

// Caskey, Damon V.
// 2018-11-30
//
// Return true if:
//
// A) Acting entity has acing animation.
// B) Target entity is within acting
// animation range.
//
// Logic is more or less a copy of OpenBOR's own
// check_range_target_y() function.
int dc_target_check_target_in_range_y(void target)
{
	int target_pos;

	// Must have a target.
	if (typeof(target) != openborconstant("VT_PTR"))
	{
		//target = dc_target_get_target();
		return 0;
	}

	// Get positions.
	target_pos = getentityproperty(target, "y");

	//  Run the range function using target's
	// position as target position.
	return dc_target_check_position_in_range_y(target_pos);
}

// Caskey, Damon V.
// 2018-11-29 (breakdown of orginal from 2017-03-18)
//
// Return true if target position is 
// within animation's Y range.
int dc_target_check_position_in_range_y(float target_pos)
{
	void ent;			// Acting entity.
	float ent_pos;		// Entity position.
	int range_min;		// Minimum range.
	int range_max;		// Maximum range.
	float pos_current;	// Current entity position.
	int animation;		// Animation to use.

	// Get action ent and position.
	ent = dc_target_get_entity();
	ent_pos = getentityproperty(ent, "y");

	// Get animation and verify entity has it.
	animation = dc_target_get_animation();

	if (!getentityproperty(ent, "animvalid", animation))
	{
		return 0;
	}

	// Use library offset if target pos argument not given.
	if (typeof(target_pos) != openborconstant("VT_DECIMAL"))
	{
		target_pos = dc_target_get_offset_y();
	}

	// Get ranges.
	range_min = getentityproperty(ent, "range", "amin", animation);
	range_max = getentityproperty(ent, "range", "amin", animation);

	// Subtract entity Y position from target position.
	target_pos -= ent_pos;

	// Return true if final target location is
	// within range min and max.
	return (target_pos >= range_min
		&& target_pos <= range_max);
}

// Caskey, Damon V.
// 2018-11-30
//
// Return true if:
//
// A) Acting entity has acing animation.
// B) Target entity is within acting
// animation range.
//
// Logic is more or less a copy of OpenBOR's own
// check_range_target_z() function.
int dc_target_check_target_in_range_z(void target)
{
	void ent;
	int ent_pos;
	int target_pos;
	int range_min;
	int range_max;
	int animation;

	// Acting entity.
	ent = dc_target_get_entity();

	// Must have a target.
	if (typeof(target) != openborconstant("VT_PTR"))
	{
		//target = dc_target_get_target();
		return 0;
	}

	// Get animation and verify entity has it.
	animation = dc_target_get_animation();

	if (!getentityproperty(ent, "animvalid", animation))
	{
		return 0;
	}

	// Get positions.
	ent_pos = getentityproperty(ent, "z");
	target_pos = getentityproperty(target, "z");

	// Get ranges.
	range_min = getentityproperty(ent, "range", "zmin", animation);
	range_max = getentityproperty(ent, "range", "zmin", animation);

	// Subtract entity position from target position.
	target_pos -= ent_pos;

	// Return true if final target location is
	// within range min and max.
	return (target_pos >= range_min
		&& target_pos <= range_max);
}

// Caskey, Damon V.
// 2018-11-29 (breakdown of orginal from 2017-03-18)
//
// Return true if target position is 
// within animation's Z range.
int dc_target_check_position_in_range_z(float target_pos)
{
	void ent;			// Acting entity.
	float ent_pos;		// Entity position.
	int range_min;		// Minimum range.
	int range_max;		// Maximum range.
	float pos_current;	// Current entity position.
	int animation;		// Animation to use.

	// Get action ent and position.
	ent = dc_target_get_entity();
	ent_pos = getentityproperty(ent, "z");

	// Get animation and verify entity has it.
	animation = dc_target_get_animation();

	if (!getentityproperty(ent, "animvalid", animation))
	{
		return 0;
	}

	// Use library offset if target pos argument not given.
	if (typeof(target_pos) != openborconstant("VT_DECIMAL"))
	{
		target_pos = dc_target_get_offset_y();
	}

	// Get ranges.
	range_min = getentityproperty(ent, "range", "zmin", animation);
	range_max = getentityproperty(ent, "range", "zmin", animation);

	// Subtract entity position from target position.
	target_pos -= ent_pos;

	// Return true if final target location is
	// within range min and max.
	return (target_pos >= range_min
		&& target_pos <= range_max);
}

// Caskey, Damon V.
// 2018-12-03
//
// Return true if wall index is within range of animation
// range (for active entity).
int dc_target_check_wall_in_range_x(int wall, int animation)
{
	void ent;

	// Positions.
	int direction;
	float pos_x;
	float pos_z;

	// Wall position/dimensions.
	float x;
	float z;
	float depth;
	float lower_left;
	float lower_right;
	float upper_left;
	float upper_right;

	// Wall calculations.
	float coefficient_left;
	float coefficient_right;
	float test_left;
	float test_right;

	// Ranges.
	float range_x_min;
	float range_x_max;
	
	// Get acting entity and positions.
	ent = dc_target_get_entity();
	direction = getentityproperty(ent, "direction");
	pos_x = getentityproperty(ent, "x");
	pos_z = getentityproperty(ent, "z");

	// Use library animation if no animation paramater given.
	if (typeof(animation) != openborconstant("VT_INTEGER"))
	{
		animation = dc_target_get_animation();
	}

	// Get X ranges.
	range_x_min = getentityproperty(ent, "range", "xmin", animation);
	range_x_max = getentityproperty(ent, "range", "xmax", animation);

	// Combine the X range settings with current position. 
	// If facing left, we'll need subtract for X. If facing 
	// right, then we'll add.
	if (direction == openborconstant("DIRECTION_LEFT"))
	{
		range_x_min = pos_x - range_x_min;
		range_x_max = pos_x - range_x_max;
	}
	else if (direction == openborconstant("DIRECTION_RIGHT"))
	{
		range_x_min += pos_x;
		range_x_max += pos_x;
	}

	// Get wall dimensions.
	x = getlevelproperty("wall", wall, "x");
	z = getlevelproperty("wall", wall, "z");
	lower_left = getlevelproperty("wall", wall, "lowerleft");
	lower_right = getlevelproperty("wall", wall, "lowerright");
	upper_left = getlevelproperty("wall", wall, "upperleft");
	upper_right = getlevelproperty("wall", wall, "upperright");

	// This is a bit more complicated since wall bases 
	// are paralellograms and we must account for entity 
	// direction. We'll use the logic from openbor's 
	// testwall(). Calculate the coef relative to the 
	// bottom left point of wall. 
	//
	// 1. Figure out how far the entity is from the bottom of the 
	// platform.
	//
	// 2. Multiply result by the difference of the bottom left 
	// point and the top left point divided by depth of the platform.
	//
	// Repeat for the right side of wall.
	//
	// We can then use the coefs to find out if our ranges fall within
	// the wall area.

	coefficient_left	= (z - pos_z) * ((upper_left - lower_left) / depth);
	coefficient_right	= (z - pos_z) * ((upper_right - lower_right) / depth);

	// Combine wall position and lower points with
	// coefficients to get final test values we can 
	// compare to range.
	test_left	= x + lower_left + coefficient_left;
	test_right = x + lower_right + coefficient_right;

	// Test locations within horizontal range?
	if(range_x_min <= test_left && range_x_max >= test_right)
	{
		return 1;
	}

	// If we got here, return false.
	return 0;
}

// Caskey, Damon V.
// 2018-12-03
//
// Return true if wall index is within range of animation
// range (for active entity).
int dc_target_check_wall_in_range_y(int wall, int animation)
{
	void ent;

	// Positions.
	float pos_y;

	// Wall position/dimensions.
	float height;

	// Ranges.
	float range_y_min;
	float range_y_max;

	// Get acting entity and positions.
	ent = dc_target_get_entity();
	pos_y = getentityproperty(ent, "y");

	// Use library animation if no animation paramater given.
	if (typeof(animation) != openborconstant("VT_INTEGER"))
	{
		animation = dc_target_get_animation();
	}

	// Get wall height.
	height = getlevelproperty("wall", wall, "height");

	// Get vertical ranges.
	range_y_min = getentityproperty(ent, "range", "amin", animation);
	range_y_max = getentityproperty(ent, "range", "amax", animation);

	// Add entity position to Y range.
	range_y_min += pos_y;
	range_y_max += pos_y;

	// Base to wall height anywhere within vertical range?
	if (range_y_min <= height && range_y_max >= 0)
	{
		return 1;
	}

	// If we got here, return false.
	return 0;
}

// Caskey, Damon V.
// 2018-12-03
//
// Return true if wall index is within range of animation
// range (for active entity).
int dc_target_check_wall_in_range_z(int wall, int animation)
{
	void ent;

	// Positions.
	float pos_z;

	// Wall position/dimensions.
	float z;
	float depth;

	// Wall calculations.
	float test_depth;

	// Ranges
	float range_z_min;
	float range_z_max;

	// Get acting entity and positions.
	ent = dc_target_get_entity();
	pos_z = getentityproperty(ent, "z");

	// Use library animation if no animation paramater given.
	if (typeof(animation) != openborconstant("VT_INTEGER"))
	{
		animation = dc_target_get_animation();
	}

	// Get wall Z dimensions.
	z = getlevelproperty("wall", wall, "z");
	depth = getlevelproperty("wall", wall, "depth");

	// Get Z ranges.
	range_z_min = getentityproperty(ent, "range", "zmin", animation);
	range_z_max = getentityproperty(ent, "range", "zmax", animation);

	// Add entity position to Z range.
	range_z_min += pos_z;
	range_z_max += pos_z;

	// Get final test depth.
	test_depth = z + depth;
	
	// Z position to test depth anywhere within Z range?
	if (range_z_min <= z && range_z_max >= test_depth)
	{
		return 1;
	}

	// If we got here, return false.
	return 0;
}