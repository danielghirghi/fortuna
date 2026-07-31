-- Views do controle financeiro

-- Saldo atual por conta

CREATE VIEW vw_saldo_contas AS
SELECT
  c.id,
  c.nome,
  c.saldo_inicial
  + COALESCE(SUM(
      CASE
        -- RENDA entra na conta destino
        WHEN m.tipo = 'RENDA'
         AND m.conta_destino_id = c.id
          THEN m.valor

        -- DESPESA sai da conta origem
        WHEN m.tipo = 'DESPESA'
         AND m.conta_origem_id = c.id
          THEN -m.valor

        -- TRANSFERÊNCIA entra na conta destino
        WHEN m.tipo = 'TRANSFERENCIA'
         AND m.conta_destino_id = c.id
          THEN m.valor

        -- TRANSFERÊNCIA sai da conta origem
        WHEN m.tipo = 'TRANSFERENCIA'
         AND m.conta_origem_id = c.id
          THEN -m.valor

        ELSE 0
      END
    ), 0) AS saldo_atual
FROM contas c
LEFT JOIN movimentacoes m
  ON m.conta_origem_id = c.id
  OR m.conta_destino_id = c.id
GROUP BY c.id, c.nome, c.saldo_inicial;

-- Despesa por categoria (mês)

CREATE VIEW vw_despesas_por_categoria_mes AS
SELECT
  strftime('%Y', m.data) AS ano,
  strftime('%m', m.data) AS mes,
  c.grupo,
  c.nome AS categoria,
  SUM(m.valor) AS total
FROM movimentacoes m
JOIN categorias c ON c.id = m.categoria_id
WHERE m.tipo = 'DESPESA'
GROUP BY
  ano,
  mes,
  c.grupo,
  c.nome;

-- Rendas por categoria (mês)

CREATE VIEW vw_rendas_por_categoria_mes AS
SELECT
  strftime('%Y', m.data) AS ano,
  strftime('%m', m.data) AS mes,
  c.nome AS categoria,
  SUM(m.valor) AS total
FROM movimentacoes m
JOIN categorias c ON c.id = m.categoria_id
WHERE m.tipo = 'RENDA'
GROUP BY
  ano,
  mes,
  c.nome;

-- Orçamento vs gasto (mês)

CREATE VIEW vw_orcamento_vs_realizado AS
SELECT
  o.ano,
  printf('%02d', o.mes) AS mes,
  c.grupo,
  c.nome AS categoria,
  o.valor AS orcado,
  COALESCE(SUM(m.valor), 0) AS realizado,
  o.valor - COALESCE(SUM(m.valor), 0) AS saldo
FROM orcamentos o
JOIN categorias c ON c.id = o.categoria_id
LEFT JOIN movimentacoes m
  ON m.categoria_id = o.categoria_id
 AND m.tipo = 'DESPESA'
 AND strftime('%Y', m.data) = CAST(o.ano AS TEXT)
 AND strftime('%m', m.data) = printf('%02d', o.mes)
GROUP BY
  o.ano,
  o.mes,
  c.grupo,
  c.nome,
  o.valor;

-- Renda prevista vs realizada

CREATE VIEW vw_previsao_renda_vs_realizado AS
SELECT
  p.ano,
  printf('%02d', p.mes) AS mes,
  c.nome AS categoria,
  p.tipo,
  p.valor_previsto,
  COALESCE(SUM(m.valor), 0) AS realizado,
  COALESCE(SUM(m.valor), 0) - p.valor_previsto AS diferenca
FROM previsoes_renda p
JOIN categorias c ON c.id = p.categoria_id
LEFT JOIN movimentacoes m
  ON m.categoria_id = p.categoria_id
 AND m.tipo = 'RENDA'
 AND strftime('%Y', m.data) = CAST(p.ano AS TEXT)
 AND strftime('%m', m.data) = printf('%02d', p.mes)
GROUP BY
  p.ano, p.mes, c.nome, p.tipo, p.valor_previsto;

-- Views de Investimentos

-- Posição atual por ativo

CREATE VIEW vw_posicao_ativos AS
SELECT
  a.id AS ativo_id,
  a.nome,
  a.moeda,
  SUM(
    CASE
      WHEN o.tipo IN ('APORTE', 'PROVENTO', 'AJUSTE') THEN o.quantidade
      WHEN o.tipo = 'RESGATE' THEN -o.quantidade
    END
  ) AS quantidade
FROM ativos a
JOIN operacoes_investimento o ON o.ativo_id = a.id
GROUP BY a.id, a.nome, a.moeda;

-- Valor atual do investimento

CREATE VIEW vw_valor_atual_ativos AS
SELECT
  p.ativo_id,
  p.nome,
  p.moeda,
  p.quantidade,
  c.preco AS preco_unitario,
  p.quantidade * c.preco AS valor_total
FROM vw_posicao_ativos p
JOIN cotacoes_ativos c
  ON c.ativo_id = p.ativo_id
 AND c.data = (
   SELECT MAX(data)
   FROM cotacoes_ativos
   WHERE ativo_id = p.ativo_id
 );

 -- Proventos por ativo

 CREATE VIEW vw_proventos_por_ativo AS
SELECT
  a.nome AS ativo,
  o.data,
  o.quantidade * o.valor_unitario AS valor,
  a.moeda
FROM operacoes_investimento o
JOIN ativos a ON a.id = o.ativo_id
WHERE o.tipo = 'PROVENTO';

-- Patrimonio total convertido para BRL

CREATE VIEW vw_patrimonio_total_brl AS
SELECT
  v.ativo_id,
  v.nome,
  v.moeda,
  v.valor_total,
  CASE
    WHEN v.moeda = 'BRL' THEN v.valor_total
    ELSE v.valor_total * c.taxa
  END AS valor_em_brl
FROM vw_valor_atual_ativos v
LEFT JOIN cambio c
  ON c.moeda_origem = v.moeda
 AND c.moeda_destino = 'BRL'
 AND c.data = (
   SELECT MAX(data)
   FROM cambio
   WHERE moeda_origem = v.moeda
     AND moeda_destino = 'BRL'
 );