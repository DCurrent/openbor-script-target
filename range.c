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
	// Use library offset if no target position provided.
	if (typeof(target_pos) != openborconstant("VT_DECIMAL"))
	{
		// Get target position.
		target_pos = dc_target_get_offset_x();
	}

	dc_target_check_range_in_range_x(target_pos, target_pos);
}

// Caskey, Damon V.
// 2018-12-04
//
// Return true if any range of min/max falls within
// range of acting animation for acting entity.
int dc_target_check_range_in_range_x(float min, float max)
{
	void ent;		// Acting entity.
	int range_min;	// Minimum range.
	int range_max;	// Maximum range.
	float ent_pos;	// Current entity position.
	int animation;	// Animation to use.

	// Get action ent and position.
	ent = dc_target_get_entity();
	ent_pos = getentityproperty(ent, "x");

	// Get animation and verify entity has it.
	animation = dc_target_get_animation();

	if (!getentityproperty(ent, "animvalid", animation))
	{
		return 0;
	}
	
	// Get range settings.
	range_min = getentityproperty(ent, "range", "xmin", animation);
	range_max = getentityproperty(ent, "range", "xmax", animation);

	// Add animation range to entity X position
	// for final X range coordinates if facing
	// right. Subject if facing left.
	if (getentityproperty(ent, "direction") == openborconstant("DIRECTION_RIGHT"))
	{
		range_min = ent_pos + range_min;
		range_max = ent_pos + range_max;
	}
	else
	{
		range_min = ent_pos - range_min;
		range_max = ent_pos - range_max;		
	}

	// Return true if ranges overlap, false otherwise.
	return (range_min <= max && range_max >= min);
}

// Caskey, Damon V.
// 2018-11-30
//
// Return true if:
//
// A) Acting entity has acing animation.
// B) Target entity is within acting
// animation range.
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

int dc_target_check_position_in_range_y(float target_pos)
{
	// Use library offset if target pos argument not given.
	if (typeof(target_pos) != openborconstant("VT_DECIMAL"))
	{
		target_pos = dc_target_get_offset_y();
	}
}

// Caskey, Damon V.
// 2018-11-29 (breakdown of orginal from 2017-03-18)
//
// Return true if any range of min/max falls within
// range of acting animation for acting entity.
int dc_target_check_range_in_range_y(float min, float max)
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

	// Get ranges.
	range_min = getentityproperty(ent, "range", "amin", animation);
	range_max = getentityproperty(ent, "range", "amin", animation);

	// Subtract entity Y position from target position. We can then
	// compare the target locations directly to the range settings.
	min -= ent_pos;
	max -= ent_pos;

	// Return true if final target location is
	// within range min and max.
	// Return true if ranges overlap, false otherwise.
	return (range_min <= max && range_max >= min);
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
// Return the absolute horizontal position of a wall's
// left edge at a given Z axis.
//
// wall: Wall index.
// Z: Z posiiton. If omitted, acting entity's current Z position used.
float dc_target_find_wall_left_edge_x(int wall, float z)
{
	void ent;
	float pos_z;
	float x;
	float z;
	float depth;
	float lower_corner;
	float upper_corner;
	float coefficient;
	float result;

	// If no valid Z position is given, use acting entity's
	// current Z position.
	if (typeof(z) != openborconstant("VT_DECIMAL"))
	{
		// Get acting entity and Z position.
		ent = dc_target_get_entity();
		pos_z = getentityproperty(ent, "z");
	}	

	// Get wall dimensions.
	x = getlevelproperty("wall", wall, "x");
	z = getlevelproperty("wall", wall, "z");
	lower_corner = getlevelproperty("wall", wall, "lowerleft");
	upper_corner = getlevelproperty("wall", wall, "upperleft");

	// Walls are rectangular parallelepipeds (think cube with a parallelogram
	// as its base), so accurately calculating where the wall edge is along
	// a given lateral position can be a little complex. We'll take 
	// some cues from OpenBOR's internal testwall() function.
	//
	// 1. Get distance between the entity's and wall's Z positions. 
	//
	// 2. Multiply distance by the difference of the bottom left 
	// point and the top left point divided by depth of the platform.
	//
	// Assuming the entity's Z position is exactly halfway between the 
	// wall Z position and depth, this will produce a horizontal value
	// exacty halfway between the upper left and lower left offsets.
	// This value is our coefficient.
	//
	// Example:
	// 
	// Entity Z:	120
	// X Position:	500
	// Z Position:	200
	// Depth:		40
	// Lower Left:	0
	// Upper Left:	10
	// Coefficient:	5
	//
	// We then add the coefficient to wall's X position and the
	// lower left offset to get an absolute horizontal position 
	// of the wall's left edge. In our example above, the wall's 
	// edge is at 505.
	//
	// Because we include the entity's Z position when we calculate
	// the coefficient, as the entity moves along Z axis the coefficient 
	// changes accordingly,  This gives us a precise X location 
	// of the wall's edge relative to entity's Z position. In the
	// example above, if our entity moves to Z 170, the coefficient
	// is now 7.5, giving us an absolute wall edge of 507.5.

	// Get our coefficients.
	coefficient = (z - pos_z) * ((upper_corner - lower_corner) / depth);
	
	// Add position and the lower corner to get an absolute
	// position of the walls edge at Z axis.
	result = x + lower_corner + coefficient;

	return result;
}

