#pragma once

class BlockData
{
public:
	POINT point;
	BuildTerms build;
	WorldTerms world;
	bool isCard;
	vector<string> description;

	BlockData(BuildTerms tems, POINT point )
	{
		this->build = tems;
		this->point = point;
		this->isCard = true;
		description.push_back(itemname());
		description.push_back(itemEffect());

		switch (build)
		{
			case Pasture: case Mountain: case Rock: { world = Standard; } break;
			case Cemetery: case Forest: { world = Road; } break;
			case spiderCocoon: case VampireMansion: case StreetLamp: { world = UnderRoad; } break;
		}
	};

	BlockData() { };
	~BlockData() { };

private:
	string itemname()
	{
		string result;
		switch (build)
		{
			case Pasture: result = "목초지"; break;
			case Mountain: result = "산맥"; break;
			case Rock: result = "바위"; break;
			case Cemetery: result = "묘지"; break;
			case Forest: result = "숲"; break;
			case spiderCocoon: result = "거미 둥지"; break;
			case VampireMansion: result = "뱀파이어의 성"; break;
			case StreetLamp: result = "가로등"; break;
		}
		return result;
	}

	string itemEffect()
	{
		string result;
		switch (build)
		{
			case Pasture: result = "효과는 없다."; break;
			case Mountain: result = "효과는 없다."; break;
			case Rock: result = "효과는 없다."; break;
			case Cemetery: result = "주변에 스켈레톤을 소환한다."; break;
			case Forest: result = "효과는 없다."; break;
			case spiderCocoon: result = "주변에 거미를 소환한다."; break;
			case VampireMansion: result = "주변에 뱀파이어를 소환한다."; break;
			case StreetLamp: result = "주변 몬스터을 소환을 억제 한다."; break;
		}

		return result;
	}
};

