/** 
 * Element for linked lists.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef UTILITY_LINKED_NODE_HPP_
#define UTILITY_LINKED_NODE_HPP_

#include "Object.hpp"

namespace utility
{  
  /** 
   * @param Type  data type of element.
   * @param Alloc heap memory allocator class.
   */
  template <typename Type, class Alloc=::Allocator>
  class LinkedNode : public ::Object<Alloc>
  {
    typedef ::Object<Alloc> Parent;  
  
  public:
  
    /**
     * Constructor.
     *
     * Given element will be copied to self nodes structure by a copy constructor calling.
     *
     * @param element an user element of this node.
     */
    LinkedNode(const Type& element) : Parent(),
      prev_    (this),
      next_    (this),
      index_   (0),
      element_ (element){
    }
  
    /**
     * Destructor.
     */
    virtual ~LinkedNode()
    {
      LinkedNode* node = this->next_;
      while(node->index_ != 0)
      {
        node->index_--;
        node = node->next_;
      }
      next_->prev_ = prev_;
      prev_->next_ = next_;
      prev_ = this;
      next_ = this;
    }
  
    /**
     * Inserts a new element after this.
     *
     * Method links a node after this and reindexes
     * chain of nodes starts from given node.
     *
     * @param node pointer to inserted node.
     */
    virtual void after(::utility::LinkedNode<Type,Alloc>* node)
    {
      link(node);
      node->index_ = index_;
      do{
        node->index_++;
        node = node->next_;
      }while(node->index_ != 0);
    }
  
    /**
     * Inserts a new element after this.
     *
     * Method links a node before this and reindexes
     * chain of nodes starts from this node.
     *
     * @param node pointer to inserted node.
     */
    virtual void before(::utility::LinkedNode<Type,Alloc>* node)
    {
      prev_->link(node);
      node->index_ = index_;
      node = this;
      do{
        node->index_++;
        node = node->next_;
      }while(node->index_ != 0);
    }

    /**
     * Returns previous element.
     *
     * @return previous element.
     */  
    virtual ::utility::LinkedNode<Type,Alloc>* prev() const
    {
      return prev_;
    }
    
    /**
     * Returns next element.
     *
     * @return next element.
     */  
    virtual ::utility::LinkedNode<Type,Alloc>* next() const
    {
      return next_;
    }

    /**
     * Returns the element.
     *
     * @return next element.
     */  
    virtual Type element() const
    {
      return element_;
    }

    /**
     * Returns the element index.
     *
     * @return element index.
     */  
    virtual int32 index() const
    {
      return index_;
    }
  
  private:
  
    /**
     * Links a given node after this.
     *
     * @param node pointer to linking node.
     */
    void link(::utility::LinkedNode<Type,Alloc>* node)
    {
      next_->prev_ = node;
      node->next_ = next_;
      next_ = node;
      node->prev_ = this;
    }

    /**
     * Copy constructor.
     *
     * @param obj reference to source object.
     */
    LinkedNode(const LinkedNode& obj);

    /**
     * Assignment operator.
     *
     * @param obj reference to source object.
     * @return reference to this object.     
     */
    LinkedNode& operator =(const LinkedNode& obj);
  
    LinkedNode*             prev_;
    LinkedNode*             next_;
    int32                   index_;
    Type                    element_;
  
  };
}
#endif // UTILITY_LINKED_NODE_HPP_
