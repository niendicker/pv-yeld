#!/bin/bash

#? Import meteo data from csv to postgresql database

psql -U dev -d pv -c "COPY pv.ts_meteodata
FROM '/home/dev/pv-yield/data/Solargis-TS-hourly-SOLARGIS-PlataformaSolardeAlmeria-Spain-v2-19940101-20161231.csv' 
DELIMITER ';' 
CSV HEADER;"
