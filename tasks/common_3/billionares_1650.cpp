//
// Created by Sergey Fedorov on 07/05/2020.
//

#include <iostream>
#include <functional>
#include <set>
#include <map>

using namespace std;

typedef struct {
    string name;
    long long money;
    int days;
} City;

typedef struct {
    long long money;
    City *location;
} SuccessfulPerson;


int main() {

    int n;
    cin >> n;

    SuccessfulPerson person[n];
    City city[n + 50000];

    set<pair<long long, City *>, greater<>> ranking;
    map<string, SuccessfulPerson *> names_to_billionaires;
    map<string, City *> names_to_city;

    // Reading billionaires

    int city_index = 0;
    for (int i = 0; i < n; i++) {
        string person_name;
        string city_name;
        long long money;
        cin >> person_name >> city_name >> money;

        if (!names_to_city[city_name]) {
            city[city_index].name = city_name;
            city[city_index].money = money;
            names_to_city[city_name] = &city[city_index];
            city_index++;
        } else names_to_city[city_name]->money += money;

        person[i].money = money;
        person[i].location = names_to_city[city_name];
        names_to_billionaires[person_name] = &person[i];
    }

    for (auto &item : names_to_city) ranking.insert({item.second->money, item.second});


    // Reading days

    int m, k, cur_day = 0;
    cin >> m >> k;

    for (int i = 0; i < k; i++) {
        int day;
        string person_name;
        string city_name;
        cin >> day >> person_name >> city_name;

        int offset = day - cur_day;
        cur_day = day;

        auto it2 = ranking.begin();
        auto it = it2++;

        if (it2 == ranking.end() || it->first > it2->first) {
            it->second->days += offset;
        }

        City *to_city = names_to_city[city_name];
        SuccessfulPerson *cur_person = names_to_billionaires[person_name];

        // in case got city not listed at the start
        if (to_city == nullptr) {
            city[city_index].name = city_name;
            names_to_city[city_name] = &city[city_index];
            city_index++;

            to_city = names_to_city[city_name];
        }

        ranking.erase({cur_person->location->money, cur_person->location});
        ranking.erase({to_city->money, to_city});

        cur_person->location->money -= cur_person->money;
        ranking.insert({cur_person->location->money, cur_person->location});

        cur_person->location = to_city;
        to_city->money += cur_person->money;
        ranking.insert({to_city->money, to_city});
    }

    int days_left = m - cur_day; // m = all days
    auto it2 = ranking.begin();
    auto it = it2++;

    if (it2 == ranking.end() || it->first > it2->first) {
        it->second->days += days_left;
    }

    for (auto &item : names_to_city) {
        if (item.second->days > 0) {
            cout << item.first << " " << item.second->days << endl;
        }
    }
}

// Test
//5
//Abramovich London 15000000000
//Deripaska Moscow 10000000000
//Potanin Moscow 5000000000
//Berezovsky London 2500000000
//Khodorkovsky Chita 1000000000
//25 9
//1 Abramovich Anadyr
//5 Potanin Courchevel
//10 Abramovich Moscow
//11 Abramovich London
//11 Deripaska StPetersburg
//15 Potanin Norilsk
//20 Berezovsky Tbilisi
//21 Potanin StPetersburg
//22 Berezovsky London