#! /bin/bash

psql -U dev -d pv -c 'CREATE TABLE pv.ts_meteodata (
    date date,
    "time" time without time zone,
    ghi real,
    dni real,
    dif real,
    gti real,
    "flagR" real,
    se real,
    sa real,
    temp real,
    ap real,
    rh real,
    ws real,
    wd real,
    pwat real
);

ALTER TABLE IF EXISTS pv.ts_meteodata
    OWNER to dev;'