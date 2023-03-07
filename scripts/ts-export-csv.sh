#!/bin/bash

#? Export data from Time Series table

psql -U dev -d pv -c "COPY (select * from pv.ts_meteodata where date < '01.01.2000') TO '/home/dev/pv-yield/data/output/ts_NN.csv'  WITH DELIMITER ';' CSV HEADER;"
