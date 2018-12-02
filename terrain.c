#include "data/scripts/dc_target/config.h"

#import "data/scripts/dc_target/animation.c"
#import "data/scripts/dc_target/entity.c"
#import "data/scripts/dc_target/offset.c"
#import "data/scripts/dc_target/range.c"

// Caskey, Damon V
// 2018-12-01 (Retool of original 2017-03-xx)
//
// Find nearest obstacle in range of animation.
int dc_target_find_obstacle() 
{
	int     result;			// Final result.
	void	ent;			// Acting entity.
	int		animation;		// Acting animation.
	void    target;			// Target entity pointer.
	int     target_count;	// Target Entity count.
	int     i;				// Loop cursor.
	float	distance_last;	// Last nearest distance in loop.
	float	distance_new;	// Current distance in loop.

	// Get acting entity and animation.
	ent = dc_target_get_entity();
	animation = dc_target_get_animation();

	// If this entity doesn't have the animation at all,
	// then exit. There's nothing else to do.
	if (!getentityproperty(ent, "animvalid", animation))
	{
		return result;
	}

	// Get entity count.
	target_count = openborvariant("count_entities");

	// Loop over each entity index.
	for (i = 0; i < target_count; i++)
	{
		// Get entity pointer.
		target = getentity(i);

		// If the target is not an obstacle, then
		// we're already done with this iteration
		// of the loop.
		if (getentityproperty(target, "type") != openborconstant("TYPE_OBSTACLE"))
		{
			continue;
		}

		// If the target falls out of any range, 
		// it's not a valid target, so get out of 
		// this loop iteration.

		if (!dc_target_check_target_in_range_z(target))
		{
			continue;
		}

		if (!dc_target_check_target_in_range_x(target))
		{
			continue;
		}

		if (!dc_target_check_target_in_range_y(target))
		{
			continue;
		}

		// Now we get distance to the current target in loop iteration. 
		// Then we compare that to distance from previous iteration. If
		// the previous distance doesn't exisit (this is first iteration)
		// or this iteration's distance is closer, then we record
		// distance for next iteration and the target as a result. When 
		// all targets are iterated, result will be the closest one.

		distance_new = dc_target_find_total_distance_to_target(target);

		if (distance_last || distance_new < distance_last)
		{
			distance_last = distance_new;
			result = target;
		}
	}

	// Return final result.
	return result;
}

// Caskey, Damon V.
// 2017-03-18
// 
// Get X position of screen edge if found within X range of
// animation.
int dc_target_find_edge_x()
{
	void ent;		// Acting entity.
	int result;		// Final result.
	int scroll_x;	// Screen scroll position.
	int far_x;		// Location of far screen edge.
	int animation;	// Acting animation.

	// Acting entity.
	ent = dc_target_get_entity();

	// Acting animation
	animation = dc_target_get_animation();

	// Get current scroll position, far edge position
	// and entity x position.
	scroll_x = openborvariant("xpos");
	far_x = scroll_x + openborvariant("hResolution");

	// Is scroll X in range of near screen position? Then
	// we can scroll X. Just in case scroll X is in range
	// but still 0, we'll return 1 instead.

	// Run the check and set result accordingly.
	if (dc_target_check_position_in_range_x(scroll_x))
	{
		if (scroll_x)
		{
			result = scroll_x;
		}
		else
		{
			result = 1;
		}

		return result;
	}

	// Same as above, but this time for the far edge of screen.
	if (dc_target_check_position_in_range_x(far_x))
	{
		if (far_x)
		{
			result = far_x;
		}
		else
		{
			result = 1;
		}

		return result;
	}

	// If we got this far, return the default (false).
	return result;
}
