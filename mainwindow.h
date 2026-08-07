#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "contas/ContasWidget.h"
#include "categorias/CategoriasWidget.h"
#include "tags/TagsWidget.h"
#include "movimentacoes/MovimentacoesWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
	class MainWindow;
}
QT_END_NAMESPACE

class MainWindow: public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();
	
private slots:
	void on_btnContas_clicked();
    void on_btnCategorias_clicked();
    void on_btnTags_clicked();
    void on_btnMovimentacoes_clicked();
    void on_actionAbrirArquivo_triggered();
    void atualizarInterface();
    void tabelaInfo();

private:
	Ui::MainWindow *ui;
    ContasWidget *m_contas {nullptr};
    CategoriasWidget *m_categorias {nullptr};
    TagsWidget *m_tags {nullptr};
    MovimentacoesWidget *m_movimentacoes {nullptr};
    template<class T>
    void abrirJanela(T *&janela)
    {
        if (!janela)
        {
            janela = new T(nullptr);
            connect(janela, &QObject::destroyed,
                    this, [&janela]() { janela = nullptr; });
        }
        janela->show();
        janela->raise();
        janela->activateWindow();
        tabelaInfo();
    };
};
#endif // MAINWINDOW_H
