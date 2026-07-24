#ifndef MOVIMENTACOESWINDOW_H
#define MOVIMENTACOESWINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MovimentacoesWindow; }
QT_END_NAMESPACE

class MovimentacoesWindow : public QWidget {
    Q_OBJECT

public:
    explicit MovimentacoesWindow(QWidget *parent = nullptr);
    ~MovimentacoesWindow();

private slots:
    void abrirReceita();
    void abrirDespesa();
    void abrirTransferencia();

private:
    Ui::MovimentacoesWindow *ui;
};

#endif // MOVIMENTACOESWINDOW_H
