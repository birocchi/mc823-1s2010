CREATE TABLE filme (
  id INTEGER PRIMARY KEY,
  n_avaliacoes INTEGER,
  nota REAL,
  titulo TEXT,
  sinopse TEXT
);

CREATE TABLE sala (
  id INTEGER PRIMARY KEY,
  nome TEXT
);

CREATE TABLE horario (
  idfilme INTEGER,
  idsala INTEGER,
  horario TEXT
);
