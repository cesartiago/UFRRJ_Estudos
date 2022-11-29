-- LINK: http://sqlfiddle.com/#!9/19a087
CREATE SCHEMA Exemplo1; -- PQ Ñ PODE TER ISSO AQUI NO SQL Fiddle? Pq smp cria um novo né? DATA BASE E SCHEMA SÃO "SINÔNIMOS" nesse sentido? (SEI Q SCHEMA É O LÓGICO)
Use Exemplo1; #Tem que ter isso no MySQL, como o a cima tb.

CREATE TABLE EMPREGADO (
  PNOME VARCHAR(20) NOT NULL,
  MINICIAL VARCHAR(1) NOT NULL,
  UNOME VARCHAR(20),
  SSN INTEGER (9) NOT NULL PRIMARY KEY,
  DATANASC DATE NOT NULL,
  ENDERECO VARCHAR (30) NOT NULL, 
  SEXO ENUM ('M', 'F') NOT NULL,
  SALARIO INTEGER (5) NOT NULL,
  SUPERSSN INTEGER (9),
  DNO INTEGER (1) NOT NULL,
  FOREIGN KEY (SUPERSSN) REFERENCES EMPREGADO (SSN)
  );                                                /*Tem q falar o nome da tabela "empregado" msm dentro dele, na foreign key*/
  
CREATE TABLE DEPARTAMENTO (DNOME VARCHAR(20) NOT NULL, DNUMERO INTEGER (1)  PRIMARY KEY NOT NULL, GERSSN INTEGER (9) NOT NULL,
                             GERDATAINICIO DATE NOT NULL);
  
CREATE TABLE DEPT_LOCALIZACOES (DNUMERO INTEGER (1), DLOCALIZACAO VARCHAR (20) NOT NULL, 
                                FOREIGN KEY (DNUMERO) REFERENCES DEPARTAMENTO (DNUMERO)); #**Referenciar algo já existente.
  

  
CREATE TABLE PROJETO (PJNOME VARCHAR(20) NOT NULL, PNUMERO INTEGER (2) NOT NULL PRIMARY KEY, PLOCALIZACAO VARCHAR (20) NOT NULL, DNUM INTEGER (1) NOT NULL);

CREATE TABLE TRABALHA_EM (ESSN INTEGER (9) NOT NULL, PNO INTEGER (2) NOT NULL, HORAS DECIMAL (3,1), FOREIGN KEY (ESSN)
                          REFERENCES EMPREGADO (SSN), FOREIGN KEY (PNO) REFERENCES PROJETO (PNUMERO)); #**Tem que referenciar chave já setada como primária na outra tabela.
  
CREATE TABLE DEPENDENTE (ESSN INTEGER (9) NOT NULL, NOME_DEPENDENTE VARCHAR(20) NOT NULL PRIMARY KEY, SEXO ENUM ('M', 'F') NOT NULL, DATANASC DATE NOT NULL, 
                         PARENTESCO VARCHAR (20) NOT NULL, FOREIGN KEY (ESSN) REFERENCES EMPREGADO (SSN)); -- por entre parêntes a chave (ESSN) se não ñ vai
                         
                         -- INSERÇÃO DE DADOS NA TABELA --
INSERT INTO DEPARTAMENTO
(DNOME, DNUMERO, GERSSN, GERDATAINICIO)
VALUES
('Pesquisa', '5', '333445555', '1988-05-22'),
('Administração', '4', '987654321', '1995-01-01'),
('Sede administrativa', '1', '888665555', '1981-06-19');

INSERT INTO DEPT_LOCALIZACOES
(DNUMERO, DLOCALIZACAO)
VALUES
('1', 'Houston'),
('4', 'Stafford'),
('5', 'Bellaire'),
('5', 'Sugariand');

INSERT INTO DEPT_LOCALIZACOES
(DLOCALIZACAO)
VALUES
('Houston');

INSERT INTO PROJETO
(PJNOME , PNUMERO,  PLOCALIZACAO, DNUM)
VALUES
('ProdutoX', '1', 'Bellaire', '5'),
('ProdutoY', '2', 'Sugarland', '5'),
('ProdutoZ', '3', 'Houston', '5'),
('Automatização', '10', 'Stafford', '4'),
('Reorganização', '20', 'Houston', '1'),
('Novos Benefícios', '30', 'Stafford', '4');

