SELECT name FROM people WHERE id IN (SELECT DISTINCT person_id FROM directors WHERE movie_id IN (SELECT movie_ID from ratings WHERE rating >= 9.0));