
#include "queue.h"

// TODO: Implement everything from the queue class here, along with
// testqueue ... we are only providing checkinvariant

bool queue::checkinvariant( ) const
{
   if( current_size == 0 )
   {
      if( first )
      {
         std::cout << "INVARIANT: ";
         std::cout << "current_size == 0, but first != nullptr\n";
         return false;
      }

      if( last )
      {
         std::cout << "INVARIANT: ";
         std::cout << "current_size == 0, but last != nullptr\n";
         return false;
      }

      return true;
   }
 
   size_t s = 0;
   const qnode* l = nullptr; // This will remember the last node.

   for( const qnode* p = first; p; p = p -> next )
   {
      if( s == current_size )
      {
         std::cout << "INVARIANT: ";
         std::cout << "current_size is less than real size: ";
         std::cout << current_size << "\n\n";
         // I don't want to count further because list may be corrupt.
         return false;
      }
      ++ s;
      l = p;
   }

   if( s != current_size )
   {
      std::cout << "INVARIANT ";
      std::cout << "current_size is not equal to real size\n";
      std::cout << "current_size = " << current_size << "\n";
      std::cout << "real size    = " << s << "\n";

      return false;
   }

   if( l != last )
   {
      std::cout << "INVARIANT: last is not correct, ";
      std::cout << "it is " << last << " but must be " << l << "\n";
      return false;
   }

   return true;
}





queue::queue( const queue& q ):
current_size(q.current_size){
    if (current_size == 0) {
        first = nullptr;
        last = nullptr;
    } else {
        first = new qnode(q.first->val);
        last = first;
        for(qnode* head = q.first->next; head; head = head->next){
            qnode* newNode = new qnode(head->val);
            last->next = newNode;
            last = newNode;
        }
        last->next = nullptr;
    }
}

const queue& queue::operator= (const queue& q){
    
    if(q.current_size == 0){
        clear();
    } else {
        while(current_size>q.current_size) pop();
        while(current_size<q.current_size) push(0);
        qnode* currq = q.first;
        qnode* currm = first;
        for(int i=0;i<current_size;i++){
            last = currm;
            currm->val = currq->val;
            currm = currm->next;
            currq = currq->next;
        }
        
    }
    
    return *this;
}

queue::queue(std::initializer_list<double> init):
    current_size(init.size())
{
    if(current_size == 0){
        first = nullptr;
        last = nullptr;
    } else {
        bool firstOrNot = true;
        for(double d: init){
            qnode* newNode = new qnode(d);
            if(firstOrNot){
                first = newNode;
                last = newNode;
                firstOrNot = false;
            } else {
                last->next = newNode;
                last = newNode;
            }
        }
        
    }
}

queue::~queue(){
    qnode* curr = first;
    while(curr){
        qnode* next = curr->next;
        delete curr;
        curr = next;
    }
    first = nullptr;
    last = nullptr;
    std::cout<<"was destructed \n";
}

//

void queue::push(double d){
    qnode* newNode = new qnode(d);
    current_size++;
    if(last){
        last->next = newNode;
        last = newNode;
    } else {
        first = newNode;
        last = newNode;
    }
}

void queue::pop(){
    if(first){
        
        if(first == last){
            delete first;
            first = nullptr;
            last = nullptr;
        } else {
            qnode* oldFirst = first;
            first = first->next;
            delete oldFirst;
            oldFirst = nullptr;
        }
        
        current_size--;
    } else {
        throw std::runtime_error("pop: there is no elements in queue");
    }
}

void queue::clear(){
    while(current_size>0){
        std::cout<<first->val<<" "<<last->val<<" clear is here"<<std::endl;
        pop();
    }
}

double queue::peek() const{
    if(first) return first->val;
    throw std::runtime_error("peek: queue is empty");
}

void queue::print(std::ostream& out) const {
    qnode* curr = first;
    while(curr){
        out<<curr->val<<"<-";
        curr = curr->next;
    }
    out<<"/\n";
}

void testqueue(){
    queue q;
    q.checkinvariant();
    q.push(5.0);
    q.checkinvariant();
    q.push(3.0);
    q.checkinvariant();
    q.print(std::cout);
    q.checkinvariant();
    q.pop();
    q.checkinvariant();
    q.print(std::cout);
    q.checkinvariant();
    q.pop();
    q.checkinvariant();
    q.print(std::cout);
    q.checkinvariant();
    q.push(1.0);
    q.checkinvariant();
    q.push(2.0);
    q.checkinvariant();
    q.push(3.0);
    q.checkinvariant();
    q.push(4.0);
    q.checkinvariant();
    q.print(std::cout);
    q.checkinvariant();
    queue q2(q);
    
    q2.clear();
    q2.checkinvariant();
    
    q.print(std::cout);
    q.checkinvariant();
    
    q2.print(std::cout);
    q2.checkinvariant();
    queue q3 = {1};
    q3.checkinvariant();
    q3.push(2);
    q3.checkinvariant();
    q3.print(std::cout);
    q3.pop();
    q3.checkinvariant();
   
    
}


