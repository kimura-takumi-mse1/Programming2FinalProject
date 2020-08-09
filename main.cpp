#include <iostream>
#include <vector>
#include <string>
using namespace std;

//�H�ו��Ɋ܂܂��J�����[�ƎO��h�{�f�������N���X
class Food {
	string foodName;
	double calorie = 0;
	double protein = 0;
	double fat = 0;
	double carbohydrate = 0;
public:
	//�l�������Ă����֐�
	void setFoodName(const string& newName) { foodName = newName; }
	void setCalorie(double newCalorie) { calorie = newCalorie; }
	void setProtein(double newProtein) { protein = newProtein; }
	void setFat(double newFat) { fat = newFat; }
	void setCarbohydrate(double newCarbohydrate) { carbohydrate = newCarbohydrate; }
	//�l�𓾂�֐�
	string getFoodName() { return foodName; }
	double getCalorie() { return calorie; }
	double getProtein() { return protein; }
	double getFat() { return fat; }
	double getCarbohydrate() { return carbohydrate; }
	void show() { cout << "�H�ו���:" << foodName << " �J�����[[kcal]:" << calorie << " �^���p�N��[g]:" << protein << " ����[g]:" << fat << " �Y������[g]:" << carbohydrate << endl; }
};

//���͂��󂯎��I�u�W�F�N�g(�H�ו��̃f�[�^)��ǉ�����֐�
vector<Food> addFoodObject(int num) {
	vector<Food> fV; //Food�^��Vector��錾
	//�I�u�W�F�N�g��ǉ�
	for (int i = 0; i < num; i++) {
		fV.emplace_back();	//�I�u�W�F�N�g����
		string foodName;
		double calorie, protein, fat, carbohydrate;
		cout << i + 1 << "�߂̐H�ו��̖��O����͂��Ă�������: ";
		cin >> foodName;
		cout << "���̐H�ו��Ɋ܂܂��^���p�N���A�����A�Y�������̃O����������͂��Ă��������B" << endl;
		cout << "�^���p�N��[g]: "; cin >> protein;
		cout << "����[g]: "; cin >> fat;
		cout << "�Y������[g]: "; cin >> carbohydrate;
		cout << endl;
		calorie = protein * 4 + fat * 9 + carbohydrate * 4;	//�J�����[�v�Z
		fV[i].setFoodName(foodName);			//�t�[�h��
		fV[i].setCalorie(calorie);				//�J�����[
		fV[i].setProtein(protein);				//�^���p�N����
		fV[i].setFat(fat);						//������
		fV[i].setCarbohydrate(carbohydrate);	//�Y��������
	}
	return fV;
}

//�d������l�����i�[����Vector�����֐�
vector<double> select(int numOfFoodTypes, int selNum, vector<Food> fV) {
	vector<double> rV;
	switch (selNum) {
	case 1:
		for (int i = 0; i < numOfFoodTypes; i++) {
			rV.push_back(fV[i].getCalorie());
		}
		break;
	case 2:
		for (int i = 0; i < numOfFoodTypes; i++) {
			rV.push_back(fV[i].getProtein());
		}
		break;
	case 3:
		for (int i = 0; i < numOfFoodTypes; i++) {
			rV.push_back(fV[i].getFat());
		}
		break;
	case 4:
		for (int i = 0; i < numOfFoodTypes; i++) {
			rV.push_back(fV[i].getCarbohydrate());
		}
		break;
	}
	return rV;
}

//�ڕW�l�ɍ������g�ݍ��킹�����߂�֐�
int decideCombination(int numOfFoodTypes, double targetValue,vector<double> sV) {
	int rBit = 0;
	double currentSum = 0;
	for (int bit = 0; bit < (1 << numOfFoodTypes); bit++) {	//bit�S�T���őg�ݍ��킹��S�ʂ�l����
		double sum = 0;
		for (int i = 0; i < (int)sV.size(); i++) {
			if (bit & (1 << i)) sum += sV[i];
		}

		//����
		if (abs(targetValue - sum) < abs(targetValue - currentSum)) {
			currentSum = sum;
			rBit = bit;
		}
	}
	return rBit;
}

