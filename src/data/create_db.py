import os
import psycopg2
from psycopg2.extensions import ISOLATION_LEVEL_AUTOCOMMIT

host = os.getenv("POSTGRES_HOST")
port = os.getenv("POSTGRES_PORT")
user = os.getenv("POSTGRES_USER")
password = os.getenv("POSTGRES_PASSWORD")
dbname = os.getenv("POSTGRES_DB")

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