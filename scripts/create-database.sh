#! /bin/bash

psql -U dev -d postgres -c "CREATE DATABASE pv
  WITH
  OWNER = dev
  ENCODING = 'UTF8'
  CONNECTION LIMIT = -1
  IS_TEMPLATE = False;"