INSERT INTO EMPREGADO
(PNOME, MINICIAL, UNOME, SSN, DATANASC, ENDERECO, SEXO, SALARIO, DNO)
VALUES
('James', 'E', 'Borg', '888665555', '1937-11-10', '450 Stone, Houston, TX', 'M', '55000', '1');
-- Primeiro inseri qm ñ tinha autorelacionamento

-- Dps inseri na ordem q o autorel. ocorria. Acredito q a ordem da tabela não importa (Alg. Rel.) ---
INSERT INTO EMPREGADO
(PNOME, MINICIAL, UNOME, SSN, DATANASC, ENDERECO, SEXO, SALARIO, SUPERSSN, DNO)
VALUES
('Franklin', 'T', 'Wong', '333445555', '1955-12-08', '638 Voss, Houston, TX', 'M', '40000', '888665555', '5'),
('John', 'B', 'Smith', '123456789', '1965-01-09', '731 Fondren, Houston, TX', 'M', '30000', '333445555', '5'),
('Ramesh', 'K', 'Narayan', '666884444', '1962-09-15', '975 Fire Oak, Humble, TX', 'M', '38000', '333445555', '5'),
('Joyce', 'A', 'English', '453453453', '1972-07-31', '5631 Rice, Houston, TX', 'F', '25000', '333445555', '5'),
('Jennifer', 'S', 'Wallace', '987654321', '1941-06-20', '291 Berry, Bellaire, TX', 'F', '43000', '888665555', '4'),
('Alicia', 'J', 'Zelaya', '999887777', '1968-01-19', '3321 Castle, Spring, TX', 'F', '25000', '987654321', '4'),
('Ahmad', 'V', 'Jabbar', '987987987', '1969-03-29', '980 Dallas, Houston, TX', 'M', '25000', '987654321', '4');

-- !!! PERGUNTAR A DIFERENÇA ENTRE OS 2 TIPOS DE INDÍCE PEDIDOS, JÁ QUE CADA FACULDADE FALA UMA COISA.
-- INDICE EM BD  É NO SENTIDO DE QUADRO/TABELA/INDEX. Difere do índice matemático.
-- Índices Primário (Ver def. com prof. Parece que lê na ordem que a tabela foi armazenada no HD...
-- ...e q caso tem-se uma chave primária, estará relacionado a ela, mas se não tem, não estará {pode ou não seguir a chave primária}:

CREATE INDEX IDX ON EMPREGADO (SSN); #Tabela(Coluna chave-primária) - Fará um Índice/TABELA/QUADRO/INDEX pela coluna.

-- Índices secundários:
CREATE INDEX IDX_2 ON EMPREGADO (PNOME); #Tabela(Coluna) - Índice na coluna
CREATE INDEX IDX_3 ON EMPREGADO (PNOME, MINICIAL, UNOME); #Tabela(Coluna) - Índice na coluna


-- Inseri o autorelacionamento organizando o insert acima --
-- !!! PERGUNTAR SE A ORDEM IMPORTA. ACHO Q EM ALGEBRA RELACIONAL, NÃO IMPORTAVA. E AQUI TB NÃO. Ñ CONSIGUI FAZER... --
-- ...DEIXANDO PRA PREENCHER DPS O AUTOREALCIONAMENTO. PQ NO DPS, O INSERT NÃO IA EM TODOS. E UPDATE, SERIA COM VÁRIOS WHERES -- 

-- !!! PERGUNTAR se pelo valor índice do ÍNDICE/QUADRO eu tenho acesso ao bloco todo (incluindo dados de cado coluna da...
-- ...tupla) ou não

-- !!! PERGUNTAR quais índices jão são normais q o SGBD crie. Tipo, ele realmente lê tds as tabelas...
-- ...sequencialmente, ou sua coluna até achar a tabela q vc quer? 

-- !!! PERGUNTAR se há índices ordenados vs não ordenados e em que sentido. Só no de cluster?
-- ...pq a ordem ñ importa, mas existe uma no HD. Algum índice fala sobre isso, dividir em blocos em ordens VS blocos fora da ordem.

#o NULL, não tá indo no primeiro insert.

-- DML:
#SELECT PNOME FROM EMPREGADO ORDER BY PNOME ASC; = JAMES

-- LINK: http://sqlfiddle.com/#!9/19a087
                      
                       
                         
                         