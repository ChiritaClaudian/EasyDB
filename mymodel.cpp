#include "mymodel.h"


MyModel::MyModel()
{

}

QVariant MyModel::data(const QModelIndex &item, int role) const{
    int row = item.row();
    int col = item.column();
    if(role == Qt::DisplayRole){
        return "
    }
}
