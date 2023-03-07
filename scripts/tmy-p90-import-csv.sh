#!/bin/bash

#? Import meteo data from csv to postgresql database

psql -U dev -d pv -c "COPY pv.tmy_p90_meteodata
FROM '/home/dev/pv-yield/data/Solargis-TMY60-SOLARGIS-PlataformaSolardeAlmeria-Spain-v2-P90.csv' 
DELIMITER ';' 
CSV HEADER;"
