#! /bin/bash

psql -U dev -d pv -c 'CREATE SCHEMA pv AUTHORIZATION dev;'