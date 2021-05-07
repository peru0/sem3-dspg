from .union_find import *
import pytest


def test_union_find():
    union = UnionFind(4)

    union.union(0, 3)
    assert union.is_in_same_set(0, 3)


def test_union_find2():
    union = UnionFind(4)

    union.union(0, 3)
    union.union(1, 2)
    union.union(2, 3)
    assert union.is_in_same_set(0, 1)
