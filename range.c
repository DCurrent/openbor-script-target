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
int dc_target_check_range_target_x(void target)
{
	int target_pos;

	// Must have a target.
	if (typeof(target) != openborconstant("VT_PTR"))
	{
		//target = dc_target_get_target();
		return 0;
	}

	// Get positions.
	target_pos = getentityproperty(target, "x");

	//  Run the range function using target's
	// position as target position.
	return dc_target_check_range_target_x(target_pos);
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
int dc_target_check_range_target_y(void target)
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
	ent_pos = getentityproperty(ent, "y");
	target_pos = getentityproperty(target, "y");

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
int dc_target_check_range_target_z(void target)
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
// within animation's Base range.
int dc_target_check_position_in_range_base()
{
	void ent;			// Acting entity.
	int range_min;		// Minimum range.
	int range_max;		// Maximum range.
	float pos_current;	// Current entity position.
	int pos_target;		// Position to varify is in range.
	int animation;		// Animation to use.

	// Get action ent and position.
	ent = dc_target_get_entity();
	pos_current = getentityproperty(ent, "base");

	// Get animation and verify entity has it.
	animation = dc_target_get_animation();

	if (!getentityproperty(ent, "animvalid", animation))
	{
		return 0;
	}

	// Get target position.
	pos_target = dc_target_get_offset_base();

	// Get ranges. We're doing the range check
	// manually, so our range needs to combine
	// range settings from an animation with
	// the acting entity's current position.
	range_min = pos_current + getentityproperty(ent, "range", "bmin", animation);
	range_max = pos_current + getentityproperty(ent, "range", "bmax", animation);

	// If the target position is less than 
	// the minimum or greater than the maximum,
	// return false immediately.
	if (pos_target < range_min)
	{
		return 0;
	}

	if (pos_target > range_max)
	{
		return 0;
	}

	// If we passed all checks, then
	// we can resturn a true result.
	return 1;
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
// 2018-11-29 (breakdown of orginal from 2017-03-18)
//
// Return true if target position is 
// within animation's Y range.
int dc_target_check_position_in_range_y()
{
	void ent;			// Acting entity.
	int range_min;		// Minimum range.
	int range_max;		// Maximum range.
	float pos_current;	// Current entity position.
	int pos_target;		// Position to varify is in range.
	int animation;		// Animation to use.

	// Get action ent and position.
	ent = dc_target_get_entity();
	pos_current = getentityproperty(ent, "y");

	// Get animation and verify entity has it.
	animation = dc_target_get_animation();

	if (!getentityproperty(ent, "animvalid", animation))
	{
		return 0;
	}

	// Get target position.
	pos_target = dc_target_get_offset_y();

	// Get ranges. We're doing the range check
	// manually, so our range needs to combine
	// range settings from an animation with
	// the acting entity's current position.
	range_min = pos_current + getentityproperty(ent, "range", "amin", animation);
	range_max = pos_current + getentityproperty(ent, "range", "amax", animation);

	// If the target position is less than 
	// the minimum or greater than the maximum,
	// return false immediately.
	if (pos_target < range_min)
	{
		return 0;
	}

	if (pos_target > range_max)
	{
		return 0;
	}

	// If we passed all checks, then
	// we can resturn a true result.
	return 1;
}

// Caskey, Damon V.
// 2018-11-29 (breakdown of orginal from 2017-03-18)
//
// Return true if target position is 
// within animation's Z range.
int dc_target_check_position_in_range_z()
{
	void ent;			// Acting entity.
	int range_min;		// Minimum range.
	int range_max;		// Maximum range.
	float pos_current;	// Current entity position.
	int pos_target;		// Position to varify is in range.
	int animation;		// Animation to use.

	// Get action ent and position.
	ent = dc_target_get_entity();
	pos_current = getentityproperty(ent, "z");

	// Get animation and verify entity has it.
	animation = dc_target_get_animation();

	if (!getentityproperty(ent, "animvalid", animation))
	{
		return 0;
	}

	// Get target position.
	pos_target = dc_target_get_offset_z();

	// Get ranges. We're doing the range check
	// manually, so our range needs to combine
	// range settings from an animation with
	// the acting entity's current position.
	range_min = pos_current + getentityproperty(ent, "range", "zmin", animation);
	range_max = pos_current + getentityproperty(ent, "range", "zmax", animation);

	// If the target position is less than 
	// the minimum or greater than the maximum,
	// return false immediately.
	if (pos_target < range_min)
	{
		return 0;
	}

	if (pos_target > range_max)
	{
		return 0;
	}

	// If we passed all checks, then
	// we can resturn a true result.
	return 1;
}