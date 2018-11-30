#include "data/scripts/dc_target/config.h"

#import "data/scripts/dc_target/animation.c"
#import "data/scripts/dc_target/entity.c"
#import "data/scripts/dc_target/offset.c"

// Caskey, Damon V.
// 2018-11-29 (breakdown of orginal from 2017-03-18)
//
// Return true if target position is 
// within animation's X range.
int dc_target_check_position_in_range_x()
{
	void ent;			// Acting entity.
	int range_min;		// Minimum range.
	int range_max;		// Maximum range.
	float pos_current;	// Current entity position.
	int pos_target;		// Position to varify is in range.
	int animation;		// Animation to use.

	// Get action ent and position.
	ent = dc_target_get_entity();
	pos_current = getentityproperty(ent, "x");

	// Get animation and verify entity has it.
	animation = dc_target_get_animation();

	if (!getentityproperty(ent, "animvalid", animation))
	{
		return 0;
	}

	// Get target position.
	pos_target = dc_target_get_offset_x();

	// Get ranges. We're doing the range check
	// manually, so our range needs to combine
	// range settings from an animation with
	// the acting entity's current position.
	range_min = pos_current + getentityproperty(ent, "range", "xmin", animation);
	range_max = pos_current + getentityproperty(ent, "range", "xmax", animation);

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

