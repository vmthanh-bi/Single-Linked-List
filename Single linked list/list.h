template <typename T> class lNode {
public:
  lNode() : next(nullptr) {}
  lNode(const T& item) : key(item), next(nullptr) {}

  lNode<T> *next;
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
    bool operator==(const iterator& other) {
      return ptr == other.ptr;
    }
    bool operator!=(const iterator& other) {
      return ptr != other.ptr;
    }
    lNode<T>* ptr;
  };

  list() {
    head = nullptr;
    tail = nullptr;
    n = 0;
  }

  ~list() {
    lNode<T> *curr = head;
    while (curr->next != nullptr) {
        lNode<T> *next = curr->next;
        delete curr;
        curr = next;
      }
    delete curr;
  }

  int size() { return n; }
    iterator begin() { return iterator(head); }
    iterator end() { return iterator(nullptr); }
    T& front() { return head->key; }
    T& back() { return tail->key; }
    
  bool empty(){ return head == nullptr; }
  
  void push_back(const T& item) {
    lNode<T> *newNode = new lNode<T>(item);
    newNode->next = nullptr;
    if (this->empty()) {
        head = newNode;
        tail = newNode;
        newNode = nullptr;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }
    n++;
  }
  void pop_back() {
    lNode<T> *curr = head;
    lNode<T> *prev;
    curr = head;
    while (curr->next != nullptr) {
        prev = curr;
        curr = curr->next;
    }
    tail = prev;
      prev->next = nullptr;
      delete curr;
    n--;
  }
  void push_front(const T& item) {
    lNode<T> *newNode = new lNode<T>(item);
    newNode->next = head;
    head = newNode;
    if(tail == nullptr) tail = head;
    n++;
  }
  void pop_front() {
    lNode<T> *toRemove = head;
    toRemove = head;
    head = head->next;
    delete toRemove;
    if(head == nullptr) tail = nullptr;
    n--;
  }
  iterator insert(const iterator& pos,const T& item) {
    lNode<T> *newNode = new lNode<T>(item);
    lNode<T> *curr = head;
    lNode<T> *prev;
    // This code will fail in the special case of trying to insert a new
    // item before the start of the list. I need an if statement to check
    // for that case and handle it separately.
    curr = head;
    while (curr != pos.ptr) {
        prev = curr;
        curr = curr->next;
    }
    prev->next = newNode;
    newNode->next = curr;
    n++;
    return iterator(newNode);
  }
  iterator erase(const iterator& pos) {
    lNode<T> *curr = head;
    lNode<T> *prev;
    // I need to check for the special case of removing the first item in
    // the list - needs to be handled as a separate case.
    curr = head;
    while (curr != pos.ptr) {
        prev = curr;
        curr = curr->next;
    }
    prev->next = curr->next;
    delete curr;
    n--;
    return iterator(prev->next);
    return this->end();
  }
private:
  lNode<T> *head;
  lNode<T> *tail;
  int n;
};