//�g�ݍ��킹��\�����鏈��
void showCombination(int sBit, vector<Food> fV) {
	double sumOfCalorie=0, sumOfProtein=0, sumOfFat=0, sumOfCarbohydrate=0;
	vector<string> slectedFoodName;
	//�I�񂾑g�ݍ��킹�̃J�����[��h�{�f�̍��v���v�Z
	for (int i = 0; i < (int)fV.size(); i++) {
		if (sBit & (1 << i)) {
			slectedFoodName.push_back(fV[i].getFoodName());
			sumOfCalorie += fV[i].getCalorie();
			sumOfProtein += fV[i].getProtein();
			sumOfFat += fV[i].getFat();
			sumOfCarbohydrate += fV[i].getCarbohydrate();
		}
	}

	//�g�ݍ��킹�̕\��
	cout << "�H�ו��̑g�ݍ��킹�́A" << endl;
	for (auto i = slectedFoodName.begin(); i != slectedFoodName.end(); i++) {	//�C�e���[�^���g�p
		cout << *i << endl;
	}
	cout << "�ł��B" << endl;
	cout << "���J�����[[kcal]: " << sumOfCalorie << endl;
	cout << "���^���p�N����[g]: " << sumOfProtein << endl;
	cout << "��������[g]: " << sumOfFat << endl;
	cout << "���Y��������[g]: " << sumOfCarbohydrate << endl;
}


//�\���������s���֐�
void showAll(vector<Food> fV) {
	for (auto& p : fV) {
		p.show();
	}
	cout << endl;
}

int main() {
	int numOfFoodTypes;
	cout << "�H�ו��̎�ނ̐�����͂��Ă�������: "; cin >> numOfFoodTypes;
	
	//�I�u�W�F�N�g(�H�ו��̃f�[�^)�̒ǉ�
	vector<Food> Foods;
	Foods = addFoodObject(numOfFoodTypes);

	//�󂯎�����f�[�^�̕\��
	cout << "�󂯎�����f�[�^�ł��B" << endl;
	showAll(Foods);

	//�ڕW�l�̎󂯎��
	double targetCalorie, targetProtein, targetFat, targetCarbohydrate;
	cout << "���ɃJ�����[�Ɖh�{�f�̖ڕW�ێ�ʂ���͂��Ă��������B" << endl;
	cout << "�J�����[[kcal]: "; cin >> targetCalorie;
	cout << "�^���p�N��[g]: "; cin >> targetProtein;
	cout << "����[g]: "; cin >> targetFat;
	cout << "�Y������[g]: "; cin >> targetCarbohydrate;
	cout << endl;
	
	//�d��������̑I�����Ă��炢�A���̒l�������i�[�����x�N�^�[���쐬
	int selNum;
	cout << "�d���������(1:�J�����[ 2:�^���p�N�� 3:���� 4:�Y������)��I�����Ă�������: "; cin >> selNum;
	vector<double> sV;
	sV = select(numOfFoodTypes, selNum, Foods);

	//�ڕW�l�ɍ����H�ו��̑g�ݍ��킹�����߂�
	int combinationBit=0;
	switch (selNum) {
	case 1:
		combinationBit = decideCombination(numOfFoodTypes, targetCalorie, sV);
		break;
	case 2:
		combinationBit = decideCombination(numOfFoodTypes, targetProtein, sV);
		break;
	case 3:
		combinationBit = decideCombination(numOfFoodTypes, targetFat, sV);
		break;
	case 4:
		combinationBit = decideCombination(numOfFoodTypes, targetCarbohydrate, sV);
		break;
	}

	//�g�ݍ��킹��\�����鏈��
	showCombination(combinationBit, Foods);

	return 0;
}