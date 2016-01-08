#ifndef NOFOCUSDELEGATE
#define NOFOCUSDELEGATE
#include<QStyledItemDelegate>
class QTableWidget;
class NoFocusDelegate:public QStyledItemDelegate{
   Q_OBJECT
public:
    NoFocusDelegate(QTableWidget*){}
    void paint(QPainter* painter, const QStyleOptionViewItem & option, const QModelIndex &index)const;
};
#endif // NOFOCUSDELEGATE