// Caskey, Damon V.
// 2018-12-03
//
// Return the absolute horizontal position of a wall's
// right edge at a given Z axis.
//
// wall: Wall index.
// Z: Z posiiton. If omitted, acting entity's current Z position used.
float dc_target_find_wall_right_edge_x(int wall, float z)
{
	void ent;
	float pos_z;
	float x;
	float z;
	float depth;
	float lower_corner;
	float upper_corner;
	float coefficient;
	float result;

	// If no valid Z position is given, use acting entity's
	// current Z position.
	if (typeof(z) != openborconstant("VT_DECIMAL"))
	{
		// Get acting entity and Z position.
		ent = dc_target_get_entity();
		pos_z = getentityproperty(ent, "z");
	}

	// Get wall dimensions.
	x = getlevelproperty("wall", wall, "x");
	z = getlevelproperty("wall", wall, "z");
	lower_corner = getlevelproperty("wall", wall, "lowerright");
	upper_corner = getlevelproperty("wall", wall, "upperright");

	// See dc_target_find_wall_left_edge_x() for explanation of 
	// the coefficient.

	// Get our coefficients.
	coefficient = (z - pos_z) * ((upper_corner - lower_corner) / depth);

	// Add position and the lower corner to get an absolute
	// position of the walls edge at Z axis.
	result = x + lower_corner + coefficient;

	return result;
}

// Caskey, Damon V.
// 2018-12-03
//
// Return true if wall index is within range of animation
// range (for active entity).
int dc_target_check_wall_in_range_all(int wall, int animation)
{
	// Run range check for each axis. If any one returns
	// false, then we return false here.

	if (!dc_target_check_wall_in_range_x(wall, animation))
	{
		return 0;
	}

	if (!dc_target_check_wall_in_range_y(wall, animation))
	{
		return 0;
	}

	if (!dc_target_check_wall_in_range_z(wall, animation))
	{
		return 0;
	}

	// Made it this far, we can return true.
	return 1;
}

// Caskey, Damon V.
// 2018-12-03
//
// Return true if wall index is within horizontal 
// range of animation (for active entity).
int dc_target_check_wall_in_range_x(int wall, int animation)
{
	void ent;

	// Positions.
	int direction;
	float pos_x;
	float pos_z;

	// Wall calculations.
	float test_left;
	float test_right;

	// Ranges.
	float range_x_min;
	float range_x_max;
	
	// Get acting entity and positions.
	ent			= dc_target_get_entity();
	direction	= getentityproperty(ent, "direction");
	pos_x		= getentityproperty(ent, "x");
	pos_z		= getentityproperty(ent, "z");

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
	
	// get wall edge positions.
	test_left	= dc_target_find_wall_left_edge_x(wall, pos_z);
	test_right	= dc_target_find_wall_right_edge_x(wall, pos_z);

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
// Return true if wall index is within vertical 
// range of animation (for active entity).
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
// Return true if wall index is within lateral 
// range of animation (for active entity).
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