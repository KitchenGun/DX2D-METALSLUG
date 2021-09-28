#pragma once
class ItemManager
{
public:
	ItemManager(PlayerManager* pm);
	~ItemManager();

	void Update();
	void Render();

	void AddItem(Vector3 position,PROJECTILETYPE pt);
	void RemoveItem(Item* tempItem);

	list<Item*> GetItemList() { return itemList; }
	void SetPM(PlayerManager* val) { pm=val; }
private:
	list<Item*> itemList;
	list<Item*>::iterator iter;

	PlayerManager* pm=nullptr;
};