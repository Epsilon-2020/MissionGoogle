#include <vector>
#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;

class product
{
private:
    /* data */
    string p_name;
    int p_price;
    vector<string> p_tags;
    bool p_sold;

public:
    product(string name, int price, vector<string> tags)
    {
        p_name = name;
        p_price = price;
        p_tags = tags;
        p_sold = false;
    }

    product()
    {
        p_name = "";
        p_price = 0;
        p_tags = {};
        p_sold = false;
    }

    void printProduct()
    {
        cout << getName() << endl;
        cout << getPrice() << endl;
        for (auto items : getTags())
        {
            cout << items << " ";
        }

        cout << endl;
    }

    string getName()
    {
        return this->p_name;
    }
    int getPrice()
    {
        return this->p_price;
    }
    bool getSold()
    {
        return this->p_sold;
    }
    vector<string> getTags()
    {
        vector<string> tagsList;
        for (auto item : this->p_tags)
        {
            tagsList.push_back(item);
        }
        return tagsList;
    }

    void setsold(bool sold)
    {
        this->p_sold = sold;
    }
};
vector<product> productList;
bool compareItemTagsWithGivenTags(vector<string> list1, vector<string> list2)
{
    // list2 size is always 3
    //bool var = false;
    int count = 0;
    for (int i = 0; i < list2.size(); i++)
    {
        for (int j = 0; j < list1.size(); j++)
        {
            if (list2[i] == list1[j])
            {
                count++;
                break;
            }
        }
    }
    return count == 3;
}
product buyProduct(vector<string> tags)
{
    int minPrice = 100000;
    int index = -1;
    for (int i = 0; i < productList.size(); i++)
    {
        //compare item tags with given tags
        // if true then check price and compare it with minPrice if less then set min price = item price and store index also in some variable and update that accordingly
        bool equal = compareItemTagsWithGivenTags(productList[i].getTags(), tags);
        //cout << i << " " << equal << endl;
        if (equal && !productList[i].getSold())
        {
            if (productList[i].getPrice() < minPrice)
            {
                minPrice = productList[i].getPrice();
                index = i;
            }
        }
    }
    if (index != -1)
    {
        productList[index].setsold(true);
        return productList[index];
    }
    else
    {
        //cout << "tsk" << endl;
        cout << "------------------------------------" << endl;
        return productList[0];
    }
}

vector<product> searchByTag(string tag)
{
    vector<product> listToReturn;
    for (int i = 0; i < productList.size(); i++)
    {
        vector<string> tags = productList[i].getTags();
        for (auto t : tags)
        {
            if (t == tag)
            {
                listToReturn.push_back(productList[i]);
                break;
            }
        }
    }
    return listToReturn;
}

vector<product> getProducts(bool soldValue)
{
    vector<product> listToReturn;
    for (int i = 0; i < productList.size(); i++)
    {
        if (productList[i].getSold() == soldValue)
        {
            listToReturn.push_back(productList[i]);
        }
    }

    return listToReturn;
}
void addProduct(product prd)
{
    productList.push_back(prd);
}

//////////////main code///////////////////////

int main()
{
    vector<string> b_tags = {"education", "novel", "student"};
    vector<string> b1_tags = {"creative", "novel", "mind"};
    vector<string> b2_tags = {"sports", "outside", "footwear", "student"};
    vector<string> b3_tags = {"mind", "novel", "student", "footwear"};
    product A("book", 200, b_tags);
    product B("book", 150, b1_tags);
    product C("Shoe", 250, b2_tags);
    product D("Pant", 180, b3_tags);
    //D.printProduct();
    addProduct(A);
    addProduct(B);
    addProduct(C);
    addProduct(D);
    addProduct(product("jersey", 10000, {"novel", "student", "footwear", "east", "west", "deagle"}));

    vector<string> buytag = {"novel", "student", "footwear"};
    product prdBrought = buyProduct(buytag);
    prdBrought.printProduct();

    prdBrought = buyProduct(buytag);
    prdBrought.printProduct();
    vector<product> searchedPrds = searchByTag("mind");
    vector<product> getPrds = getProducts(true);
    for (auto item : getPrds)
    {
        item.printProduct();
    }

    return 0;
}