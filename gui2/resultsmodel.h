#ifndef RESULTSMODEL_H
#define RESULTSMODEL_H

#include <QAbstractItemModel>
#include <QList>
#include <QString>

class ResultsModel : public QAbstractItemModel {
    Q_OBJECT
public:
    explicit ResultsModel(QObject *parent = 0);

    class Node {
    public:
        Node() {
            parent = 0;
        }

        Node(QString filename, QString line, QString severity, QString text) {
            this->filename = filename;
            this->line     = line;
            this->severity = severity;
            this->text     = text;
            parent = 0;
        }

        ~Node() {
            qDeleteAll(children);
        }

        Node *parent;
        QString filename;
        QString line;
        QString severity;
        QString text;
        QList<Node*> children;
    };

    void clear();
    void addresult(const QString &errmsg);

    bool save(const QString &fileName, const QString &projectName) const;

private:
    void setRootNode(Node *node);
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    static bool parseErrorMessage(const QString &errmsg, QString *file, QString *line, QString *severity, QString *text);
    Node *nodeFromIndex(const QModelIndex &index) const;
    Node *rootNode;
};
#endif // RESULTSMODEL_H
