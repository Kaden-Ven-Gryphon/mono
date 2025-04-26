use bracket_lib::prelude::*;
use specs::prelude::*;

mod components;
pub use components::*;
mod map;
pub use map::*;
mod player;
pub use player::*;
mod rect;
pub use rect::Rect;
mod visibility_system;
use visibility_system::VisibilitySystem;



#[derive(PartialEq, Copy, Clone)]
pub enum RunState { Paused, Running }

pub struct State {
	pub ecs: World,
	pub runstate : RunState
}

impl State {
	fn run_systems(&mut self) {
		let mut vis = VisibilitySystem{};
		vis.run_now(&self.ecs);
		self.ecs.maintain();
	}
}

impl GameState for State {
    fn tick(&mut self, ctx: &mut BTerm) {
		if self.runstate == RunState::Running {
			self.run_systems();
			self.runstate = RunState::Paused;
		} else {
			self.runstate = player_input(self, ctx);
		}

       ctx.cls();
	   let positions = self.ecs.read_storage::<Position>();
	   let renderables = self.ecs.read_storage::<Renderable>();
	   let map = self.ecs.fetch::<Map>();

	   draw_map(&self.ecs, ctx);

	   for (pos, render) in (&positions, &renderables).join() {
		let idx = map.xy_idx(pos.x, pos.y);
		if map.visible_tiles[idx] { ctx.set(pos.x, pos.y, render.fg, render.bg, render.glyph) }
	   }
    }
}


fn main() -> BError {
    let context = BTermBuilder::simple80x50()
        .with_title("Roguelike Tutorial")
        .build()?;

    let mut gs: State = State {
		ecs: World::new(),
		runstate : RunState::Running
	};
	gs.ecs.register::<Position>();
	gs.ecs.register::<Renderable>();
	gs.ecs.register::<Player>();
	gs.ecs.register::<Viewshed>();
	gs.ecs.register::<Monster>();
	gs.ecs.register::<Name>();

	let map = Map::new_map_rooms_and_corridors();
	let (player_x, player_y) = map.rooms[0].center();

	

	gs.ecs
		.create_entity()
		.with(Position { x: player_x, y: player_y})
		.with(Renderable {
			glyph: to_cp437('@'),
			fg: RGB::named(YELLOW),
			bg: RGB:: named(BLACK)
		})
		.with(Player {})
		.with(Viewshed{ visible_tiles: Vec::new(), range: 8, dirty: true})
		.with(Monster{})
		.build();
	

	let mut rng = RandomNumberGenerator::new();

	for (i,room) in map.rooms.iter().skip(1).enumerate() {
		let (x,y) = room.center();

		let glyph : FontCharType;
		let name : String;
		let roll = rng.roll_dice(1, 2);
		match roll {
			1 => { glyph = to_cp437('g'); name = "Goblin".to_string(); }
			_ => { glyph = to_cp437('o'); name = "Orc".to_string(); }
		}
		gs.ecs.create_entity()
			.with(Position{x, y})
			.with(Renderable{
				glyph: glyph,
				fg: RGB::named(RED),
				bg: RGB::named(BLACK)
			})
			.with(Viewshed { visible_tiles : Vec::new(), range: 8, dirty: true})
			.with(Name{ name: format!("{} #{}", &name, i)})
			.build();
	}


	gs.ecs.insert(map);


    main_loop(context, gs)
}




