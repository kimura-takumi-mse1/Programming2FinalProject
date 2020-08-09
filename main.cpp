#include <iostream>
#include <vector>
#include <string>
using namespace std;

//食べ物に含まれるカロリーと三大栄養素を扱うクラス
class Food {
	string foodName;
	double calorie = 0;
	double protein = 0;
	double fat = 0;
	double carbohydrate = 0;
public:
	//値を代入していく関数
	void setFoodName(const string& newName) { foodName = newName; }
	void setCalorie(double newCalorie) { calorie = newCalorie; }
	void setProtein(double newProtein) { protein = newProtein; }
	void setFat(double newFat) { fat = newFat; }
	void setCarbohydrate(double newCarbohydrate) { carbohydrate = newCarbohydrate; }
	//値を得る関数
	string getFoodName() { return foodName; }
	double getCalorie() { return calorie; }
	double getProtein() { return protein; }
	double getFat() { return fat; }
	double getCarbohydrate() { return carbohydrate; }
	void show() { cout << "食べ物名:" << foodName << " カロリー[kcal]:" << calorie << " タンパク質[g]:" << protein << " 脂質[g]:" << fat << " 炭水化物[g]:" << carbohydrate << endl; }
};

//入力を受け取りオブジェクト(食べ物のデータ)を追加する関数
vector<Food> addFoodObject(int num) {
	vector<Food> fV; //Food型のVectorを宣言
	//オブジェクトを追加
	for (int i = 0; i < num; i++) {
		fV.emplace_back();	//オブジェクト生成
		string foodName;
		double calorie, protein, fat, carbohydrate;
		cout << i + 1 << "つめの食べ物の名前を入力してください: ";
		cin >> foodName;
		cout << "その食べ物に含まれるタンパク質、脂質、炭水化物のグラム数を入力してください。" << endl;
		cout << "タンパク質[g]: "; cin >> protein;
		cout << "脂質[g]: "; cin >> fat;
		cout << "炭水化物[g]: "; cin >> carbohydrate;
		cout << endl;
		calorie = protein * 4 + fat * 9 + carbohydrate * 4;	//カロリー計算
		fV[i].setFoodName(foodName);			//フード名
		fV[i].setCalorie(calorie);				//カロリー
		fV[i].setProtein(protein);				//タンパク質量
		fV[i].setFat(fat);						//脂質量
		fV[i].setCarbohydrate(carbohydrate);	//炭水化物量
	}
	return fV;
}

//重視する値だけ格納するVectorを作る関数
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

//目標値に合った組み合わせを決める関数
int decideCombination(int numOfFoodTypes, double targetValue,vector<double> sV) {
	int rBit = 0;
	double currentSum = 0;
	for (int bit = 0; bit < (1 << numOfFoodTypes); bit++) {	//bit全探索で組み合わせを全通り考える
		double sum = 0;
		for (int i = 0; i < (int)sV.size(); i++) {
			if (bit & (1 << i)) sum += sV[i];
		}

		//判定
		if (abs(targetValue - sum) < abs(targetValue - currentSum)) {
			currentSum = sum;
			rBit = bit;
		}
	}
	return rBit;
}

//組み合わせを表示する処理
void showCombination(int sBit, vector<Food> fV) {
	double sumOfCalorie=0, sumOfProtein=0, sumOfFat=0, sumOfCarbohydrate=0;
	vector<string> slectedFoodName;
	//選んだ組み合わせのカロリーや栄養素の合計を計算
	for (int i = 0; i < (int)fV.size(); i++) {
		if (sBit & (1 << i)) {
			slectedFoodName.push_back(fV[i].getFoodName());
			sumOfCalorie += fV[i].getCalorie();
			sumOfProtein += fV[i].getProtein();
			sumOfFat += fV[i].getFat();
			sumOfCarbohydrate += fV[i].getCarbohydrate();
		}
	}

	//組み合わせの表示
	cout << "食べ物の組み合わせは、" << endl;
	for (auto i = slectedFoodName.begin(); i != slectedFoodName.end(); i++) {	//イテレータを使用
		cout << *i << endl;
	}
	cout << "です。" << endl;
	cout << "総カロリー[kcal]: " << sumOfCalorie << endl;
	cout << "総タンパク質量[g]: " << sumOfProtein << endl;
	cout << "総脂質量[g]: " << sumOfFat << endl;
	cout << "総炭水化物量[g]: " << sumOfCarbohydrate << endl;
}


//表示処理を行う関数
void showAll(vector<Food> fV) {
	for (auto& p : fV) {
		p.show();
	}
	cout << endl;
}

int main() {
	int numOfFoodTypes;
	cout << "食べ物の種類の数を入力してください: "; cin >> numOfFoodTypes;
	
	//オブジェクト(食べ物のデータ)の追加
	vector<Food> Foods;
	Foods = addFoodObject(numOfFoodTypes);

	//受け取ったデータの表示
	cout << "受け取ったデータです。" << endl;
	showAll(Foods);

	//目標値の受け取り
	double targetCalorie, targetProtein, targetFat, targetCarbohydrate;
	cout << "次にカロリーと栄養素の目標摂取量を入力してください。" << endl;
	cout << "カロリー[kcal]: "; cin >> targetCalorie;
	cout << "タンパク質[g]: "; cin >> targetProtein;
	cout << "脂質[g]: "; cin >> targetFat;
	cout << "炭水化物[g]: "; cin >> targetCarbohydrate;
	cout << endl;
	
	//重視するもの選択してもらい、その値だけを格納したベクターを作成
	int selNum;
	cout << "重視するもの(1:カロリー 2:タンパク質 3:脂質 4:炭水化物)を選択してください: "; cin >> selNum;
	vector<double> sV;
	sV = select(numOfFoodTypes, selNum, Foods);

	//目標値に合う食べ物の組み合わせを決める
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

	//組み合わせを表示する処理
	showCombination(combinationBit, Foods);

	return 0;
}