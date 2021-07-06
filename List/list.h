template <typename T> class lNode {
public:
  lNode() : next(nullptr), prev(nullptr) {}
  lNode(const T& item) : key(item), next(nullptr), prev(nullptr) {}

  lNode<T> *prev, *next;
  T key;
};

template <typename T> class list {
public:
  class iterator {
  public:
    iterator(lNode<T>* pos) : ptr(pos) {}

    T& operator*() { return ptr->key; }
    iterator operator++() {
      ptr = ptr->next;
      return *this;
    }
    iterator operator++(int n) {
      iterator result = *this;
      ptr = ptr->next;
      return result;
    }
    iterator operator--() {
      ptr = ptr->prev;
      return *this;
    }
    iterator operator--(int n) {
      iterator result = *this;
      ptr = ptr->prev;
      return result;
    }
    bool operator==(const iterator& other) {
      return ptr == other.ptr;
    }
    bool operator!=(const iterator& other) {
      return ptr != other.ptr;
    }

    lNode<T>* ptr;
  };

  list() {
    dummy = new lNode<T>();
    dummy->next = dummy;
    dummy->prev = dummy;
    n = 0;
  }
  ~list() {
    lNode<T> *current = dummy->next;
    while(current != dummy) {
      lNode<T> *next = current->next;
      delete current;
      current = next;
    }
    delete current;
  }

  int size() { return n; }
  iterator begin() { return iterator(dummy->next); }
  iterator end() { return iterator(dummy); }
  T& front() { return dummy->next->key; }
  T& back() { return dummy->prev->key; }

  void push_back(const T& item) {
    lNode<T> *newNode = new lNode<T>(item);
    lNode<T> *prev = dummy->prev;
    prev->next = newNode;
    dummy->prev = newNode;
    newNode->prev = prev;
    newNode->next = dummy;
    n++;
  }
  void pop_back() {
    lNode<T> *toRemove = dummy->prev;
    if(toRemove != dummy) {
      dummy->prev = toRemove->prev;
      toRemove->prev->next = dummy;
      delete toRemove;
      n--;
    }
  }
  void push_front(const T& item) {
    lNode<T> *newNode = new lNode<T>(item);
    lNode<T> *next = dummy->next;
    next->prev = newNode;
    dummy->next = newNode;
    newNode->next = next;
    newNode->prev = dummy;
    n++;
  }
  void pop_front() {
    lNode<T> *toRemove = dummy->next;
    if(toRemove != dummy) {
      dummy->next = toRemove->next;
      toRemove->next->prev = dummy;
      delete toRemove;
      n--;
    }
  }
  iterator insert(const iterator& pos,const T& item) {
    lNode<T> *newNode = new lNode<T>(item);
    lNode<T> *prev = pos.ptr->prev;
    pos.ptr->prev = newNode;
    newNode->next = pos.ptr;
    prev->next = newNode;
    newNode->prev = prev;
    n++;
    return iterator(newNode);
  }
  iterator erase(const iterator& pos) {
    if(pos.ptr != dummy) {
      lNode<T> *next = pos.ptr->next;
      lNode<T> *prev = pos.ptr->prev;
      next->prev = prev;
      prev->next = next;
      delete pos.ptr;
      n--;
      return iterator(next);
    }
    return this->end();
  }
private:
  lNode<T> *dummy;
  int n;
};
