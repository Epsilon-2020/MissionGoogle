#include <iostream>
#include<unordered_map>
#include<vector>
#include<assert.h>
using namespace std;
#define MAX 100000
#define MAXPRICE 10000
class Product
{
public:
	Product() {};
	Product(string name, int price, int id) {
		this->price = price;
		this->id = id;
		this->name = name;
		this->sold = false;
	}
	~Product() {};
	bool isSold() {
		return this->sold;
	}
	void sell() {
		this->sold = true;
	}
	int getPrice() {
		return this->price;
	}
	string getName() {
		return this->name;
	}
private:
	int price;
	string name;
	bool sold;
	int id;
};

unordered_map <string, int> PrdMap;
unordered_map<string, vector<int>> tagMap;
unordered_map<string, vector<int>> combinationMap;
int idx = -1;
Product products[MAX];

void init() {
	idx = -1;
	PrdMap.clear();
	tagMap.clear();
	combinationMap.clear();
}

string computeHash(string a, string b, string c) {
	string small, mid, big;
	if (a < b && b < c) {
		small = a;
		mid = b;
		big = c;
	}
	else if (a < c && c < b) {
		small = a;
		mid = c;
		big = b;
	}
	else if (b < a && a < c) {
		small = b;
		mid = a;
		big = c;
	}
	else if (b < c && c < a) {
		small = b;
		mid = c;
		big = a;
	}
	else if (c < a && a < b) {
		small = c;
		mid = a;
		big = b;
	}
	else if (c < b && b < a) {
		small = c;
		mid = b;
		big = a;
	}
	else {
		assert(false);
	}

	string hash = small + ',' + mid + ',' + big;
	return hash;
}

void addProduct(string name, int price,vector<string> tags) {
	if (PrdMap.find(name) == PrdMap.end()) {
		idx++;
		Product newPrd = Product(name, price, idx);
		products[idx] = newPrd;
		PrdMap[name] = idx;
		for (string tag : tags) {
			tagMap[tag].push_back(idx);
		}
		int size = tags.size();
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size && i!=j; j++) {
				for (int k = 0; k < size && i!=k && j!=k; k++) {
					string hash = computeHash(tags[i], tags[j], tags[k]);
					combinationMap[hash].push_back(idx);
				}
			}
		}
	}
	else {
		cout << "Product name already exists\n";
	}
}

vector<Product> getProducts(bool sold) {
	vector<Product> res;
	for (int i = 0; i <= idx;i++) {
		if (products[i].isSold() == sold) {
			res.push_back(products[i]);
		}
	}
	return res;
}

vector<Product> Search(string x) {
	vector<Product> res;
	for (int idx : tagMap[x]) {
		if (products[idx].isSold() == false) {
			res.push_back(products[idx]);
		}
	}
	return res;
}

int Buy(string a, string b, string c) {
	string hash = computeHash(a, b, c);
	vector<Product> res;
	int minIdx = -1;
	int minPrice = MAXPRICE + 1;
	for (int idx : combinationMap[hash]) {
		if (!products[idx].isSold() && products[idx].getPrice() < minPrice) {
			minPrice = products[idx].getPrice();
			minIdx = idx;
		}
	}
	if (minIdx == -1) {
		return -1;
	}
	else {
		products[minIdx].sell();
		return products[minIdx].getPrice();
	}
}

void PrintProducts(vector<Product> p) {
	cout << p.size() << " results returned\n";
	for (Product prd:p) {
		cout << "name :" << prd.getName() << " price : " << prd.getPrice() << endl;
	}
	cout << endl;
	return;
}

void testStub() {
	init();
	addProduct("book", 100, { "read","edu","school","clg","student" });
	addProduct("sega pullup", 650, { "clg","football","turf","sports" });
	addProduct("nivea pullup", 1050, { "football","clg","sports" });
	PrintProducts(getProducts(false));
	PrintProducts(Search("clg"));
	cout<<Buy("football", "clg", "sports")<<endl;
	PrintProducts(Search("clg"));


}


int main()
{
	testStub();
}

