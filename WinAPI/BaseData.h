#pragma once
class RoadTap;

class BaseData
{
	public:
		CharacterSit character;
		POINT point;
		int state;
		map < string, int> health = { {"max",0} , {"min",0} };
		map<string, int> damage = { {"max",0} , {"min",0} };
		map<string, int> deffens = { {"max",0} , {"min",0} };
		map<string, int> stamina = { {"max",0} , {"min",0} };
		function<void(RoadTap&)> loopCallback;
	
		BaseData(CharacterSit character,POINT point)
		{
			this->character = character;
			this->state = 0;
			this->point = point;
			switch (character)
			{
				case Player: player(); break;
				case Slime: slime(); break;
				case Spider: spider(); break;
				case Skeleton: skeleton(); break;
			}
		
		};

		BaseData() {};
		~BaseData() {};

	private:

		void player()
		{
			state = 0;
			damage["min"] = 1; damage["max"] = 3;
			deffens["min"] =	 deffens["max"] = 0;
			stamina["min"] = 0; stamina["max"] = 100;
			health["max"] = health["min"] = 50;

			loopCallback = BaseData::playerLoop;
		}

		static void playerLoop(RoadTap& data) { }

		void slime()
		{
			state = 0;
			damage["min"] = 1 ;	damage["max"] = 2;
			stamina["min"] = 0;	stamina["max"] = 150;
			health["min"] = health["max"] = 10;
		}

		void spider()
		{
			state = 0;
			damage["min"] = 1;	damage["max"] = 2;
			stamina["min"] = 0;	stamina["max"] = 100;
			health["min"] = health["max"] = 10;
		}


		void skeleton()
		{
			state = 0;
			damage["min"] = 1;	damage["max"] = 2;
			stamina["min"] = 0;	stamina["max"] = 50;
			health["min"] = health["max"] = 10;
		}

};

