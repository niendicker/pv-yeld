#! /bin/bash

psql -U dev -d pv -c 'CREATE TABLE pv.tmy_p90_meteodata (
    day real,
    "time" time without time zone,
    ghi real,
    dni real,
    dif real,
    se real,
    sa real,
    temp real,
    ap real,
    rh real,
    ws real,
    wd real,
    pwat real
);

ALTER TABLE IF EXISTS pv.tmy_p90_meteodata
    OWNER to dev;'