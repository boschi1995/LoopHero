#pragma once
#include "Stdafx.h"

class ItemData
{
	public:
		bool isDrag;
		int rating;
		POINT point;
		ItemSit state;
		vector<string> description;
		vector<function<void(BaseData&)>> setCallback;
		vector<function<void(BaseData&)>> outCallback; 

	#pragma region  Init

			ItemData(ItemSit state, POINT point )
			{ 
				this->state = state;
				this->point = point;
				isDrag = false;
				rating = RND->getInt(3);
				description.push_back(itemname());
				description.push_back(itemEffect());
				switch (state)
				{
					case Necklace: case Armor: case Shoes: case HeadGear: case Ring: case Shield:
						switch (rating)
						{
							case 0: 	setCallback.push_back(setdefence1); outCallback.push_back(outdefence1);    break;
							case 1: 	setCallback.push_back(setdefence2); outCallback.push_back(outdefence2);    break;
							case 2: 	setCallback.push_back(setdefence3); outCallback.push_back(outdefence3);    break;
						} break;
					case Weapon:
						switch (rating)
						{
							case 0: 	setCallback.push_back(setAttack1); outCallback.push_back(outAttack1);    break;
							case 1: 	setCallback.push_back(setAttack2); outCallback.push_back(outAttack2);    break;
							case 2: 	setCallback.push_back(setAttack3); outCallback.push_back(outAttack3);    break;
						} break;
				}
			};
			ItemData(ItemSit state) { this->state = state; };
			~ItemData() { };

	#pragma endregion

	private:

	#pragma region  TEXT

			string itemname()
			{
				string result;
				switch (rating)
				{
					case 0: result = "�㸧�� ";  break;
					case 1: result = "������ "; break;
					case 2: result = "������ "; break;
				}
				switch (state)
				{
					case Necklace: result.append("�����"); break;
					case Armor: result.append("����"); break;
					case Shoes: result.append("�Ź�"); break;
					case HeadGear: result.append("���"); break;
					case Ring: result.append("����"); break;
					case Shield: result.append("����"); break;
					default: result.append("����"); break;
				}
				return result;
			}

			string itemEffect()
			{
				string result;
				switch (state)
				{
					case Necklace: case Armor: case Shoes: case HeadGear: case Ring: case Shield:
							result = ("���� ���� +"); break;
					default :
							result = ("���ݷ� ���� +"); break;
				}
				switch (rating)
				{
					case 0: result.append("1");  break;
					case 1: result.append("2"); break;
					case 2: result.append("3"); break;
				}
				return result;
			}

	#pragma endregion

	#pragma region static defence

			static void setdefence1(BaseData& player) { player.deffens["min"] += 1; player.deffens["max"] += 1; }
			static void outdefence1(BaseData& player) { player.deffens["min"] -= 1;	 player.deffens["max"] -= 1; }
			static void setdefence2(BaseData& player) { player.deffens["min"] += 2; player.deffens["max"] += 2; }
			static void outdefence2(BaseData& player) { player.deffens["min"] -= 2;	 player.deffens["max"] -= 2; }
			static void setdefence3(BaseData& player) { player.deffens["min"] += 3; player.deffens["max"] += 3; }
			static void outdefence3(BaseData& player) { player.deffens["min"] -= 3;	 player.deffens["max"] -= 3; }

	#pragma endregion

	#pragma region static attack

			static void setAttack1(BaseData& player) { player.damage["min"] +=  1; player.damage["max"] += 1; }
			static void outAttack1(BaseData& player) { player.damage["min"] -= 1;  player.damage["max"] -= 1; }
			static void setAttack2(BaseData& player) { player.damage["min"] += 2;  	player.damage["max"] += 2; }
			static void outAttack2(BaseData& player) { player.damage["min"] -= 2;  	player.damage["max"] -= 2; }
			static void setAttack3(BaseData& player) { player.damage["min"] += 3;  	player.damage["max"] += 3; }
			static void outAttack3(BaseData& player) { player.damage["min"] -= 3;  	player.damage["max"] -= 3; }

	#pragma endregion

};
