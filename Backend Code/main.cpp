#include <iostream>
#include <QVector>
#include "db.h"
#include "summary.h"

using namespace std;

int main()
{
    DB* db = new DB();
    db->createDatabase();

    Summary* sum = new Summary();
    QVector<Year> vector;
    vector.append(sum->summaryFill("Postgraduate Medical Education", 1999, 1999));
    cout<<vector[0].date<<endl;
    cout<<vector[0].tothours<<endl;
    cout<<vector[0].totstudents<<endl;
    for(int i=0; i<vector[0].list.size(); i++){
        cout<<vector[0].list[i].faculty.toStdString()<<endl;
        cout<<vector[0].list[i].hours<<endl;
        cout<<vector[0].list[i].students<<endl;
    }
}
