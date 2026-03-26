from sqlalchemy import create_engine, Column, BigInteger, Integer, String, ForeignKey, DateTime
from sqlalchemy.orm import declarative_base

Base = declarative_base()

class ToDo(Base):
    __tablename__ = "todo"

    id = Column(BigInteger, primary_key=True)
    name = Column(String(255), nullable=False)
    createdAtUtc = Column(BigInteger, nullable=False)
    deletedAtUtc = Column(BigInteger, nullable=True)

