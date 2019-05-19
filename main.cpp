#include <iostream>
#include <string>
#include <fstream>
#include <math.h>

using namespace std;

class Student
{
    string first_name, last_name, patromymic, group, birthday;
    Student **head;
    int size_of_student;
public:
    Student()
    {
        cout << "Введите данные следующего студента." << endl;
        cout << "Фамилия: ";
        cin >> first_name;
        cout << "Имя: ";
        cin >> last_name;
        cout << "Отчество: ";
        cin >> patromymic;
        cout << "Номер группы: ";
        cin >> group;
        cout << "Дата рождения: ";
        cin >> birthday;
    }

    Student(bool read_from_file)
    {
        if (read_from_file == true)
        {
            cin >> first_name;
            cin >> last_name;
            cin >> patromymic;
            cin >> group;
            cin >> birthday;
        }
    }

    Student(int inp_size_of_student, bool read_from_file)
    {
        this->size_of_student = inp_size_of_student;
        this->head = new Student*[size_of_student];
        for (int i = 0; i < this->size_of_student; i++)
        {
            this->head[i] = new Student(read_from_file);
        }
    }

    Student(const Student &from)
    {
        this->first_name = from.first_name;
        this->last_name = from.last_name;
        this->patromymic = from.patromymic;
        this->group = from.group;
        this->birthday = from.birthday;
    }

    Student **GetHead()
    {
        return head;
    }

    int GetSizeOfStudent()
    {
        return size_of_student;
    }

    string GetFirstName()
    {
        return first_name;
    }

    string GetLastName()
    {
        return last_name;
    }

    string GetPatromymic()
    {
        return patromymic;
    }

    string GetGroup()
    {
        return group;
    }

    string GetBirthday()
    {
        return birthday;
    }

    void Print(string order)
    {
        for (int i = 0; i < this->size_of_student; i++)
        {
            cout << this->head[i]->first_name << " ";
            cout << this->head[i]->last_name << " ";
            cout << this->head[i]->patromymic << " ";
            cout << this->head[i]->group << " ";
            cout << this->head[i]->birthday << endl;
        }
    }

    void WriteToFile()
    {
        ofstream out("Base_of_date/Date.txt");
        if (out.is_open())
        {
            out << this->size_of_student << endl;
            for (int i  = 0; i < this->size_of_student; i++)
            {
                out << this->head[i]->first_name << " ";
                out << this->head[i]->last_name << " ";
                out << this->head[i]->patromymic << " ";
                out << this->head[i]->group << " ";
                out << this->head[i]->birthday << endl;
            }
        }
        out.close();
    }

    void Append()
    {
        Student **new_head = new Student*[this->size_of_student + 1];
        for (int i = 0; i < this->size_of_student; i++)
        {
            new_head[i] = new Student(*this->head[i]);
        }

        delete [] this->head;
        this->head = new_head;
        this->size_of_student++;
        this->head[this->size_of_student - 1] = new Student(false);
    }

    void SwapStudent(Student *first, Student *second)
    {
        Student temp = *first;
        *first = *second;
        *second = temp;
    }


    void QuickSort(int first, int last, string parameter)
    {
        if (first < last)
        {
            int left = first, right = last, index = (left + right) / 2;
            string middle;

            if (parameter == "first_name last_name patromymic")
                middle = head[index]->first_name + " " + head[index]->last_name + " " + head[index]->patromymic;

            if (parameter == "group")
                middle = head[index]->group;

            if (parameter == "birthday")
                middle = head[index]->birthday;
            do
            {
                if (parameter == "first_name last_name patromymic")
                {
                    while ((head[left]->first_name + " " + head[left]->last_name + " " + head[left]->patromymic) < middle) left++;
                    while ((head[right]->first_name + " " + head[right]->last_name + " " + head[right]->patromymic) > middle) right--;
                }

                if (parameter == "group")
                {
                    while (this->head[left]->group < middle) left++;
                    while (this->head[right]->group > middle) right--;
                }

                if (parameter == "birthday")
                {
                    while (this->head[left]->birthday < middle) left++;
                    while (this->head[right]->birthday > middle) right--;
                }
                if (left <= right)
                {
                    SwapStudent(this->head[left], this->head[right]);
                    left++;
                    right--;
                }
            } while (left <= right);
            QuickSort(first, right, parameter);
            QuickSort(left, last, parameter);
        }
    }

    void Sort()
    {
        QuickSort(0, size_of_student - 1, "first_name last_name patromymic");
    }

    bool BinarySearch()
    {
        string refirst_name, relast_name, repatromymic, regroup, rebirthday;

        cout << "Введите данные студента." << endl;
        cout << "Фамилия: ";
        cin >> refirst_name;
        cout << "Имя: ";
        cin >> relast_name;
        cout << "Отчество: ";
        cin >> repatromymic;
        cout << "Номер группы: ";
        cin >> regroup;
        cout << "Дата рождения: ";
        cin >> rebirthday;

        QuickSort(0, size_of_student - 1, "first_name last_name patromymic");

        string requset = refirst_name + " " + relast_name + " " + repatromymic + " " + regroup + " " + rebirthday;
        int left = 0, right = size_of_student - 1;
        bool result = false;

        while (left <= right)
        {
            int middle = (left + right) / 2;
            string example = head[middle]->first_name + " " + head[middle]->last_name + " " + head[middle]->patromymic + " " + head[middle]->group + " " + head[middle]->birthday;
            if (requset == example)
            {
                result = true;
                break;
            }

            if (requset < example)
                right = middle - 1;
                else
                    left = middle + 1;
        }

        return result;
    }

