-- RENDA Inválida
CREATE TRIGGER trg_renda_valida
BEFORE INSERT ON movimentacoes
WHEN NEW.tipo = 'RENDA'
BEGIN
  SELECT
    CASE
      WHEN NEW.conta_destino_id IS NULL
        THEN RAISE(ABORT, 'RENDA exige banco_destino')
      WHEN NEW.conta_origem_id IS NOT NULL
        THEN RAISE(ABORT, 'RENDA não pode ter banco_origem')
      WHEN NEW.categoria_id IS NULL
        THEN RAISE(ABORT, 'RENDA exige categoria')
    END;
END;

-- DESPESA Inválida
CREATE TRIGGER trg_despesa_valida
BEFORE INSERT ON movimentacoes
WHEN NEW.tipo = 'DESPESA'
BEGIN
  SELECT
    CASE
      WHEN NEW.conta_origem_id IS NULL
        THEN RAISE(ABORT, 'DESPESA exige banco_origem')
      WHEN NEW.conta_destino_id IS NOT NULL
        THEN RAISE(ABORT, 'DESPESA não pode ter banco_destino')
      WHEN NEW.categoria_id IS NULL
        THEN RAISE(ABORT, 'DESPESA exige categoria')
    END;
END;

-- TRANSFERENCIA Inválida
CREATE TRIGGER trg_transferencia_valida
BEFORE INSERT ON movimentacoes
WHEN NEW.tipo = 'TRANSFERENCIA'
BEGIN
  SELECT
    CASE
      WHEN NEW.conta_origem_id IS NULL
        OR NEW.conta_destino_id IS NULL
        THEN RAISE(ABORT, 'TRANSFERENCIA exige origem e destino')
      WHEN NEW.conta_origem_id = NEW.conta_destino_id
        THEN RAISE(ABORT, 'TRANSFERENCIA não pode ser para a mesma conta')
      WHEN NEW.categoria_id IS NOT NULL
        THEN RAISE(ABORT, 'TRANSFERENCIA não pode ter categoria')
    END;
END;

-- Categoria compatível com tipo
CREATE TRIGGER trg_categoria_tipo_compativel
BEFORE INSERT ON movimentacoes
WHEN NEW.categoria_id IS NOT NULL
BEGIN
  SELECT
    CASE
      WHEN (
        SELECT tipo FROM categorias WHERE id = NEW.categoria_id
      ) <> NEW.tipo
        THEN RAISE(ABORT, 'Categoria incompatível com tipo da movimentação')
    END;
END;

-- Orçamento não existe para transferencia

CREATE TRIGGER trg_validar_orcamento_categoria
BEFORE INSERT ON orcamentos
BEGIN
  SELECT
    CASE
      WHEN (
        SELECT tipo
        FROM categorias
        WHERE id = NEW.categoria_id
      ) NOT IN ('DESPESA', 'RENDA')
      THEN RAISE(ABORT,
        'Orcamento so pode ser criado para categorias de DESPESA ou RENDA'
      )
    END;
END;

-- Validar Movimentação
CREATE TRIGGER trg_validar_movimentacao
BEFORE INSERT ON movimentacoes
BEGIN
  -- RENDA
  SELECT
    CASE
      WHEN NEW.tipo = 'RENDA'
       AND (
         NEW.conta_destino_id IS NULL OR
         NEW.conta_origem_id IS NOT NULL OR
         NEW.categoria_id IS NULL
       )
      THEN RAISE(ABORT,
        'RENDA exige conta_destino_id e categoria_id, e nao pode ter conta_origem_id'
      )
    END;

  -- DESPESA
  SELECT
    CASE
      WHEN NEW.tipo = 'DESPESA'
       AND (
         NEW.conta_origem_id IS NULL OR
         NEW.conta_destino_id IS NOT NULL OR
         NEW.categoria_id IS NULL
       )
      THEN RAISE(ABORT,
        'DESPESA exige conta_origem_id e categoria_id, e nao pode ter conta_destino_id'
      )
    END;

  -- TRANSFERENCIA
  SELECT
    CASE
      WHEN NEW.tipo = 'TRANSFERENCIA'
       AND (
         NEW.conta_origem_id IS NULL OR
         NEW.conta_destino_id IS NULL OR
         NEW.categoria_id IS NOT NULL OR
         NEW.conta_origem_id = NEW.conta_destino_id
       )
      THEN RAISE(ABORT,
        'TRANSFERENCIA exige conta_origem_id e conta_destino_id diferentes e nao pode ter categoria'
      )
    END;
END;

-- Validar UPDATE de movimentacao
CREATE TRIGGER trg_validar_movimentacao_update
BEFORE UPDATE ON movimentacoes
BEGIN
  -- RENDA
  SELECT
    CASE
      WHEN NEW.tipo = 'RENDA'
       AND (
         NEW.conta_destino_id IS NULL OR
         NEW.conta_origem_id IS NOT NULL OR
         NEW.categoria_id IS NULL
       )
      THEN RAISE(ABORT,
        'UPDATE invalido: RENDA exige conta_destino_id e categoria_id'
      )
    END;

  -- DESPESA
  SELECT
    CASE
      WHEN NEW.tipo = 'DESPESA'
       AND (
         NEW.conta_origem_id IS NULL OR
         NEW.conta_destino_id IS NOT NULL OR
         NEW.categoria_id IS NULL
       )
      THEN RAISE(ABORT,
        'UPDATE invalido: DESPESA exige conta_origem_id e categoria_id'
      )
    END;

  -- TRANSFERENCIA
  SELECT
    CASE
      WHEN NEW.tipo = 'TRANSFERENCIA'
       AND (
         NEW.conta_origem_id IS NULL OR
         NEW.conta_destino_id IS NULL OR
         NEW.categoria_id IS NOT NULL OR
         NEW.conta_origem_id = NEW.conta_destino_id
       )
      THEN RAISE(ABORT,
        'UPDATE invalido: TRANSFERENCIA exige contas diferentes e sem categoria'
      )
    END;
END;