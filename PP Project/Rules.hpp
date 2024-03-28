#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Rules {
private:
    vector<bool> birth;
    vector<bool> death;
    int size;

public:

    Rules() {
        this->size = 9;
        this->birth = vector<bool>(size, 0);
        this->death = vector<bool>(size, 0);
    }

    Rules(int size) {
        if (not(size == 5 || size == 9)) {
            cout << "Size must be 5 or 9 now is " << size;
        }
        this->size = size;
        this->birth = vector<bool>(size, 0);
        this->death = vector<bool>(size, 0);
    }

    bool prossesCell(bool type, const vector<bool>& filter) {
        int count = 0;
        for (auto i : filter) {
            if (i == 1) {
                count++;
            }
        }
        switch (type) {
            case 0:
                if (birth[count]) {
                    return 1;
                }
                return 0;
            case 1:
                if (death[count]) {
                    return 0;
                }
                return 1;
        }
    }

    int setRules(const vector<bool>& birth, const vector<bool>& death) {
        if (birth.size() != death.size() || not(birth.size() == 5 || death.size() == 9)) {
            cout << "Size must be 5 or 9 now is " << birth.size() << " " << death.size();
        }
        this->birth = birth;
        this->death = death;
        return 0;
    }

};

