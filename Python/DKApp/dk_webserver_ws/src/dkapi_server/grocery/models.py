from sqlalchemy import String, Integer
from sqlalchemy.orm import mapped_column, Mapped, DeclarativeBase
from ..database import Base
from typing import Optional


class Item(Base):
	__tablename__ = "Grocery"
	id: Mapped[int] = mapped_column(primary_key=True)
	name: Mapped[str] = mapped_column(String(30))
	list_id: Mapped[int] = mapped_column(default=0, primary_key=True)
	user_id: Mapped[int] = mapped_column(default=0)
	quant: Mapped[int]
	use: Mapped[Optional[str]] = mapped_column(String(255))
	state: Mapped[int] = mapped_column(default=0)


class List(Base):
	__tablename__ = "Grocery_Lists"
	id: Mapped[int] =mapped_column(primary_key=True)
	user_id: Mapped[int] = mapped_column(default=-1)
