from sqlalchemy import create_engine, Column, BigInteger, Integer, String, ForeignKey, DateTime
from datetime import datetime, timezone
from sqlalchemy.orm import declarative_base

Base = declarative_base()

class ToDo(Base):
    __tablename__ = "todo"

    id = Column(BigInteger, primary_key=True)
    name = Column(String(255), nullable=False)
    createdAtUtc = Column(DateTime(timezone=False), nullable=False)
    deletedAtUtc = Column(DateTime(timezone=False), nullable=True)
