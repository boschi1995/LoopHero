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
			case Pasture: result = "������"; break;
			case Mountain: result = "���"; break;
			case Rock: result = "����"; break;
			case Cemetery: result = "����"; break;
			case Forest: result = "��"; break;
			case spiderCocoon: result = "�Ź� ����"; break;
			case VampireMansion: result = "�����̾��� ��"; break;
			case StreetLamp: result = "���ε�"; break;
		}
		return result;
	}

	string itemEffect()
	{
		string result;
		switch (build)
		{
			case Pasture: result = "ȿ���� ����."; break;
			case Mountain: result = "ȿ���� ����."; break;
			case Rock: result = "ȿ���� ����."; break;
			case Cemetery: result = "�ֺ��� ���̷����� ��ȯ�Ѵ�."; break;
			case Forest: result = "ȿ���� ����."; break;
			case spiderCocoon: result = "�ֺ��� �Ź̸� ��ȯ�Ѵ�."; break;
			case VampireMansion: result = "�ֺ��� �����̾ ��ȯ�Ѵ�."; break;
			case StreetLamp: result = "�ֺ� ������ ��ȯ�� ���� �Ѵ�."; break;
		}

		return result;
	}
};

