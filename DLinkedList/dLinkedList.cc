#include "../Utils/utils.h"
#include "dLinkedList.h"

int main() {
    utils::runtest("Add", {
        []() {
            DLinkedList<int> list;
            int size = 10;
            for(int idx=0; idx < size; idx++){
               list.add(idx);
            }
            auto result = list.toString();
            cout << result;
            if (result != "[0,1,2,3,4,5,6,7,8,9]") return 1;
            return 0;
        },
        []() {
            DLinkedList<int> list;
            int size = 10;
            for(int idx=0; idx < size; idx++){
               list.add(0, idx);
            }
            auto result = list.toString();
            cout << result;
            if (result != "[9,8,7,6,5,4,3,2,1,0]") return 1;
            return 0;
        },
        []() {
            DLinkedList<int> list;
            int size = 10;
            for(int idx=0; idx < size; idx++){
               list.add(list.size(), idx);
            }
            auto result = list.toString();
            cout << result;
            if (result != "[0,1,2,3,4,5,6,7,8,9]") return 1;
            return 0;
        },
    });
    utils::runtest("Get", {
        []() {
            DLinkedList<int> list;
            int size = 10;
            for(int idx=0; idx < size; idx++){
              list.add(idx);
            }
            std::string result("");
            for(int idx=0; idx < size; idx++){
              result += to_string(list.get(idx)) + " |";
            }
            std::cout << result;
            if (result != "0 |1 |2 |3 |4 |5 |6 |7 |8 |9 |") return 1;
            return 0;
        },
        []() {
            DLinkedList<int> list;
            int size = 10;
            int value[] = {2,5,6,3,67,332,43,1,0,9};
            for(int idx=0; idx < size; idx++){
              list.add(idx);
            }
            for(int idx=0; idx < size; idx++){
              list.set(idx, value[idx]);
            }
            auto result = list.toString();
            cout << result;
            if (result != "[2,5,6,3,67,332,43,1,0,9]") return 1;
            return 0;
        },
        []() {
            DLinkedList<int> list;
            int size = 10;
            int value[] = {2,5,6,3,67,332,43,1,0,9};
            for(int idx=0; idx < size; idx++){
              list.add(value[idx]);
            }
            std::string result = to_string(list.indexOf(6)) + " " + to_string(list.indexOf(100)) + " " + to_string(list.indexOf(2)) + " " + to_string(list.indexOf(9));
            cout << result;
            if (result != "2 -1 0 9") return 1;
            return 0;
        }
    });
    utils::runtest("Remove", {
        []() {
            DLinkedList<int> list;
            int size = 10;
            int value[] = {2,5,6,3,67,332,43,1,0,9};

            for(int idx=0; idx < size; idx++){
              list.add(value[idx]);
            }
            list.removeAt(0);
            auto result = list.toString();
            cout << result; 
            if (result != "[5,6,3,67,332,43,1,0,9]") return 1;
            return 0;
        },
        []() {

            DLinkedList<int> list;
            int size = 10;
            int value[] = {2,5,6,3,67,332,43,1,0,9};

            for(int idx=0; idx < size; idx++){
              list.add(value[idx]);
            }
            list.removeAt(0);
            list.removeAt(list.size() - 1);
            std::string result;
            result = to_string(list.size());
            cout << result << endl;
            if (result != "8") return 1;
            result = list.toString();
            cout << result << endl;
            if (result != "[5,6,3,67,332,43,1,0]") return 1;
            return 0;
        },
        []() {
            DLinkedList<int> list;
            int values[] = {10, 15, 2, 6, 4, 7, 40, 8};
            int index[] = {0, 1, 5, 3, 2, 1, 1, 0};

            for (int idx = 0; idx < 8; idx++)
                list.add(values[idx]);

            for(int idx=0; idx < 8; idx++){
                int idxRemoved = index[idx];
                int rs = list.removeAt(idxRemoved);
                cout << rs << "\n" << list.toString() << endl;
            }
            cout << list.empty();
            return 0;
        },
        [](){

            DLinkedList<int> list;
            if (list.size() != 0 ) return 1;

            int size = 10;
            for(int idx=0; idx < size; idx++){
                list.add(idx);
            }
            if ( list.size() != size ) return 1;
            int count = size;
            bool rem;

            for(int idx=0; idx < size; idx++){
                rem = list.removeItem(idx);
                count--;
                if ( rem == false ) return 1;
                if ( list.size() != count ) return 1;
            }
            rem = list.removeItem(100);
            if ( rem == true ) return 1;
            cout << list.toString();
            return 0;
        }
    });
}