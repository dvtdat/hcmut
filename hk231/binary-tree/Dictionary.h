#ifndef DICTIONARY_H
#define DICTIONARY_H

template <typename Key, typename T>
class Dictionary {
private:
public:
    Dictionary() {}
    virtual ~Dictionary() {}

    virtual void clear() = 0;
    virtual void insert(const Key& k, const T& t) = 0;

    virtual T remove(const Key& k) = 0;
    virtual T removeAny() = 0;

    virtual T find(const Key& k) const = 0;
    virtual int size() = 0;
};

#endif // DICTIONARY_H