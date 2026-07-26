# Contributting

Alguns padrões que estão sendo utilizados no projeto.

## Nomes de widgets ui no QT

| Widget           | Prefixo |
| ---------------- | ------- |
| QLabel           | lbl     |
| QLineEdit        | edt     |
| QTextEdit        | txt     |
| QPushButton      | btn     |
| QDialogButtonBox | bb      |
| QCheckBox        | chk     |
| QComboBox        | cmb     |
| QTableView       | tbl     |
| QTreeView        | tree    |
| QListView        | lst     |
| QDoubleSpinBox   | spn     |
| QDateEdit        | date    |
| QGroupBox        | grp     |
| QWidget          | wdg     |
| Layout           | lay     |

## Classes de Entidade

No singular (Conta, Categoria, Tag), pois trabalham com um único registro.

## Janelas são Widgets

Exceto a mainwindow, todas as janelas são chamadas Widgets, pois são módulos da interface, não necessariamente uma janela. Hoje elas podem ser exibidas em uma janela própria, amanhã dentro de um QTabWidget, QDockWidget ou QStackWidget, sem que a classe precise mudar de nome ou de responsabilidade.

## Diálogos de Edição

Formulários para adicionar uma nova entidade, editar ou excluir uma já existente.

No geral, todo formulário é nomeado no singular + ```Widget``` (```ContaWidget```).

Repositórios e Modelos também ficam no Singular.

## Tabelas de Visualização

No plural, pois tratam da visualização de várias entradas.

Nomeado no plural + ```Widget``` (```ContasWidget```).
