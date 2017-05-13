#include "Arena.h"

bool Arena::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

bool Arena::Start()
{
	bool ret =true;
	to_round = 0;
	starting = false;

	BROFILER_CATEGORY("StartDungeon", Profiler::Color::DarkBlue);
	curr_id = dungeon;
	stdStart();
	//GetRoom(0, 2)->AddNpc(NPC_ZELDA,500, 400, 1);
	App->player->PlayerInmortal(10);

	wave_time.Start();
	wave_time.SetFlag(true);

	spawn1 = { 200,200 };
	spawn2 = { 300,200 };
	spawn3= { 400,200 };
	spawn4 = { 500,200 };

	return ret;
}

bool Arena::Update(float dt)
{
	bool ret = true;
	BROFILER_CATEGORY("UpdateDungeon", Profiler::Color::Red)
	stdUpdate(dt);
	/*
	t_bluesoldier = 0,
		t_bluearcher,
		t_redsoldier,
		t_greensoldier,
		t_hinox,  // ciclop
		t_rope,
		t_geldman, //sandman
		t_freezor, //ghost
		t_GBat,
		t_boss_ballandchain,
		t_beamos, // eye
		t_boss_agahnim,
		t_boss_agahnimclone,
		__LAST_ENEMYTYPE*/
	AddEnemy(t_redsoldier, 0, 0, spawn1.x, spawn2.y);
	/*
	if (wave_time.Read() > 15000) {
		wave_time.SetFlag(false);
		starting = true;
		round = 1;
	}

	if (starting) {
		wave_time.Start();
		wave_time.SetFlag(true);

		if (wave_time.Read() > 15000 && to_round < round) {
			round_timer.Start();
			round_timer.SetFlag(true);
			if(round_timer.Read() > 500) {
			AddEnemy(rand() % 10, 0, 0, spawn1.x, spawn1.y);
			AddEnemy(rand() % 10, 0, 0, spawn2.x, spawn2.y);
			AddEnemy(rand() % 10, 0, 0, spawn3.x, spawn3.y);
			AddEnemy(rand() % 10, 0, 0, spawn4.x, spawn4.y);
			to_round++;
			round_timer.SetFlag(false);
			}
		}
		else {
			wave_time.SetFlag(false);
		}	

	}*/

	return ret;
}
