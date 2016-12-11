#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>
using namespace std;

struct Student
{
    int _studentId;

    // Not Needed
    //Student(int id) : _studentId(id) { }
};

class Registration
{
private:
    list<Student> _studentsList;
    unordered_map<int, list<Student>::iterator> _studentsMap;
    int _currentSize; // Size of studentsList
    int _capacity;    // Max registrants possible; Would be set to initial in the constructor
    
public:
    bool Register(Student);
    bool Deregister(Student);
    vector<Student> SelectTopM(int);
};

bool
Registration::Register(Student studentDetail)
{
    if (_currentSize == _capacity)
    {
        // Reached Capacity
        return false;
    }
    
    auto itr = _studentsMap.find(studentDetail._studentId);
    if  (itr != _studentsMap.end())
    {
        // Student already registered
        // Because student is already in the system
        return true;
    }
    
    _studentsList.push_back(studentDetail);

    // Move the iterator to the end of the list and store that in the Map
    auto tmpItr = _studentsList.begin();
    advance(tmpItr, _currentSize);
    _studentsMap[studentDetail._studentId] = tmpItr;
    cout << "TmpItr: " << (*tmpItr)._studentId << endl;
    _currentSize++;
}


bool
Registration::Deregister(Student studentDetail)
{
    auto itr = _studentsMap.find(studentDetail._studentId);
    if  (itr != _studentsMap.end())
    {
        // Student is registered. Time to deregister
        // _studentList will be a doubly linked list. If we have the address of the student where it is inserted.
        // Can go one step back and remove the next entry from the list.
        _studentsList.erase(itr->second);
        cout << "Erase: " << (*itr->second)._studentId << endl;
        _currentSize--;
    }    
    
    // Remove from Map too
    _studentsMap.erase(studentDetail._studentId);
}

vector<Student>
Registration::SelectTopM(int topM)
{
    int count = 0;
    vector<Student> topMStudents;
    for (auto itr = _studentsList.begin(); itr != _studentsList.end(); itr++)
    {
        if (count == topM)
        {
            break;
        }
        topMStudents.push_back(*itr);
        count++;
    }
    
    return topMStudents;
}

int main()
{
    {
        list<int> myList;
        unordered_map<int, list<int>::iterator> myMap;
        int count = 0;

        myList.push_back(1);
        myMap[1] = myList.begin() + count;    //<--- Why can't I do this

        // Alternatively I can do something like this
        auto tmpItr1 = myList.begin();
        advance(tmpItr1, count);
        myMap[1] = tmpItr1;
        count++;


        myList.push_back(2);
        //myMap[2] = myList.begin() + count;    <--- Why can't I do this
        auto tmpItr2 = myList.begin();
        advance(tmpItr2, count);
        myMap[2] = tmpItr2;
        count++;


        myList.push_back(3);
        //myMap[3] = myList.begin() + count;    <--- Why can't I do this
        auto tmpItr3 = myList.begin();
        advance(tmpItr3, count);
        myMap[3] = tmpItr3;
        count++;

        // Delte 2 from the list
        auto mapItr = myMap.find(2);
        if (mapItr != myMap.end())
        {
            cout << "Delte: " << *(mapItr->second) << endl;
            myList.erase(mapItr->second);
        }

        // Print the list
        for (auto entry : myList)
        {
            cout << entry << " ";
        }
        cout << endl;
    }

    {
    /*
        Registration objRegister;
        objRegister.Register({1});
        objRegister.Register({2});
        objRegister.Register({3});
        objRegister.Register({4});
        objRegister.Register({5});

        vector<Student> topN = objRegister.SelectTopM(5);
        for (auto entry : topN)
        {
            cout << entry._studentId << " " ;
        }
        cout << endl;

        // Deregister 3 
        objRegister.Deregister({3});
        vector<Student> topN2 = objRegister.SelectTopM(5);
        for (int i = 0; i < topN2.size(); i++)
        {
            cout << topN2[i]._studentId << " ";
        }
        cout << endl;

        // Reregister 3
        objRegister.Register({3});
        vector<Student> topN3 = objRegister.SelectTopM(5);
        for (int i = 0; i < topN3.size(); i++)
        {
            cout << topN3[i]._studentId << " ";
        }
        cout << endl;
    */
    }

    cout << endl;
    return 0;
}
