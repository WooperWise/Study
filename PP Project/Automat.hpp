#pragma once

#include "Field.hpp"
#include "Rules.hpp"
#include <omp.h>

using namespace std;

class Automat {
private:
    Field field_old;
    Field field_new;
    Rules rules;
    bool filter_type;
    
public:

    Automat(vector<vector<bool>>& field, bool filter_type, const vector<bool>& birth, const vector<bool>& death) {
        this->field_old = Field(field);
        this->filter_type = filter_type;
        this->rules = Rules(filter_type ? 9 : 5);
        this->rules.setRules(birth, death);
    }
    Automat(vector<vector<bool>>& field, bool filter_type) {
        this->field_old = Field(field);
        this->filter_type = filter_type;
        this->rules = Rules(filter_type ? 9 : 5);
    }

    Automat(int x, int y, bool filter_type) {
        this->field_old = Field(x, y);
        //cout << (filter_type ? "9" : "5") << endl;
        this->rules = Rules(filter_type ? 9 : 5);
        this->filter_type = filter_type;
    }

    int setRules(const vector<bool>& birth, const vector<bool>& death) {
        this->rules.setRules(birth, death);
        return 0;
    }

    int setFieldSize(int x, int y) {
        this->field_old = Field(x, y);
        return 0;
    }

    int setFilterType(bool filter_type) {
        this->filter_type = filter_type;
        return 0;
    }

    vector<vector<bool>>& getField() {
        return this->field_old.getField();
    }

    void printField() {
        cout << this->field_old;
    }

    void generateField() {
        this->field_old.generateField();
    }

    void prossesFieldMP(int freeThreadCount) {
        this->field_new = Field(this->field_old.getSizeX(), this->field_old.getSizeY());

        #pragma omp parallel num_threads(freeThreadCount) shared(field_old, field_new)
            for (int i = 1; i < field_old.getSizeX()+1; i++) {
                for (int j = 1; j < field_old.getSizeY()+1; j++) {
                    this->field_new[i][j] = rules.prossesCell(this->field_old[i][j], this->getNeighbours(i, j));
                }
            }

        this->field_old = this->field_new;
    }

    void prossesField(int iterations) {
        this->field_new = Field(this->field_old.getSizeX(), this->field_old.getSizeY());

        for (int k = 0; k < iterations; k++) {
        
            for (int i = 1; i < field_old.getSizeX()+1; i++) {
                for (int j = 1; j < field_old.getSizeY()+1; j++) {
                    this->field_new[i][j] = rules.prossesCell(this->field_old[i][j], this->getNeighbours(i, j));
                }
            }

            this->field_old = this->field_new;
        }
    }

    vector<bool> getNeighbours(int x, int y) {
        vector<bool> result(1);
        switch (filter_type) {
            case 0:
                result.resize(4);
                result[0] = field_old[x-1][y];
                result[1] = field_old[x+1][y];
                result[2] = field_old[x][y-1];
                result[3] = field_old[x][y+1];
                return result;
            case 1:
                result.resize(8);
                result[0] = field_old[x-1][y-1];
                result[1] = field_old[x-1][y];
                result[2] = field_old[x-1][y+1];
                result[3] = field_old[x][y-1];
                result[4] = field_old[x][y+1];
                result[5] = field_old[x+1][y-1];
                result[6] = field_old[x+1][y];
                result[7] = field_old[x+1][y+1];
                return result;
        }
    }

    Automat& operator=(const Automat& other) {
        field_old = other.field_old;
        rules = other.rules;
        filter_type = other.filter_type;
        return *this;
    }

};