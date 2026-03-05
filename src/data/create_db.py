import os
import psycopg2
from psycopg2.extensions import ISOLATION_LEVEL_AUTOCOMMIT

connection_string = os.getenv("ConnectionStrings__DefaultConnection", "host=postgresql port=5432 dbname=to-dos-api-cpp-db user=postgres password=password")
database_credentials = dict(item.split("=", 1) for item in connection_string.split())

host = database_credentials["host"]
port = database_credentials["port"]
user = database_credentials["user"]
password = database_credentials["password"]
dbname = database_credentials["dbname"]

try:
    # We connect to postgres because it contains a table with existing databases
    conn = psycopg2.connect(host=host, port=port, user=user, password=password, dbname="postgres")
except psycopg2.OperationalError as e:
    print(f"[ERROR]: Unable to connect to database. Code: {e}")
    exit(1)

# This is necessary because it is not possible to create a database in transaction mode
conn.set_isolation_level(ISOLATION_LEVEL_AUTOCOMMIT)

cursor = conn.cursor()

cursor.execute("SELECT 1 FROM pg_database WHERE datname = %s", (dbname,))

exists = cursor.fetchone()

if not exists:
    cursor.execute(f'CREATE DATABASE "{dbname}"')
    print(f"[INFO]: Database {dbname} created.")
else:
    print(f"[INFO]: Database {dbname} already exists, skipping.")

cursor.close()
conn.close()