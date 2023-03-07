#! /bin/bash

psql -U postgres -d postgres -c "create user dev with superuser;"