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

		if (!dc_target_check_range_target_z(target))
		{
			continue;
		}

		if (!dc_target_check_range_target_x(target))
		{
			continue;
		}

		if (!dc_target_check_range_target_y(target))
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

