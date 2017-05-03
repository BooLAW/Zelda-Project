#include "EntityManager.h"

//Constructor and destructor
EntityManager::EntityManager() {

}

EntityManager::~EntityManager() {



}

Enemy * EntityManager::CreateEnemy(uint subtype)
{
	Enemy* ret = nullptr;
	//LOG("CREATE ENEMY");
	//LOG("SUBT: %d", subtype);
	switch (subtype) {
	case t_bluesoldier:
		ret = new BSoldier();
		break;
	case t_bluearcher:
		ret = new BlueArcher();
		break;
	case t_redsoldier:
		ret = new RSoldier();
		break;
	case t_greensoldier:
		ret = new GSoldier();
		break;
	case t_hinox:
		ret = new Hinox();
		break;
	case t_rope:
		ret = new Rope();
		break;
	case t_geldman:
		ret = new Geldman();
		break;
	case t_freezor:
		ret = new Freezor();
    break;
	case t_GBat:
		ret = new GreyBat();
		break;
	case t_beamos:
		ret = new Beamos();
		break;
	case t_boss_ballandchain:
		ret = new BossChainBall();
		break;
	default:
		LOG("Unknown Enemy Type: %d", subtype);
		break;
	}

	ret->type = enemy;

	ret->Start();

	App->entitymanager->PushEntity(ret);

	//LOG("CREATE ENEMY");

	return ret;
}

Item * EntityManager::CreateItem(uint subtype)
{
	Item* ret = nullptr;

	switch (subtype) {
	case power_gauntlet:
		ret = new PowerGauntlet();
		ret->type = item;
		break;
	case pegasus_boots:
		ret = new PegasusBoots();
		ret->type = item;
		break;
	case heart_container:
		ret = new HeartContainer();
		ret->type = item;
		break;
	case boss_key:
		ret = new BossKey();
		ret->type = item;
		break;
	case drop_heart:
		ret = new DropHeart();
		ret->type = drop;
		break;
	case drop_potion:
		ret = new DropPotion();
		ret->type = drop;
		break;
	case drop_rupee:
		ret = new DropRupee();
		ret->type = drop;
		break;
	case drop_fiverupee:
		ret = new DropFiveRupee();
		ret->type = drop;
		break;
	case drop_tenrupee:
		ret = new DropTenRupee();
		ret->type = drop;
		break;
	case weapon_sword:
		ret = new ItemSword();
		ret->type = weapon;
	case weapon_bow:
		ret = new ItemBow();
		ret->type = weapon;
	default:
		LOG("Unknown Item Type: %d", subtype);
		break;
	}

	if (ret != nullptr) {
		
		ret->Start();

		App->entitymanager->PushEntity(ret);

	}

	return ret;
}

Block * EntityManager::CreateBlock(uint type)
{
	Block* ret = nullptr;
	
		switch (type) {
		case bush:
			ret = new Bush();
			break;
		case pot:
			ret = new Pot();
			break;
		case statue:
			ret = new Statue();
			break;
		case torch_bowl:
			ret = new Torch_Bowl();
			break;
		/*case torch_pillar:
			ret = new Torch_Pillar();
			break;*/
		case slabs:
			ret = new Slab();
			break;
		case slabs_no_move :
			ret = new Slab_No_Move();
			break;
		case slabs_spikes:
			ret = new Slab_Spikes();
			break;
		case button_wall:
			ret = new Button_Wall();
			break;
		case pressure_plate:
			ret = new Pressure_Plate();
			break;
		default:
			LOG("Unknown Block Type: %d", type);
			break;
									
	}
	
	ret->type = block;
	
	ret->Start();
	
	App->entitymanager->PushEntity(ret);
	
	return ret;
}



bool EntityManager::PreUpdate()
{

	for (uint i = 0; i < entities.size(); i++) {
		if (entities[i] != nullptr && entities[i]->to_delete == true) {
			entities[i]->to_delete = false;
			DestroyEnity(entities[i]);
		}
	}

	return true;
}

bool EntityManager::Update(float dt) {

	//LOG("ENTITY UPDT START");
	if(entities.empty() == false)
	for (int i = 0; i < entities.size(); i++) {
		if (entities[i] != nullptr) {
			//LOG("ENTITY UPDATE %d", i);
			if(entities[i]->active == true)
				entities[i]->Update(dt);
		}
	}
	//LOG("ENTITY UPDT END");


	return true;
}

void EntityManager::PushEntity(Entity * ent)
{
	if (ent != nullptr)
		entities.push_back(ent);
	else
		LOG("Error Pushing Entity to Entities List");
}


void EntityManager::DestroyEntities()
{
	for (uint i = 0; i < entities.size(); i++) {
		if (entities[i] != nullptr) {
			DestroyEnity(entities[i]);
			//RELEASE(entities[i]);
		}
	}
}

void EntityManager::DestroyEnity(Entity * ent)
{

	if (ent != nullptr) {

			LOG("ENTITY CLEAR");
			std::deque<Entity*>::iterator aux = std::find(entities.begin(), entities.end(), ent);
				if (aux != entities.end()) {
					entities.erase(aux);
				}
			LOG("ENTITY TYPE %d", ent->type);
			ent->CleanUp();
			LOG("ENT CLEAR");
			//std::deque<Entity*>::iterator aux = std::find(entities.begin(), entities.end(), ent);
			//if(ent != nullptr)
			//	RELEASE(ent);
			//
			//ent = nullptr;

	}

	LOG("ENTITY DESTROYED");
}

void EntityManager::OnCollision(Collider * c1, Collider * c2)
{
	
}

uint EntityManager::fromEntoPlDir(uint EnDir)
{
	uint ret = NULL;

	switch (EnDir) {
	case 0: // Up
		ret = 1;
		break;
	case 1: // Down
		ret = 4;
		break;
	case 2: // Right
		ret = 3;
		break;
	case 3: // Left
		ret = 2;
		break;
	}

	return ret;
}

