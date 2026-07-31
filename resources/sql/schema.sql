-- CONTROLE FINANCEIRO PESSOAL

CREATE TABLE contas (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nome TEXT NOT NULL,
	tipo TEXT NOT NULL,
	banco TEXT,
    saldo_inicial REAL NOT NULL DEFAULT 0,
    ativo INTEGER NOT NULL DEFAULT 1
);

CREATE TABLE categorias (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nome TEXT NOT NULL,
    grupo TEXT NOT NULL,
    tipo TEXT NOT NULL CHECK (tipo IN ('DESPESA', 'RENDA')),
    ativo INTEGER NOT NULL DEFAULT 1
);

-- Uma tabela: movimentacoes
-- tipo define o sentido do dinheiro
-- Valor sempre positivo
-- Categoria já sabe se é de renda, despesa ou transferência
-- No futuro, permitir ajustes pontuais sem mexer no saldo inicial adicionando TIPO_AJUSTE

CREATE TABLE movimentacoes (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    data DATE NOT NULL,
    valor REAL NOT NULL CHECK (valor > 0),
    descricao TEXT,

    tipo TEXT NOT NULL CHECK (
        tipo IN ('RENDA', 'DESPESA', 'TRANSFERENCIA')
    ),

    conta_origem_id INTEGER,
    conta_destino_id INTEGER,
    categoria_id INTEGER,

    FOREIGN KEY (conta_origem_id) REFERENCES contas(id),
    FOREIGN KEY (conta_destino_id) REFERENCES contas(id),
    FOREIGN KEY (categoria_id) REFERENCES categorias(id)
);

-- Um orçamento diferente por mês
-- Histórico de mudanças
-- Comparações tipo “orçado vs gasto”

CREATE TABLE orcamentos (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    categoria_id INTEGER NOT NULL,
    ano INTEGER NOT NULL,
    mes INTEGER NOT NULL CHECK (mes BETWEEN 1 AND 12),
    valor REAL NOT NULL CHECK (valor >= 0),
    observacoes TEXT,

    UNIQUE (categoria_id, ano, mes),
    FOREIGN KEY (categoria_id) REFERENCES categorias(id)
    );

CREATE TABLE previsoes_renda (
    id INTEGER PRIMARY KEY,
    categoria_id INTEGER NOT NULL,
    ano INTEGER NOT NULL,
    mes INTEGER NOT NULL,
    valor_previsto REAL NOT NULL,

    tipo TEXT NOT NULL CHECK (tipo IN (
        'FIXA',
        'VARIAVEL',
        'EVENTUAL'
    )),

    observacoes TEXT,

    UNIQUE (categoria_id, ano, mes),
    FOREIGN KEY (categoria_id) REFERENCES categorias(id)
);

CREATE TABLE tags (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nome TEXT NOT NULL UNIQUE,
    cor TEXT,
    ativo INTEGER NOT NULL DEFAULT 1
);

CREATE TABLE movimentacao_tag
(
    movimentacao_id INTEGER NOT NULL,
    tag_id INTEGER NOT NULL,

    PRIMARY KEY (movimentacao_id, tag_id),

    FOREIGN KEY (movimentacao_id)
        REFERENCES movimentacoes(id),

    FOREIGN KEY (tag_id)
        REFERENCES tags(id)
);

CREATE INDEX idx_mov_data ON movimentacoes(data);
CREATE INDEX idx_mov_tipo ON movimentacoes(tipo);
CREATE INDEX idx_mov_conta_origem ON movimentacoes(conta_origem_id);
CREATE INDEX idx_mov_conta_destino ON movimentacoes(conta_destino_id);
CREATE INDEX idx_orcamentos_periodo ON orcamentos(ano, mes);
CREATE INDEX idx_renda_prevista_periodo ON previsoes_renda(ano, mes);

-- INVESTIMENTOS 

CREATE TABLE ativos (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nome TEXT NOT NULL,
    tipo TEXT NOT NULL CHECK (
        tipo IN (
          'MOEDA',
          'ACAO',
          'ETF',
          'FII',
          'TITULO_PUBLICO',
          'POUPANCA',
          'FUNDO'
        )
    ),
    moeda TEXT NOT NULL, -- BRL, USD, etc
    ativo INTEGER NOT NULL DEFAULT 1,
    observacoes TEXT
);

CREATE TABLE operacoes_investimento (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    ativo_id INTEGER NOT NULL,
    data DATE NOT NULL,
    tipo TEXT NOT NULL CHECK (
        tipo IN (
          'APORTE',
          'RESGATE',
          'PROVENTO',
          'JUROS',
          'TAXA',
          'AJUSTE'
        )
    ),
    quantidade REAL NOT NULL,
    valor_unitario REAL NOT NULL,
    conta_id INTEGER, -- opcional
    observacoes TEXT,

    FOREIGN KEY (ativo_id) REFERENCES ativos(id),
    FOREIGN KEY (conta_id) REFERENCES contas(id)
);

-- Valorização não é evento, é estado ao longo do tempo.
-- cotacoes vai registrar a valorização ou desvalorização nas datas
CREATE TABLE cotacoes_ativos (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    ativo_id INTEGER NOT NULL,
    data DATE NOT NULL,
    preco REAL NOT NULL,

    UNIQUE (ativo_id, data),
    FOREIGN KEY (ativo_id) REFERENCES ativos(id)
);

CREATE TABLE cambio (
  data DATE NOT NULL,
  moeda_origem TEXT NOT NULL,
  moeda_destino TEXT NOT NULL,
  taxa REAL NOT NULL,

  PRIMARY KEY (data, moeda_origem, moeda_destino)
);
