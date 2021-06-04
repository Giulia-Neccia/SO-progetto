
// these are trivial helpers to support you in case you want
// to do a bitmap implementation
int levelIdx(size_t idx) { return (int)floor(log2(idx)); };

int buddyIdx(int idx) {
  if (idx & 0x1) {
    return idx - 1;
  }
  return idx + 1;
}

int parentIdx(int idx) { return idx / 2; }

int startIdx(int idx) { return (idx - (1 << levelIdx(idx))); }
