#include "EntityManager.h"

//Constructor and destructor
EntityManager::EntityManager() {

}

EntityManager::~EntityManager() {



}

Enemy * EntityManager::CreateEnemy(uint subtype)
{
	Enemy* ret = nullptr;
	LOG("CREATE ENEMY");
	LOG("SUBT: %d", subtype);
	switch (subtype) {
	case t_bluesoldier:
		ret = new BSoldier();
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

	LOG("CREATE ENEMY");

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
		ret->type = item;
	case weapon_bow:
		ret = new ItemBow();
		ret->type = item;
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
		default:
			LOG("Unknown Block Type: %d", type);
			break;
									
	}
	
	ret->type = block;
	
	ret->Start();
	
	App->entitymanager->PushEntity(ret);
	
	return ret;
}

bool EntityManager::Update(float dt) {

	for (int i = 0; i < entities.size(); i++) {
		if(entities[i] != nullptr)
			entities[i]->Update(dt);
	}


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
			entities[i]->CleanUp();
			delete entities[i];
		}
	}
}

void EntityManager::DestroyEnity(Entity * ent)
{

	if(ent != nullptr)
		ent->CleanUp();

	std::deque<Entity*>::iterator aux = std::find(entities.begin(), entities.end(), ent);
	//RELEASE(ent);
	entities.erase(aux);
}

void EntityManager::OnCollision(Collider * c1, Collider * c2)
{
	
}

