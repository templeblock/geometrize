#include "searchbox.h"

#include <QCompleter>
#include <QStringListModel>

namespace geometrize
{

namespace dialog
{

class StringListModel : public QStringListModel
{
public:
    void setStringList(const QStringList& list)
    {
        QStringListModel::setStringList(list);
    }
};

class SearchBox::SearchBoxImpl
{
public:
    SearchBoxImpl(SearchBox* pQ) : q{pQ}
    {
        m_completer.setCompletionMode(QCompleter::PopupCompletion);
        m_completer.setCaseSensitivity(Qt::CaseInsensitive);
        m_completer.setFilterMode(Qt::MatchStartsWith);
        m_completer.setModel(&m_model);
        q->setCompleter(&m_completer);
    }

    void addToCompletionList(const QString& item)
    {
        m_model.insertRows(m_model.rowCount(), 1);
        m_model.setData(m_model.index(m_model.rowCount() - 1), item);
    }

    void setCompletionList(const QStringList& completionList)
    {
        m_model.setStringList(completionList);
    }

private:
    QCompleter m_completer;
    StringListModel m_model;
    SearchBox* q;
};

SearchBox::SearchBox(QWidget* parent) : QLineEdit(parent), d{std::make_unique<SearchBox::SearchBoxImpl>(this)}
{

}

void SearchBox::setCompletionList(const QStringList& completionList)
{
    d->setCompletionList(completionList);
}

void SearchBox::addToCompletionList(const QString& item)
{
    d->addToCompletionList(item);
}

}

}