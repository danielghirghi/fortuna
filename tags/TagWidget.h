#ifndef TAGWIDGET_H
#define TAGWIDGET_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class TagWidget; }
QT_END_NAMESPACE

class TagWidget : public QDialog
{
    Q_OBJECT

public:
    explicit TagWidget(QWidget *parent = nullptr);
    ~TagWidget();
    void setId(int id);

private slots:
    void salvar();
    void inserirTag();
    void atualizarTag();

private:
    int m_id = -1;
    void carregarTag();
    Ui::TagWidget *ui;
};

#endif // TAGWIDGET_H