    bool GoldenSectionSearch()
    {
        string refirst_name, relast_name, repatromymic, regroup, rebirthday;

        cout << "Введите данные студента." << endl;
        cout << "Фамилия: ";
        cin >> refirst_name;
        cout << "Имя: ";
        cin >> relast_name;
        cout << "Отчество: ";
        cin >> repatromymic;
        cout << "Номер группы: ";
        cin >> regroup;
        cout << "Дата рождения: ";
        cin >> rebirthday;

        QuickSort(0, size_of_student - 1, "first_name last_name patromymic");

        string requset = refirst_name + " " + relast_name + " " + repatromymic + " " + regroup + " " + rebirthday;
        int left = 0, right = size_of_student - 1;
        bool result = false;

        while (left <= right)
        {
            int golden_section = (0.382 * right) + (0.618 * left);
            string example = head[golden_section]->first_name + " " + head[golden_section]->last_name + " " + head[golden_section]->patromymic + " " + head[golden_section]->group + " " + head[golden_section]->birthday;
            if (requset == example)
            {
                result = true;
                break;
            }

            if (requset < example)
                right = golden_section - 1;
                else
                    left = golden_section + 1;
        }

        return result;
    }

    bool ProportionSearch()
    {
        string refirst_name, relast_name, repatromymic, regroup, rebirthday;

        cout << "Введите данные студента." << endl;
        cout << "Фамилия: ";
        cin >> refirst_name;
        cout << "Имя: ";
        cin >> relast_name;
        cout << "Отчество: ";
        cin >> repatromymic;
        cout << "Номер группы: ";
        cin >> regroup;
        cout << "Дата рождения: ";
        cin >> rebirthday;

        int a, b;
        cout << "Введите два натуральных числа:" << endl;
        cin >> a >> b;

        QuickSort(0, size_of_student - 1, "first_name last_name patromymic");

        string requset = refirst_name + " " + relast_name + " " + repatromymic + " " + regroup + " " + rebirthday;
        int left = 0, right = size_of_student - 1;
        bool result = false;

        while (left <= right)
        {
            int i = ((a * right) + (b * left))/(a + b);
            string example = head[i]->first_name + " " + head[i]->last_name + " " + head[i]->patromymic + " " + head[i]->group + " " + head[i]->birthday;
            if (requset == example)
            {
                result = true;
                break;
            }

            if (requset < example)
                right = i - 1;
                else
                    left = i + 1;
        }

        return result;
    }
};


template <class T>
struct Node
{
    int index;
    T *ptr;
};

template <class T>
class Graph
{
    int number_of_points, **matrix;
    Node<T> *head;
public:
    Graph(int inp_number_of_points)
    {
        this->number_of_points = inp_number_of_points;
        matrix = new int* [this->number_of_points];
        head = new Node<T> [this->number_of_points];

        for (int i = 0; i < this->number_of_points; i++)
        {
            head[i].ptr = nullptr;
            matrix[i] = new int[this->number_of_points];
            for (int j = 0; j < this->number_of_points; j++)
                matrix[i][j] = 0;
        }

        for (int i = 0; i < this->number_of_points; i++)
        {
            cout << "========== Введите значение вершины " << i << " ==========" << endl;
            if (head[i].ptr == nullptr)
            {
                head[i].ptr = new T;
                head[i].index = i;
            }
            cout << "Введите количество смежных вершин для вершины " << i << endl;
            int size_of_neigh;
            cin >> size_of_neigh;
            for (int j = 0; j < size_of_neigh; j++)
            {
                cout << "Введите номер смежной вершины для вершины " << i << endl;
                int neigh;
                cin >> neigh;
                if (head[neigh].ptr == nullptr)
                {
                    cout << "Введите значение вершины " << neigh << endl;
                    head[neigh].ptr = new T;
                    head[neigh].index = neigh;
                }
                cout << "Введите длину ребра между вершинами " << neigh << " и " << i << endl;
                int length;
                cin >> length;
                matrix[i][neigh] = length;
            }
        }
    }

    void Print()
    {
        for (int i = 0; i < this->number_of_points; i++)
        {
            for (int j = 0; j < this->number_of_points; j++)
            {
                cout << this->matrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    void FastWay()
    {
        int SIZE = 5, minindex, min;
        int d[SIZE], v[SIZE];
        for (int i = 0; i<SIZE; i++)
        {
            d[i] = 10000;
            v[i] = 1;
        }
          d[0] = 0;
          do {
            minindex = 10000;
            min = 10000;
            for (int i = 0; i<SIZE; i++)
            {
                if ((v[i] == 1) && (d[i]<min))
                {
                    min = d[i];
                    minindex = i;
                }
            }

            if (minindex != 10000)
            {
                for (int i = 0; i<SIZE; i++)
                {
                    if (this->matrix[minindex][i] > 0)
                    {
                        int temp = min + this->matrix[minindex][i];
                        if (temp < d[i])
                        {
                            d[i] = temp;
                        }
                    }
                }
              v[minindex] = 0;
            }
          } while (minindex < 10000);

          printf("\nКратчайшие расстояния до вершин: \n");
          for (int i = 0; i<SIZE; i++)
            printf("%5d ", d[i]);
    }
};

int main()
{
    setlocale(0, "Russian");
    int size_of_nodes = 5;
    freopen("Base_of_date/Date.txt", "r", stdin);
    Graph<Student> graph(size_of_nodes);
    cout << "Таблица" << endl;
    graph.Print();
    graph.FastWay();
    freopen("CONIN$", "r", stdin);
    return 0;
}
