#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE
void ULListStr::push_back(const std::string& val){
  if (tail_ == nullptr){
    tail_ = new Item();
    head_ = tail_;

    tail_->val[0] = val;
    tail_->first = 0;
    tail_->last = 1;
  }
  else if(tail_->last < ARRSIZE){
    tail_->val[tail_->last] = val;
    tail_->last++;
  }
  else{
    Item* temp = new Item();

    temp->val[0] = val;
    temp->first = 0;
    temp-> last =1;
    temp -> prev = tail_;
    tail_->next = temp;
    tail_ = temp;

  }
  size_ ++;
}

void ULListStr::pop_back(){
  if (size_==0){
    return;
  }

  tail_->last--;

  if(tail_->first == tail_->last){

    if (head_ == tail_){
      delete tail_;
      head_ = NULL;
      tail_ = NULL;
    }
    else{
      Item* temp = tail_;
      tail_ = tail_->prev;
      tail_->next = NULL;
      delete temp;
    }
  }

    size_--;

}

void ULListStr::push_front(const std::string& val){
  if (head_ == NULL){
    head_ = new Item();
    tail_ = head_;
    head_->val[0] = val;
    head_ -> first = 0;
    head_ -> last = 1;
  }
  else if (head_->first > 0){
    head_->first--;
    head_->val[head_->first] = val;
  }
  else{
    Item* temp = new Item();
    
    temp->val[ARRSIZE - 1] = val;
    temp->first = ARRSIZE - 1;
    temp->last = ARRSIZE;

    temp->next = head_;
    head_->prev = temp;
    head_ = temp;
  }
  
  size_++;
}

void ULListStr::pop_front(){
  if (size_==0){
    return;
  }
  head_->first++;  
  if(head_->first == head_->last){
    if (head_ == tail_){
      delete head_;
      head_ = NULL;
      tail_ = NULL;
    }
    else{
      Item* temp = head_;
      head_ = head_->next;
      head_->prev = NULL;
      delete temp;
    }
  }
  
  size_--;
}

std::string const & ULListStr::back() const{
  return tail_->val[tail_->last - 1];
}

std::string const & ULListStr::front() const{
  return head_->val[head_->first];
}

std::string* ULListStr::getValAtLoc(size_t loc) const{
  if (loc >= size_){
    return NULL;
  }

  Item* curr = head_;

  while (curr != nullptr){
    size_t curr_num = curr->last - curr->first;

    if(loc < curr_num){
      return &curr->val[curr->first+loc];
    }

    loc -= curr_num;
    curr = curr->next;
  }

  return NULL;
}

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
