//��� ��������� ����� ������ ����������� ������� � ���������� ������� � ������������ � ���������������� ����������
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int AttrCnt = 0, ClsCnt = 0, ClsfCnt = 0; //������������ ��� ��������� ID-������



class DSAttribute  //�������
{
public:
	DSAttribute(string iname, string itype) //������ ����� ������������� ����� ������(����), ��� ����� ����� ������������ � ���� ��������
	{
		AttrCnt++;
		id = "attr_" + to_string(AttrCnt);
		name = iname;
		type = itype;
	}
	~DSAttribute()
	{
		id.clear();
		name.clear();
		type.clear();
	}
private:
	string id, name, type;
};

class DSClass  //�����
{
public:
	DSClass(string iname)
	{
		ClsCnt++;
		id = "cls_" + to_string(ClsCnt);
		name = iname;
	}
	~DSClass()
	{
		id.clear();
		name.clear();
	}
private:
	string id, name;
};

struct AttrVal //��������� ��� �������� ������ �� ������� � ��� �������� � ������� �����
{
	DSAttribute *Attr;
	int value;
};

struct ClsPr //��������� ��� �������� ������ �� ����� � ������� �������������� � ����
{
	DSClass *Cls;
	int probability;
};

class DSProbe //���� ���� �� ��������� �������
{
public:
	DSProbe(vector<DSAttribute>& At, vector<DSClass>& Cl, int *values)
	{
		int i;
		AttrVal atemp;
		ClsPr ctemp;
		for (i = 0; i < At.size(); i++)  //������������ �������� ��������� � �� ���������� � ������� �� ��������� ��������������
		{
			atemp.Attr = &At[i];
			atemp.value = values[i];
			AttrVector.push_back(atemp);
		}

		for (int j = 0; j < Cl.size(); j++)
		{
			ctemp.Cls = &Cl[j];
			ctemp.probability = values[j+i];
			ClsVector.push_back(ctemp);
		}
	}
	~DSProbe()
	{
		AttrVector.clear();
		ClsVector.clear();
	}
private:
	vector <AttrVal> AttrVector;
	vector <ClsPr> ClsVector;
};

class DSClassifier
{
public:
	DSClassifier(string iname)
	{
		ClsfCnt++;
		id = "clsf_" + to_string(ClsfCnt);
		name = iname;
	}
	void add_attrib(DSAttribute iAt)
	{
		Attributes.push_back(iAt);
	}
	
	void add_class(DSClass iCl)
	{
		Classes.push_back(iCl);
	}
	void init_training_set(int *vals)
	{
		DSProbe temp(Attributes,Classes,vals);
		TrainingSet.push_back(temp);
	}
	void init_base_object(int *vals)
	{
		AttrVal temp;
		for (int i = 0; i < Attributes.size(); i++) //������������ �������� ��������� ��� �������� �������
		{
			temp.Attr = &Attributes[i];
			temp.value = vals[i];
			BaseObject.push_back(temp);
		}
	}
	DSClassifier *next; //��������� �� ��������� ������������� ��������(������� ����)
	~DSClassifier()
	{
		id.clear(); name.clear();
		Attributes.clear();
		Classes.clear();
		TrainingSet.clear();
		BaseObject.clear();
	}
private:
	string id, name;
	vector <DSAttribute> Attributes;
	vector <DSClass> Classes;
	vector <DSProbe> TrainingSet;
	vector <AttrVal> BaseObject;
};

class DSHierarchy //��� ����������� ��� ���� ��������
{
public:
	DSHierarchy();
	void load() //������� �������/�������� � �� ������, ���� �� ����� ������ ��� ������, ������� ��������
	{

	}
	void save()
	{

	}
private:
	vector<DSClassifier> Classifiers;
};

int main() 
{	
	system("pause");
	return 0;
}