#pragma once

class BattleTap : public GameNode
{
	enum CharacterState
	{
		Idle, Attack, Hit, Die
	};

	class Battledata : public BaseData
	{
		public:
			CharacterState ani;
			int aniStack;
			int Dely;
			RECT healthBar;
			RECT staminaBar;
	};


	private:
		Battledata player;
		vector<Battledata> _monster;
		void battle();

		string EnumToText(CharacterSit sit);
	public:
		BaseData getPlayer();
		void setMatching(vector<BaseData>);
		int getVictory();

#pragma region MyRegion

	public:
		HRESULT init(void);
		void release(void);
		void update(void);
		void render(void);
		BattleTap() { init(); };
		~BattleTap() { };

#pragma endregion

};
