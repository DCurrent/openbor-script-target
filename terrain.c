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
	float   target_x;		// Position of entity on X axis.
	float   target_y;		// Position of entity on Y axis.
	float   target_z;		// Position of entity on Z axis.
	int     target_h;		// Target's height setting.
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

		// Get target location.
		target_x = getentityproperty(target, "x");
		target_y = getentityproperty(target, "y");
		target_z = getentityproperty(target, "z");
		target_h = getentityproperty(target, "height");

		// Add height to target's Y position.
		target_y += target_h;

		// If the target falls out off any range, 
		// it's not a valid target, so get out of 
		// this loop iteration.

		dc_target_set_offset_z(target_z);

		if (!dc_target_check_position_in_range_z())
		{
			continue;
		}

		if (!dc_target_check_range_target_x(target))
		{
			continue;
		}

		dc_target_set_offset_y(target_y);

		if (!dc_target_check_position_in_range_y())
		{
			continue;
		}

		// If we'e made it this far, we've found a valid
		// target. Use the current target x position as
		// a result and exit loop.
		result = target_x;
		break;
	}

	// Return final result.
	return result;
}

