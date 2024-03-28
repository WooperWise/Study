#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Field {
private:
    vector<vector<bool>> field;

public:
    void generateField() {
        for (int i = 1; i < field.size()-1; i++) {
            for (int j = 1; j < field[0].size()-1; j++) {
                field[i][j] = rand() % 2;
            }
        }
    }

    Field(vector<vector<bool>>& field) {
        this->field = field;
    }

    Field() {
        field = vector<vector<bool>>(10, vector<bool>(10, 0));
    }

    Field(int x, int y) {
        field = vector<vector<bool>>(x+2, vector<bool>(y+2, 0));
    }

    vector<bool>& operator[](int index) {
        return field[index];
    }

    const vector<bool>& operator[](int index) const {
        return field[index];
    }

    Field& operator=(const Field& other) {
        field = other.field;
        return *this;
    }

    friend ostream& operator<<(ostream& os, const Field& obj) {
        for (const auto& row : obj.field) {
            for (bool num : row) {
                os << num << " ";
            }
            os << endl;
        }
        return os;
    }

    vector<vector<bool>>& getField() {
        return field;
    }

    auto getSizeX() {
        return field.size()-2;
    }

    auto getSizeY() {
        return field[0].size()-2;
    }
};