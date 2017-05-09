//��� ��������� ����� ������ ����������� ������� � ���������� ������� � ������������ � ���������������� ����������
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int AttrCnt = 0, ClsCnt = 0, ClsfCnt = 0; //������������ ��� ��������� ID-������

class ModuleAccess  //�����
{	//���� ������� ���
public:
	static ModuleAccess& Instance()
	{
		static ModuleAccess access;
		return access;
	}
	void FuzzyAC_Call() {};
private:
	ModuleAccess() {};
	~ModuleAccess() {};
	ModuleAccess(ModuleAccess const&) = delete;
	ModuleAccess& operator = (ModuleAccess const&) = delete;
};

//���������� ��������

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
	int get_level()
	{
		return level;
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
	vector <DSClass> get_classes()
	{
		return Classes;
	}
	void classify()
	{
		ModuleAccess& access = ModuleAccess::Instance(); //��������� ������ �� ����� � �������� ��� �������������
		access.FuzzyAC_Call();
	}
	vector <DSClassifier*> ptr_prev;
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
	int level;
	vector <DSAttribute> Attributes;
	vector <DSClass> Classes;
	vector <DSProbe> TrainingSet;
	vector <AttrVal> BaseObject;
};

class DSHierarchy //���������� ����������� �������� "��������", ��� ��� � ������� ����� ���� ���� ���� ��������
{
public:
	static DSHierarchy& Instance()
	{
		static DSHierarchy h;
		return h;
	}
	struct DSResults
	{
		DSClassifier* current;
		vector <ClsPr> result;
	};
	void add_attribute(DSAttribute iAt)
	{
		Attributes.push_back(iAt);
	}
	void add_class(DSClass iCl)
	{
		Classes.push_back(iCl);
	}
	void init_results_table(DSClassifier iClsf)
	{
		DSResults Rtemp;
		Rtemp.current = &iClsf;
		vector<DSClass> Ctemp = iClsf.get_classes();

		for (int i = 0; i < Ctemp.size(); i++)
		{
			ClsPr temp;
			temp.Cls = &Ctemp[i];
			temp.probability = 0;
			Rtemp.result.push_back(temp);
		}
		Ctemp.clear();
		
	}
	void load() //������� �������/�������� � �� ������, ���� �� ����� ������ ��� ������, ������� ��������
	{

	}
	void save()
	{
		
	}
private:
	DSHierarchy() {};
	~DSHierarchy() {};
	DSHierarchy(DSHierarchy const&) = delete;
	DSHierarchy& operator = (DSHierarchy const&) = delete;

	vector <vector <DSResults>> ResultsTable;
	vector <DSAttribute> Attributes;
	vector <DSClass> Classes;
};



int main() 
{	
	DSHierarchy& hierarchy = DSHierarchy::Instance();
	hierarchy.load();
	system("pause");
	return 0;
}