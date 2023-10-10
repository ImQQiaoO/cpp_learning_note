#include "Folder.h"
#include "Message.h"

void swap(Folder &lhs, Folder &rhs) {
    using std::swap;
    // 将每个Folder的指针从它原来所在的Message中删除
    for (auto m : lhs.msgs)
        m->remFldr(&lhs);
    for (auto m : rhs.msgs)
        m->remFldr(&rhs);
    // 交换Folder指针set
    swap(lhs.msgs, rhs.msgs);
    // 将每个Folder的指针添加到它的新Message中
    for (auto m : lhs.msgs)
        m->addFldr(&lhs);
    for (auto m : rhs.msgs)
        m->addFldr(&rhs);
}

Folder::Folder(const Folder &f) : msgs(f.msgs) {
    add_to_Message(f);
}

Folder::~Folder() {
    remove_from_Message();
}

Folder &Folder::operator=(const Folder &rhs) {
    remove_from_Message();
    msgs = rhs.msgs;
    add_to_Message(rhs);
    return *this;
}

void Folder::add_to_Message(const Folder &f) {
    for (auto m : f.msgs)
        m->addFldr(this);
}

void Folder::remove_from_Message() {
    for (auto m : msgs)
        m->remFldr(this);
}