use specs::prelude::*;
use super::{Viewshed, Position, Map, Player};
use bracket_lib::{geometry::Point, pathfinding::field_of_view};

pub struct VisibilitySystem {}

impl<'a> System<'a> for VisibilitySystem {
	type SystemData = ( WriteExpect<'a, Map>,
						WriteStorage<'a, Viewshed>,
						WriteStorage<'a, Position>,
						Entities<'a>,
						ReadStorage<'a, Player>,);
	
	fn run(&mut self, data : Self::SystemData) {
		let (mut map, mut viewshed, pos, entities, player) = data;

		for (ent, viewshed, pos) in (&entities, &mut viewshed, &pos).join() {
			if viewshed.dirty {
				viewshed.dirty = false;
				viewshed.visible_tiles.clear();
				viewshed.visible_tiles = field_of_view(Point::new(pos.x, pos.y), viewshed.range, &*map);
				viewshed.visible_tiles.retain(|p| p.x >= 0 && p.x < map.width && p.y >= 0 && p.y < map.height );
				
				let _p : Option<&Player> = player.get(ent);
				if let Some(_p) = _p {
					for t in map.visible_tiles.iter_mut() { *t = false };
					for vis in viewshed.visible_tiles.iter() {
						let idx = map.xy_idx(vis.x, vis.y);
						map.revealed_tiles[idx] = true;
						map.visible_tiles[idx] = true;
					}
			
				}
			}
		}
	}
}