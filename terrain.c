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
	int result = 0;		// Final result.
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
		result = far_x;
		return result;
	}

	// If we got this far, return the default (false).
	return result;
}

// Caskey, Damon V.
// 2019-11-03
//
// Get X position of screen edge if found within X range of
// animation.
float dc_target_find_wall_x()
{
	void ent;
	int wall_count;			// Number of walls in level.
	int wall_cursor;		// Wall we are currently evaluating.

	int wall_height;		// Wall height.

	float pos_x;			// Entity position, X axis.
	float pos_y;			// Entity position, Y axis.
	float pos_z;			// Entity position, Z axis.

	int wall_pos_x;			// Wall position, X axis.
	int wall_pos_z;			// Wall position, Z axis.
	int wall_depth;			// Wall size, Z axis.
	int wall_lower_left;	// Wall lower left corner.
	int wall_lower_right;	// Wall lower right corner.
	int wall_upper_left;	// Wall upper left corner.
	int wall_upper_right;	// Wall upper right corner.

	float wall_coef_left;	// Wall coefficiant, left side.
	float wall_coef_right;	// Wall coefficiant, right side.

	float wall_point_left;
	float wall_point_right;

	float distance_to_point_left;
	float distance_to_point_right;

	float result = DC_TARGET_NO_WALL_FOUND;

	ent = dc_target_get_entity();

	log("\n\n");
	log("\n dc_target_find_wall_x()");

	// Get number of walls in level.
	wall_count = openborvariant("numwalls");

	log("\n dc_target_find_wall_x, wall_count: " + wall_count);

	for (wall_cursor = 0; wall_cursor < wall_count; wall_cursor++)
	{
		log("\n\t dc_target_find_wall_x, wall_cursor: " + wall_cursor);

		// Before we bother with complex coefficient calculations, let's
		// evaluate height first. We don't care about walls below our
		// current Y position.

		wall_height = getlevelproperty("wall", wall_cursor, "height");
		pos_y = get_entity_property(ent, "position_y");

		log("\n\t dc_target_find_wall_x, wall_height: " + wall_height);
		log("\n\t dc_target_find_wall_x, pos_y: " + pos_y);


		if (wall_height < pos_y)
		{
			continue;
		}

		// If not within wall's Z area, exit.

		pos_z = get_entity_property(ent, "position_z");
		wall_pos_z = getlevelproperty("wall", wall_cursor, "z");
		wall_depth = getlevelproperty("wall", wall_cursor, "depth");

		log("\n\t dc_target_find_wall_x, pos_z: " + pos_z);
		log("\n\t dc_target_find_wall_x, wall_pos_z: " + wall_pos_z);
		log("\n\t dc_target_find_wall_x, wall_depth: " + wall_depth);

		if (!(pos_z <= wall_pos_z && pos_z >= wall_pos_z - wall_depth))
		{
			continue;
		}

		// Now we need to know if the wall is in X range. This gets a bit more
		// complex since walls may have angled sides. We'll need to find a
		// coefficiant for the left and right side based on our Z position 
		// in relation to the wall. This is the same basic formula used by
		// the engine's native wall check. 
		//
		// Once we have the coefficiants, we'll create a final point by 
		// combining them with the wall's X position and corner offsets.
		// We can then send those on to the range function to compare with
		// animation range.

		wall_pos_x = getlevelproperty("wall", wall_cursor, "x");
		wall_lower_left = getlevelproperty("wall", wall_cursor, "lowerleft");
		wall_upper_left = getlevelproperty("wall", wall_cursor, "upperleft");
		wall_lower_right = getlevelproperty("wall", wall_cursor, "lowerright");
		wall_upper_right = getlevelproperty("wall", wall_cursor, "upperright");

		wall_coef_left = (wall_pos_z - pos_z) * ((wall_upper_left - wall_lower_left) / wall_depth);
		wall_coef_right = (wall_pos_z - pos_z) * ((wall_upper_right - wall_lower_right) / wall_depth);

		wall_point_left = wall_pos_x + wall_lower_left + wall_coef_left;
		wall_point_right = wall_pos_x + wall_lower_right + wall_coef_right;

		log("\n\t dc_target_find_wall_x, wall_pos_x: " + wall_pos_x);
		log("\n\t dc_target_find_wall_x, wall_lower_left: " + wall_lower_left);
		log("\n\t dc_target_find_wall_x, wall_upper_left: " + wall_upper_left);
		log("\n\t dc_target_find_wall_x, wall_lower_right: " + wall_lower_right);
		log("\n\t dc_target_find_wall_x, wall_upper_right: " + wall_upper_right);
		log("\n\t dc_target_find_wall_x, wall_coef_left: " + wall_coef_left);
		log("\n\t dc_target_find_wall_x, wall_coef_right: " + wall_coef_right);
		log("\n\t dc_target_find_wall_x, wall_point_left: " + wall_point_left);
		log("\n\t dc_target_find_wall_x, wall_point_right: " + wall_point_right);

		// If the wall is not in range, go to next loop. If the wall IS in range
		// break out of loop and set result 1.
		if (!dc_target_check_range_in_range_x(wall_point_left, wall_point_right))
		{
			continue;
		}
		else
		{
			result = DC_TARGET_WALL_FOUND;
			break;
		}
	}

	log("\n\t dc_target_find_wall_x, result (post loop): " + result);

	// If result == DC_TARGET_WALL_FOUND, then loop found a wall within animation range. 
	// Now we need to decide which side to send as a result. Get the entity location, 
	// compare its distance to both wall points and send the closer one as a result.
	if (result == DC_TARGET_WALL_FOUND)
	{
		pos_x = get_entity_property(ent, "position_x");

		distance_to_point_left = dc_math_difference_float(pos_x, wall_point_left);
		distance_to_point_right = dc_math_difference_float(pos_x, wall_point_right);

		log("\n\t dc_target_find_wall_x, pos_x: " + pos_x);
		log("\n\t dc_target_find_wall_x, distance_to_point_left: " + distance_to_point_left);
		log("\n\t dc_target_find_wall_x, distance_to_point_right: " + distance_to_point_right);

		// Use closer side. In the unlikely event we are exactly the same
		// distance to both sides, default to left.
		if (distance_to_point_left <= distance_to_point_right)
		{
			result = wall_point_left;
		}
		else
		{
			result = wall_point_right;
		}
	}
	
	log("\n\t dc_target_find_wall_x, result (final): " + result);

	return result;

}