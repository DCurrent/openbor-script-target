#include "data/scripts/dc_target/config.h"

#import "data/scripts/dc_target/animation.c"
#import "data/scripts/dc_target/entity.c"
#import "data/scripts/dc_target/offset.c"
#import "data/scripts/dc_target/range.c"

// Returns x position of first obstacle in range of animation.
int dc_target_find_obstacle_x() {

	int     result;			// Final result.
	void	ent;			// Acting entity.
	int		animation;		// Acting animation.
	void    target;			// Target entity pointer.
	int     target_count;	// Target Entity count.
	int     i;				// Loop cursor.

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

		// If the target falls out off any range, 
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

		// If we'e made it this far, we've found a valid
		// target. Use the current target x position as
		// a result and exit loop.
		result = getentityproperty(target, "x");
		break;
	}

	// Return final result.
	return result;
}

