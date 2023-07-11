#pragma once

#include "Iterable.tpp"

// Your implementations go here.
# pragma once
# include "Iterable.tpp"
# include <utility>
# include <stdexcept>
# include <memory>
#include <algorithm>

// Repeat Iterable and Iterator
template <typename T>
class RepeatIterator;

template <typename T>
class RepeatIterable : public IIterable<T> {
public:
    RepeatIterable(T value) : value(value) {}

    IIterator<T> *iter() const {
        return new RepeatIterator<T>(value);
    }

private:
    T value;
};

template <typename T>
class RepeatIterator : public IIterator<T> {
public:
    RepeatIterator(T value) : value(value) {}

    T next() {
        return value;
    }

private:
    T value;
};

template <typename T>
IIterable<T> *repeat(T value) {
    return new RepeatIterable<T>(value);
}

// Count Iterable and Iterator
template <typename T>
class CountIterator;

template <typename T>
class CountIterable : public IIterable<T> {
public:
    CountIterable(T start, T delta)
                    : start(start), delta(delta) {}

    IIterator<T> *iter() const {
        return new CountIterator<T>(start, delta);
    }

private:
    T start, delta;
};

template <typename T>
class CountIterator : public IIterator<T> {
public:
    CountIterator(T start, T delta) : value(start), delta(delta) {}

    T next() {
        T current = value;
        value += delta;
        return current;
    }

private:
    T value, delta;
};

template <typename T>
IIterable<T> *count(T start, T delta) {
    return new CountIterable<T>(start, delta);
}

// Skip Iterable and Iterator
template <typename T>
class SkipIterator;

template <typename T>
class SkipIterable : public IIterable<T> {
public:
    SkipIterable(unsigned k, IIterable<T> *iterable) : k(k), iterable(iterable) {}

    IIterator<T> *iter() const {
        IIterator<T> *iterator = iterable->iter();
        for (unsigned i = 0; i < k; ++i) {
            if (iterator->has_next()) {
                iterator->next();
            } else {
                break;
            }
        }
        return iterator;
    }

private:
    unsigned k;
    IIterable<T> *iterable;
};

template <typename T>
class TakeIterator;

template <typename T>
class TakeIterable : public IIterable<T> {
public:
    TakeIterable(unsigned k, IIterable<T> *iterable) : k(k), iterable(iterable) {}

    IIterator<T> *iter() const {
        return new TakeIterator<T>(k, iterable->iter());
    }

private:
    unsigned k;
    IIterable<T> *iterable;
};

template <typename T>
class TakeIterator : public IIterator<T> {
public:
    TakeIterator(unsigned k, IIterator<T> *iterator) : k(k), iterator(iterator), count(0) {}

    T next() {
        if (count < k) {
            count++;
            return iterator->next();
        } else {
            throw std::out_of_range("TakeIterator: No more elements");
        }
    }

    bool has_next() {
        return count < k && iterator->has_next();
    }

private:
    unsigned k;
    IIterator<T> *iterator;
    unsigned count;
};

template <typename T>
IIterable<T> *take(unsigned k, IIterable<T> *iterable) {
    return new TakeIterable<T>(k, iterable);
}

template <typename T>
IIterable<T> *skip(unsigned k, IIterable<T> *iterable) {
    return new SkipIterable<T>(k, iterable);
}

// Cycle Iterable and Iterator
template <typename T>
class CycleIterator;

template <typename T>
class CycleIterable : public IIterable<T> {
public:
    CycleIterable(IIterable<T> *iterable) : iterable(iterable) {}

    IIterator<T> *iter() const {
        return new CycleIterator<T>(iterable->iter());
    }

private:
    IIterable<T> *iterable;
};

template <typename T>
class CycleIterator : public IIterator<T> {
public:
    CycleIterator(IIterator<T> *iterator) : iterator(iterator), initial_iterator(iterator->clone()) {}

    T next() {
        if (!iterator->has_next()) {
            iterator = initial_iterator->clone();
        }
        return iterator->next();
    }

    bool has_next() {
        return true;
    }

private:
    IIterator<T> *iterator;
    IIterator<T> *initial_iterator;
};

template <typename T>
IIterable<T> *cycle(IIterable<T> *iterable) {
    return new CycleIterable<T>(iterable);
}

// Concat Iterable and Iterator
template <typename T>
class ConcatIterator;

template <typename T>
class ConcatIterable : public IIterable<T> {
public:
    ConcatIterable(IIterable<T> *iterable1, IIterable<T> *iterable2)
            : iterable1(iterable1), iterable2(iterable2) {}

    IIterator<T> *iter() const {
        return new ConcatIterator<T>(iterable1->iter(), iterable2->iter());
    }

private:
    IIterable<T> *iterable1;
    IIterable<T> *iterable2;
};

template <typename T>
class ConcatIterator : public IIterator<T> {
public:
    ConcatIterator(IIterator<T> *iterator1, IIterator<T> *iterator2)
            : iterator1(iterator1), iterator2(iterator2) {}

