#include <iostream>

//无旋Treap
template <typename T>
class Treap {
private:
    struct TreapNode {
        T data;
        size_t size;
        TreapNode *lson, *rson;
        TreapNode(const T& data_) {
            data = data_;
            lson = rson = nullptr;
            size = 1;
        }
        TreapNode(const T& data, const size_t& size, const TreapNode*& lson, const TreapNode*& rson):
        data(data), size(size), lson(lson), rson(rson){}

        size_t& getsize() {
            return size;
        }
        TreapNode*& getleftson() {
            return lson;
        }
        TreapNode*& getrightson() {
            return rson;
        }
        const T& getdata() const {
            return data;
        }
    };
    TreapNode* root;
    int Compare(const T& x,const T& y) const {
        if (x == y) {
            return 0;
        } else if (x < y) {
            return -1;
        } else {
            return 1;
        }
    }

    inline void pushup(TreapNode*& rt) {
        rt->getsize() = rt->getleftson()->getsize() + rt->getrightson()->getsize();
    }
public:
    Treap() {
        root = nullptr;
    }

    void split(TreapNode*& rt, TreapNode*& x, TreapNode*& y, const T& val) {
        if (rt == nullptr) {
            x = y = 0;
            return;
        } else if (Compare(rt->data, val) <= 0) {
            x = rt;
            split(rt->getrightson(), x->rson, y, val);
        } else {
            y = rt;
            split(rt->getleftson(), x, y->getleftson(), val);
        }
        pushup(rt);
    }
};

int main() {

    return 0;
}