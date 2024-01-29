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
  // Check if the list is empty
  if(head_ == NULL && tail_ == NULL){
    // Create a new Item
    Item *fresh = new Item;
    // Have the head of the list point to the Item
    head_ = fresh;
    // Have the tail of the list point to the Item
    tail_ = fresh;
    // Update the first value in the new item
    fresh->val[0] = val;
    // Update the Item's last variable
    fresh->last = 1;
    // Update the size of the list
    size_+= 1;
  }
  // If the list isn't empty
  else{
    // Check if the Item is at max capacity
    if(tail_->last == ARRSIZE){
      // Create a new item
      Item *fresh = new Item;
      // Update the tails next pointer to the new tail
      tail_->next = fresh;
      // Update the new Iems previous pointer to the old tail
      fresh->prev = tail_;
      // Update the new tail
      tail_ = fresh;
      // Update the new tails first value
      fresh->val[0] = val;
      // Update the new tails last variable
      fresh->last = 1;
      // Update the size of the list
      size_+= 1;
    }
    // If the item isn't at max capacity
    else{
      // Update the tails last value
      tail_->val[tail_->last] = val;
      // Update the tails last variable
      tail_->last +=1;
      // Update the size of the list
      size_+=1;
    }
  }
}

void ULListStr::pop_back(){
  // Check if the list is empty
  if(head_ == NULL && tail_ == NULL){
    return;
  }
  // If the tail node has only one element
  if(tail_->last - tail_->first == 1){
    // Temporarily store the current tail to delete it later
    Item* temp = tail_; 
    // If there's only one node in the list
    if(head_ == tail_){
      head_ = tail_ = NULL;
    }
    // If there are multiple nodes in the list
    else{
      // Move the tail pointer to the previous node
      tail_ = tail_->prev; 
      // Update the new tail's next pointer to NULL
      if(tail_ != NULL){
        tail_->next = NULL;
      }
    }
    // Delete the old tail node
    delete temp; 
    // Decrement the size of the list
    size_-=1;     
  }
  // If the tail node has more than one element, just remove the last one
  else{
    tail_->last -= 1;
    // Decrement the size of the list
    size_-= 1; 
  }
}


void ULListStr::push_front(const std::string& val){
  // Check if the list is empty
  if(head_ == NULL && tail_ == NULL){
    // Create a new Item
    Item *fresh = new Item;
    // Have the head of the list point to the Item
    head_ = fresh;
    // Have the tail of the list point to the Item
    tail_ = fresh;
    // Update the last value in the new item
    fresh->val[9] = val;
    // Update the Item's last variable
    fresh->last = 10;
    // Update the Item's first variable
    fresh->first = 9;
    // Update the size of the list
    size_+= 1;
  }
  // If the list isn't empty
  else{
    // Check if the Item first variable isn't at 0
    if(head_->first != 0){
      // Update the heads first value
      head_->val[head_->first-1] = val;
      // Update the head's first variable
      head_->first -=1;
      // Update the size of the list
      size_+=1;
    }
    else{
      // If first and last are 0
      if(head_->last == 0){
        // Update the head value 
        head_->val[9] = val;
        // Update the first variable
        head_->first = 9;
        // Update the last variable
        head_->last = 10;
        // Update the size of the list
        size_+=1;
      }
      // If the item is at max capacity
      else{
        // Create a new item
        Item *fresh = new Item;
        // Update the new item's next pointer to the head 
        fresh->next = head_;
        // Update the new Iems previous pointer to NULL
        fresh->prev = NULL;
        // Update the new head
        head_ = fresh;
        // Update the new head's last value
        fresh->val[9] = val;
        // Update the new heads last variable
        fresh->last = 10;
        // Update the new heads first variable
        fresh->first = 9;
        // Update the size of the list
        size_+= 1;
      }
    }
  }
}

void ULListStr::pop_front(){
  // Check if the list is empty
  if(head_ == NULL && tail_ == NULL){
    return;
  }
  // If the head node has one or zero elements
  if(head_->last - head_->first == 1){
    // Temporarily store the current head to delete it later
    Item* temp = head_; 
    // If there's only one node in the list
    if(head_ == tail_){
      head_ = tail_ = NULL;
    }
    // If there are multiple nodes in the list
    else{
      // Move the head pointer to the next node
      head_ = head_->next; 
      // Update the new heads's prev pointer to NULL
      if(head_ != NULL){
        head_->prev = NULL;  
      }
    }
    // Delete the old head node
    delete temp; 
    // Decrement the size of the list
    size_-=1;     
  }
  // If the head node has more than one element
  else{
    // Remove the first
    // Update the head's first variable
    head_->first += 1;
    // Decrement the size of the list
    size_-= 1; 
  }
}

std::string const & ULListStr::back() const{
  static std::string emptyString;
  if(head_ == NULL && tail_ == NULL){
    return emptyString;
  }
  else if(tail_->last - tail_->first == 0){
    return emptyString;
  }
  else{
    return tail_->val[tail_->last-1];
  }
}

std::string const & ULListStr::front() const{
  static std::string emptyString;
  if(head_ == NULL && tail_ == NULL){
    return emptyString;
  }
  else if(head_->last - head_->first == 0){
    return emptyString;
  }
  else{
    return head_->val[head_->first];
  }
}

std::string* ULListStr::getValAtLoc(size_t loc) const{
  if (loc >= size_) {
    return NULL;
  }
  Item* curr = head_;
  size_t i = 0; 
  while (curr != NULL) {
    size_t count = curr->last - curr->first;
    if (i + count > loc) {
      size_t offset = loc - i;
      return &(curr->val[curr->first + offset]);
    }
    i += count;
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

