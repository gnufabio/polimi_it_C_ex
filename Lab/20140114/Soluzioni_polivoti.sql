/* Stampo tutte le tre tabelle */
select * from studente;
select * from esame;
select * from corso;

set sql_mode = ONLY_FULL_GROUP_BY;

/* Estrarre la matricola e il nome, degli studenti che hanno preso 30 almeno una volta */
select distinct s.matr, s.nome 
from studente as s join esame as e on s.matr = e.matr
where e.voto >= 30;

/* Calcolare la media dello studente "Saverio Serio" */
select avg(e.voto) as Media
from esame as e
where e.matr in (select s.matr
	from studente as s
	where s.nome = 'Saverio Serio');

/* Estrarre la media di ogni studente che abbia sostenuto almeno tre esami */
select s.matr, s.nome, avg(e.voto)
from studente as s join esame as e on e.matr = s.matr
group by s.matr, s.nome
having count(*) >= 3;

/* Estrarre, per ogni studente, la media relativa ad ogni anno di corso
   (esami del 1°, 2°, o 3° anno) per cui abbia sostenuto qualche esame */
select s.matr, s.nome, c.anno, avg(e.voto)
from studente as s join (esame as e join corso as c on e.codcorso = c.codcorso) on s.matr = e.matr
group by s.matr, s.nome, c.anno
having count(*) > 0;

/* Estrarre il nome del corso che vale il minor numero di crediti */
select titolo, cfu
from corso
where cfu in (select min(cfu) from corso);

/* Estrarre il nome del corso che vale il minor numero di crediti di ogni anno */
select titolo, anno, cfu
from corso
where (anno, cfu) in (select anno, min(cfu) from corso group by anno)
order by anno;

/* Estrarre la matricola degli studenti che hanno sempre preso LO STESSO voto */
select distinct e.matr
from esame as e
where e.voto = all (select e1.voto from esame as e1 where e.matr = e1.matr);

/* Estrarre la matricola degli studenti che hanno sempre preso LO STESSO voto,
   **più di una volta** */
select distinct e.matr
from esame as e
where e.voto = 
	all (select e1.voto from esame as e1 where e.matr = e1.matr)
	and	(select count(*) from esame as e1 where e1.matr = e.matr) > 1;

/* Estrarre la matricola dello studente con la media più bassa */
select e.matr as Matricola, avg(e.voto) as Media
from esame as e
group by e.matr
having avg(e.voto) <= all 
	(select avg(e1.voto) from esame as e1 group by e1.matr);

/* Estrarre la matricola degli studenti che non hanno mai preso 19 */
select e.matr
from esame as e
where e.voto <> 19
group by e.matr
having count(*) = 
	(select count(*) from esame as e1 where e1.matr = e.matr);
	/* oppure */
select distinct e.matr
from esame as e
where e.matr not in (select distinct e1.matr from esame as e1 where e1.voto = 19);

/* Estrarre la matricola degli studenti che hanno preso TUTTI i voti 
   almeno una volta */
drop view if exists n_voti;
create view n_voti as (select e.matr, e.voto, s.nome 
	from esame as e join studente as s on s.matr = e.matr 
	group by e.matr, s.nome, e.voto 
	having count(*) = 1);

select matr, nome from n_voti
group by matr, nome
having count(*) >= 13;

/* Estrarre il nome e la matricola degli studenti che non hanno 
   mai preso meno di 30 */
select distinct e1.matr from esame as e1
where not exists 
	(select e2.matr 
		from esame as e2 
		where e2.matr = e1.matr and e2.voto < 30);

/* Studenti che non hanno mai preso due volte lo stesso voto (voti tutti diversi) */
select distinct e1.matr from esame as e1
where not exists (select voto from esame
where matr = e1.matr
group by voto
having count(*) > 1);