    T next() {
        if (iterator1->has_next()) {
            return iterator1->next();
        } else if (iterator2->has_next()) {
            return iterator2->next();
        } else {
            throw std::out_of_range("ConcatIterator: No more elements");
        }
    }

    bool has_next() {
        return iterator1->has_next() || iterator2->has_next();
    }

private:
    IIterator<T> *iterator1;
    IIterator<T> *iterator2;
};

template <typename T>
IIterable<T> *concat(IIterable<T> *iterable1, IIterable<T> *iterable2) {
    return new ConcatIterable<T>(iterable1, iterable2);
}

// PairIterator
template<typename T>
class PairIterator : public IIterator<std::pair<T, T>> {
private:
    IIterator<T> *mIterator1;
    IIterator<T> *mIterator2;

public:
    PairIterator(IIterator<T> *iterator1, IIterator<T> *iterator2)
            : mIterator1(iterator1), mIterator2(iterator2) {}

    virtual std::pair<T, T> next() override {
        T value1 = mIterator1->next();
        T value2 = mIterator2->next();
        return std::make_pair(value1, value2);
    }

    virtual bool has_next() const override {
        return mIterator1->has_next() && mIterator2->has_next();
    }

    virtual ~PairIterator() override {
        delete mIterator1;
        delete mIterator2;
    }
};

// PairIterable
template<typename T>
class PairIterable : public IIterable<std::pair<T, T>> {
private:
    IIterable<T> *mIterable1;
    IIterable<T> *mIterable2;

public:
    PairIterable(IIterable<T> *iterable1, IIterable<T> *iterable2)
            : mIterable1(iterable1), mIterable2(iterable2) {}

    virtual IIterator<std::pair<T, T>> * iter() const override {
        return new PairIterator<T>(mIterable1->iter(), mIterable2->iter());
    }

    virtual ~PairIterable() override {
        delete mIterable1;
        delete mIterable2;
    }
};

template<typename T>
IIterable<std::pair<T, T>> * pair(IIterable<T> *iterable1, IIterable<T> *iterable2) {
    return new PairIterable<T>(iterable1, iterable2);
}

// SelectIterator
template<typename T, typename Func>
class SelectIterator : public IIterator<T> {
private:
    IIterator<T> *mSourceIterator;
    Func mFunc;

public:
    SelectIterator(IIterator<T> *sourceIterator, Func func)
            : mSourceIterator(sourceIterator), mFunc(func) {}

    virtual T next() override {
        return mFunc(mSourceIterator->next());
    }

    virtual bool has_next() const override {
        return mSourceIterator->has_next();
    }

    virtual ~SelectIterator() override {
        delete mSourceIterator;
    }
};

// SelectIterable
template<typename T, typename Func>
class SelectIterable : public IIterable<T> {
private:
    IIterable<T> *mSourceIterable;
    Func mFunc;

public:
    SelectIterable(IIterable<T> *sourceIterable, Func func)
            : mSourceIterable(sourceIterable), mFunc(func) {}

    virtual IIterator<T> * iter() const override {
        return new SelectIterator<T, Func>(mSourceIterable->iter(), mFunc);
    }

    virtual ~SelectIterable() override {
        delete mSourceIterable;
    }
};

template<typename T, typename Func>
IIterable<T> * select(IIterable<T> *sourceIterable, Func func) {
    return new SelectIterable<T, Func>(sourceIterable, func);
}

// MinIterator
template<typename T>
class MinIterator : public IIterator<T> {
private:
    IIterator<T> *mIterator1;
    IIterator<T> *mIterator2;

public:
    MinIterator(IIterator<T> *iterator1, IIterator<T> *iterator2)
            : mIterator1(iterator1), mIterator2(iterator2) {}

    virtual T next() override {
        T value1 = mIterator1->next();
        T value2 = mIterator2->next();
        return std::min(value1, value2);
    }

    virtual bool has_next() const override {
        return mIterator1->has_next() && mIterator2->has_next();
    }

    virtual ~MinIterator() override {
        delete mIterator1;
        delete mIterator2;
    }
};

// MinIterable
template<typename T>
class MinIterable : public IIterable<T> {
private:
    IIterable<T> *mIterable1;
    IIterable<T> *mIterable2;

public:
    MinIterable(IIterable<T> *iterable1, IIterable<T> *iterable2)
            : mIterable1(iterable1), mIterable2(iterable2) {}

    virtual IIterator<T> * iter() const override {
        return new MinIterator<T>(mIterable1->iter(), mIterable2->iter());
    }

    virtual ~MinIterable() override {
        delete mIterable1;
        delete mIterable2;
    }
};

template<typename T>
IIterable<T> * min(IIterable<T> *iterable1, IIterable<T> *iterable2) {
    return new MinIterable<T>(iterable1, iterable2);
}