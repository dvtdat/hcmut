#include "main.h"

const int positive_inf = 2147483647;

class imp_res : public Restaurant
{
public:
  // Only use for PURPLE method in Seat
  class OrderQueue
  {
  public:
    class Node
    {
    public:
      int data = 0;
      Node* next = NULL;
      Node(int data, Node* next = nullptr)
      {
        this->data = data;
        this->next = next;
      }
    };

    Node* front = NULL;
    Node* rear = NULL;
    int size = 0;

    void enqueue(int num)
    {
      Node* newNode = new Node(num);
      if (size == 0)
      {
        front = newNode;
        rear = newNode;
      }
      else if (size > 0)
      {
        rear->next = newNode;
        rear = newNode;
      }
      size++;
    }

    Node *atIndex(int num)
    {
      Node *temp = front;
      for (int i = 0; i < num; i++)
      {
        temp = temp->next;
      }
      return temp;
    }

    void DeleteOrderQueue()
    {
      while (front != nullptr)
      {
        Node* temp = front;
        front = front->next;
        delete temp;
        size--;
      }
      front = NULL;
      rear = NULL;
    }
  };

  class Queue
  {
  public:
    customer* front = NULL;
    customer* rear = NULL;
    int size = 0;

    void deleteQueue()
    {
      while (front != nullptr)
      {
        customer* temp = front;
        front = front->next;
        temp->next = nullptr;
        delete temp;
        size--;
      }
      front = NULL;
      rear = NULL;
      size = 0;
    }

    bool enqueue(customer* cus, bool addToGeneralQueue = false, bool skipMaxSize = false)
    {
      if ((this->checkname(cus) && (this->size < MAXSIZE || skipMaxSize) && cus->energy != 0) || addToGeneralQueue)
      {
        // Accept customer into queue, add at rear
        customer* newCus = new customer(cus->name, cus->energy, NULL, NULL);
        if (this->size == 0)
        {
          front = newCus;
          rear = newCus;
        }
        else if (this->size > 0)
        {
          this->rear->next = newCus;
          newCus->prev = this->rear;
          this->rear = newCus;
        }
        size++;
        return true;
      }
      return false;
    }

    // Remove from front of the queue
    void dequeue()
    {
      // Remove customer at head
      if (this->size == 0) return;
      customer* toDelete = this->front;
      this->front = this->front->next;
      if (this->front != nullptr) this->front->prev = nullptr;
      delete toDelete;
      this->size--;
      if (size == 0)
      {
        front = NULL;
        rear = NULL;
      }
    }

    void addToFront(customer* cus)
    {
      if (this->size == 0)
      {
        front = cus;
        rear = cus;
      }
      else if (this->size > 0)
      {
        this->front->prev = cus;
        cus->next = this->front;
        this->front = cus;
      }
      size++;
    }

    bool empty()
    {
      return (this->size == 0);
    }

    // Return true if there is no customer with the same name, return false otherwise
    bool checkname(customer* cus)
    {
      if (size == 0) return true;
      customer* temp = this->front;
      while (temp != nullptr)
      {
        if (temp->name == cus->name) return false;
        temp = temp->next;
      }
      return true;
    }

    void removeFromQueue(string name)
    {
      if (this->size == 0) return;
      customer* temp = this->front;
      while (temp != nullptr)
      {
        if (temp->name == name)
        {
          break;
        }
        temp = temp->next;
      }
      if (temp == this->front)
      {
        this->dequeue();
      }
      else if (temp == this->rear)
      {
        this->rear = this->rear->prev;
        if (this->rear != nullptr) this->rear->next = nullptr;
        this->size--;
        delete temp;
      }
      else
      {
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        this->size--;
        temp->next = nullptr;
        temp->prev = nullptr;
        delete temp;
      }
    }

    bool findCustomer(string name)
    {
      customer* temp = this->front;
      while (temp != nullptr)
      {
        if (temp->name == name)
        {
          return true;
        }
        temp = temp->next;
      }
      return (temp == nullptr);
    }

    int getIndex(string name)
    {
      int index = 0;
      customer* temp = this->front;
      while (temp != nullptr)
      {
        if (temp->name == name) return index;
        index++;
        temp = temp->next;
      }
      return index;
    }

    // if flag is True, delete all customer with energy > 0
    // if flag is False, delete all customer with energy < 0
    void LIGHT()
    {
      customer* temp = this->front;
      while (temp != nullptr)
      {
        temp->print();
        temp = temp->next;
      }
    }

    // TODO: Using Shell Sort (stable) with Division = 2, from the front of the queue to the
    // last customer whose |ENERGY| is the largest.

    customer* atIndex(int num)
    {
      customer* tempCus = front;
      for (int i = 0; i < num; i++)
      {
        tempCus = tempCus->next;
      }
      return tempCus;
    }

    int endIndexOfPURPLE()
    {
      customer* tempCus = front->next;
      int index = 0;
      int biggestIndex = 0;
      customer* biggestCus = front;
      while (tempCus != nullptr)
      {
        index++;
        if (abs(tempCus->energy) >= abs(biggestCus->energy))
        {
          biggestCus = tempCus;
          biggestIndex = index;
        }
        tempCus = tempCus->next;
      }
      return biggestIndex;
    }

    // EDIT
    bool compare(int a, int b, OrderQueue &orderQueue)
    {
      if (abs(atIndex(a)->energy) > abs(atIndex(b)->energy))
      {
        return true;
      }
      else if (abs(atIndex(a)->energy) == abs(atIndex(b)->energy))
      {
        if (orderQueue.atIndex(a)->data > orderQueue.atIndex(b)->data)
          return true;
        else return false;
      }
      return false;
    }

    void swap(int a, int b, OrderQueue &orderQueue)
    {
      // cout << "Swap: " << this->atIndex(a)->energy << " and " << this->atIndex(b)->energy << "\n";
      string tempStr = this->atIndex(a)->name;
      int tempInt = this->atIndex(a)->energy;

      this->atIndex(a)->name = this->atIndex(b)->name;
      this->atIndex(a)->energy = this->atIndex(b)->energy;
      this->atIndex(b)->name = tempStr;
      this->atIndex(b)->energy = tempInt;

      // Swap orderQueue
      tempInt = orderQueue.atIndex(a)->data;
      orderQueue.atIndex(a)->data = orderQueue.atIndex(b)->data;
      orderQueue.atIndex(b)->data = tempInt;
    }

    int insertionSort(int size, int begin, int k, OrderQueue &orderQueue)
    {
      int numOfSwap = 0;
      for (int i = k; i < size; i += k)
      {
        for (int j = i; (j >= k) && compare(j + begin, j + begin - k, orderQueue); j -= k)
        {
          swap(j + begin, j + begin - k, orderQueue);
          numOfSwap++;
        }
        // Debugging
        // for (int j = i; (j >= k); j -= k)
        // {
        //   cout << "Compare: " << this->atIndex(j + begin)->name << " - " << this->atIndex(j + begin)->energy;
        //   cout << " and " << this->atIndex(j + begin - k)->name << " - " << this->atIndex(j + begin - k)->energy;
        //   if (compare(j + begin, j + begin - k, orderQueue))
        //   {
        //     cout << " ==> TRUE" << "\n";
        //     swap(j + begin, j + begin - k, orderQueue);
        //     numOfSwap++;
        //   }
        //   else
        //   {
        //     cout << " ==> FALSE" << "\n";
        //     break;
        //   }
        // }
        // Debugging
      }
      return numOfSwap;
    }

    int PURPLE()
    {
      if (size == 0) return 0;
      int endIndex = endIndexOfPURPLE();
      int n = endIndex + 1;
      int numOfSwap = 0;
      OrderQueue orderQueue;
      for (int i = endIndex + 1; i > 0; i--)
      {
        orderQueue.enqueue(i);
      }

      for (int i = n / 2; i > 2; i /= 2)
      {
        // cout << "Increment = " << i << "\n";
        for (int j = 0; j < i; j++)
        {
          numOfSwap += insertionSort(n - j, j, i, orderQueue);
        }
      }
      // cout << "Increment = " << 1 << "\n";
      numOfSwap += insertionSort(n, 0, 1, orderQueue);
      orderQueue.DeleteOrderQueue();
      // Debugging
      cout << "--DEBUG--" << "\n";
      cout << "Num of Swap: " << numOfSwap << "\n";
      this->LIGHT();
      cout << "--DEBUG--" << "\n" << "\n";
      // Debugging
      return numOfSwap;
    }
  };

  // Only use for the REVERSE function
  class Stack
  {
  public:
    customer* top = nullptr;

    void push(customer* cus)
    {
      customer* newCus = new customer(cus->name, cus->energy, NULL, NULL);
      newCus->next = top;
      top = newCus;
    }

    void pop()
    {
      customer* temp = this->top;
      top = top->next;
      temp->next = NULL;
      delete temp;
    }

    void deleteStack()
    {
      customer* temp = this->top;
      while (temp != nullptr)
      {
        this->top = this->top->next;
        delete temp;
        temp = this->top;
      }
    }
  };

  class Seat
  {
  public:
    void deleteSeat()
    {
      while (size > 0)
      {
        BLUE_REMOVE();
      }
      if (size == 0) X = NULL;
    }
    customer* X = NULL;
    Queue CustomerQueue;
    // Contain all customer in the restaurant, its size is 2*MAXSIZE
    Queue GeneralQueue;
    int size = 0;
    // TESTING
    bool RED(customer* cus, bool addToSeat = false, bool skipCheckName = false)
    {
      if (GeneralQueue.checkname(cus) && cus->energy != 0 && GeneralQueue.size < (MAXSIZE * 2))
      {
        GeneralQueue.enqueue(cus, false, true);
      }
      else if (skipCheckName)
      {
        // Do nothing
      }
      else 
      {
        delete cus;
        return false;
      }
      if (this->size < MAXSIZE)
      {
        if (size == 0)
        {
          X = cus;
          X->next = X;
          X->prev = X;
        }
        else if (this->size < (MAXSIZE / 2))
        {
          if (cus->energy >= X->energy)
          {
            cus->next = X->next;
            cus->prev = X;
            X->next->prev = cus;
            X->next = cus;
          }
          else if (cus->energy < X->energy)
          {
            cus->prev = X->prev;
            cus->next = X;
            X->prev->next = cus;
            X->prev = cus;
          }
          X = cus;
        }
        else if (this->size >= (MAXSIZE / 2))
        {
          // Y is the place where the different between cus and Y is the largest, compare to all
          // of the seated customer
          customer* Y = X;
          int RES = abs(cus->energy - X->energy);
          customer* temp = X->next;
          while (temp != X)
          {
            if (abs(cus->energy - temp->energy) > RES)
            {
              RES = abs(cus->energy - temp->energy);
              Y = temp;
            }
            temp = temp->next;
          }
          RES = cus->energy - Y->energy;
          if (RES >= 0)
          {
            cus->next = Y->next;
            cus->prev = Y;
            Y->next->prev = cus;
            Y->next = cus;
          }
          else if (RES < 0)
          {
            cus->prev = Y->prev;
            cus->next = Y;
            Y->prev->next = cus;
            Y->prev = cus;
          }
          X = cus;
        }
        size++;
        return true;
      }
      else if (this->size >= MAXSIZE)
      {
        if (addToSeat) return false;
        bool flag = CustomerQueue.enqueue(cus);
        delete cus;
        return flag;
      }
      return false;
    }

    bool checkName(customer* cus)
    {
      customer* temp = X;
      do
      {
        if (temp->name == cus->name) return false;
        temp = temp->next;
      } while (temp != X);
      return true;
    }

    bool containCustomer(string name)
    {
      if (this->size == 0) return false;
      customer* temp = X;
      do
      {
        if (temp->name == name)
          return true;
        temp = temp->next;
      } while (temp != X);
      return false;
    }

    // TESTING
    void BLUE(int num)
    {
      // Delete [num] customer on the table base on their order of arrival
      if (num == 0) return;
      customer* temp = GeneralQueue.front;
      while (temp != nullptr && num > 0 && this->size > 0)
      {
        if (this->containCustomer(temp->name))
        {
          while (X->name != temp->name)
          {
            X = X->next;
          }
          temp = temp->next;
          GeneralQueue.removeFromQueue(X->name);
          this->BLUE_REMOVE();
          num--;
        }
        else temp = temp->next;
      }

      // Add customer in the CustomerQueue into the table
      while (CustomerQueue.size > 0)
      {
        customer* newCus = new customer(CustomerQueue.front->name, CustomerQueue.front->energy, nullptr, nullptr);
        CustomerQueue.dequeue();
        if (!this->RED(newCus, true, true))
        {
          CustomerQueue.addToFront(newCus);
          break;
        }
      }
    }

    void BLUE_REMOVE()
    {
      customer* temp = X;
      if (X->energy < 0)
      {
        X = X->prev;
      }
      else if (X->energy > 0)
      {
        X = X->next;
      }
      temp->prev->next = temp->next;
      temp->next->prev = temp->prev;
      size--;
      delete temp;
      if (size == 0) X = NULL;
    }

    void LIGHT(int num)
    {
      if (num == 0)
      {
        CustomerQueue.LIGHT();
      }
      if (size == 0) return;
      if (num > 0)
      {
        X->print();
        customer* temp = X->next;
        while (temp != X)
        {
          temp->print();
          temp = temp->next;
        }
      }
      else if (num < 0)
      {
        X->print();
        customer* temp = X->prev;
        while (temp != X)
        {
          temp->print();
          temp = temp->prev;
        }
      }
    }

    // TODO
    // Find minimum sublist (continuous element >= 4), begin from X, going clockwise
    // If that sublist exists, print the sublist, begin from the first smallest element, clockwise.
    // Else do nothing
    void UNLIMITED_VOID()
    {
      if (this->size < 4) return;
      int min_so_far = positive_inf;
      int min_current = 0;
      customer* best_begin = X;
      int best_length = 4;

      customer* begin = X;
      for (int i = 0; i < size; i++)
      {
        customer* cur_cus = begin;
        min_current = 0;
        for (int j = 0; j <= 3; j++)
        {
          min_current += cur_cus->energy;
          cur_cus = cur_cus->next;
        }
        if (min_current <= min_so_far)
        {
          if (min_current < min_so_far)
          {
            min_so_far = min_current;
            best_begin = begin;
            best_length = 4;
          }
          else if (min_current == min_so_far)
          {
            if (4 >= best_length)
            {
              min_so_far = min_current;
              best_begin = begin;
              best_length = 4;
            }
          }
        }
        for (int j = 4; j < size; j++)
        {
          min_current += cur_cus->energy;
          cur_cus = cur_cus->next;
          if (min_current <= min_so_far)
          {
            if (min_current < min_so_far)
            {
              min_so_far = min_current;
              best_begin = begin;
              best_length = j + 1;
            }
            else if (min_current == min_so_far)
            {
              if (j + 1 >= best_length)
              {
                min_so_far = min_current;
                best_begin = begin;
                best_length = j + 1;
              }
            }
          }
        }
        begin = begin->next;
      }

      int smallest_energy = best_begin->energy;
      customer* smallest_cus = best_begin;
      int smallest_cus_index = 0;
      customer* temp = best_begin;
      for (int i = 0; i < best_length; i++)
      {
        if (temp->energy < smallest_cus->energy)
        {
          smallest_cus = temp;
          smallest_cus_index = i;
        }
        temp = temp->next;
      }

      temp = smallest_cus;
      for (int i = smallest_cus_index; i < best_length; i++)
      {
        temp->print();
        temp = temp->next;
      }
      temp = best_begin;
      for (int i = 0; i < smallest_cus_index; i++)
      {
        temp->print();
        temp = temp->next;
      }
      return;
    }

    // TESTING
    void DOMAIN_EXPANSION()
    {
      if (size == 0) return;

      // cout << "DEBUG DOMAIN_EXPANSION: \n";
      // customer* tempCus = GeneralQueue.rear;
      // while (tempCus != nullptr)
      // {
      //   tempCus->print();
      //   tempCus = tempCus->prev;
      // }
      // cout << "DEBUG DOMAIN_EXPANSION: \n";

      int sorcerer = 0;
      int curse = 0;
      customer* temp = X;
      do
      {
        if (temp->energy > 0)
        {
          sorcerer += temp->energy;
        }
        else if (temp->energy < 0)
        {
          curse += temp->energy;
        }
        temp = temp->next;
      } while (temp != X);

      temp = CustomerQueue.front;
      while (temp != nullptr)
      {
        if (temp->energy > 0)
        {
          sorcerer += temp->energy;
        }
        else if (temp->energy < 0)
        {
          curse += temp->energy;
        }
        temp = temp->next;
      }

      curse = abs(curse);

      // If flag is True, delete all curses, else, delete all sorcerers
      bool flag = (sorcerer >= curse);

      temp = GeneralQueue.front;
      while (temp != nullptr)
      {
        if (flag)
        {
          if (temp->energy < 0)
          {
            if (this->containCustomer(temp->name))
            {
              while (X->name != temp->name)
              {
                X = X->next;
              }
              this->BLUE_REMOVE();
              temp = temp->next;
            }
            else if (CustomerQueue.findCustomer(temp->name))
            {
              CustomerQueue.removeFromQueue(temp->name);
              temp = temp->next;
            }
          }
          else
          {
            temp = temp->next;
          }
        }
        else
        {
          if (temp->energy > 0)
          {
            if (this->containCustomer(temp->name))
            {
              while (X->name != temp->name)
              {
                X = X->next;
              }
              this->BLUE_REMOVE();
              temp = temp->next;
            }
            else if (CustomerQueue.findCustomer(temp->name))
            {
              CustomerQueue.removeFromQueue(temp->name);
              temp = temp->next;
            }
          }
          else
          {
            temp = temp->next;
          }
        }
      }

      temp = GeneralQueue.rear;
      while (temp != nullptr)
      {
        if (flag)
        {
          if (temp->energy < 0)
          {
            temp->print();
            string name = temp->name;
            temp = temp->prev;
            GeneralQueue.removeFromQueue(name);
          }
          else
          {
            temp = temp->prev;
          }
        }
        if (!flag)
        {
          if (temp->energy > 0)
          {
            temp->print();
            string name = temp->name;
            temp = temp->prev;
            GeneralQueue.removeFromQueue(name);
          }
          else
          {
            temp = temp->prev;
          }
        }
      }

      while (CustomerQueue.size > 0)
      {
        customer* newCus = new customer(CustomerQueue.front->name, CustomerQueue.front->energy, nullptr, nullptr);
        CustomerQueue.dequeue();
        if (!this->RED(newCus, true, true))
        {
          CustomerQueue.addToFront(newCus);
          break;
        }
      }
    }

    void REVERSE()
    {
      if (size == 0) return;
      Stack positiveEnergy;
      Stack negativeEnergy;

      if (X->energy > 0) positiveEnergy.push(X);
      else if (X->energy < 0) negativeEnergy.push(X);
      string curName = X->name;
      customer* temp = X->prev;

      while (temp != X)
      {
        if (temp->energy > 0) positiveEnergy.push(temp);
        else if (temp->energy < 0) negativeEnergy.push(temp);
        temp = temp->prev;
      }

      if (X->energy > 0)
      {
        X->name = positiveEnergy.top->name;
        X->energy = positiveEnergy.top->energy;
        positiveEnergy.pop();
      }
      else if (X->energy < 0)
      {
        X->name = negativeEnergy.top->name;
        X->energy = negativeEnergy.top->energy;
        negativeEnergy.pop();
      };

      temp = X->prev;
      while (temp != X)
      {
        if (temp->energy > 0)
        {
          temp->name = positiveEnergy.top->name;
          temp->energy = positiveEnergy.top->energy;
          positiveEnergy.pop();
        }
        else if (temp->energy < 0)
        {
          temp->name = negativeEnergy.top->name;
          temp->energy = negativeEnergy.top->energy;
          negativeEnergy.pop();
        };
        temp = temp->prev;
      }

      while (X->name != curName)
      {
        X = X->next;
      }

      // Delete Stack
      positiveEnergy.deleteStack();
      negativeEnergy.deleteStack();
    }

    void PURPLE()
    {
      int N = CustomerQueue.PURPLE();
      // Testing
      // customer* temp = CustomerQueue.front;
      // cout << "TESTING PURPLE" << endl;
      // while (temp != nullptr)
      // {
      //   temp->print();
      //   temp = temp->next;
      // }

      BLUE(N % MAXSIZE);
    }


  };

  Seat customerSeat;

  imp_res(){};
  ~imp_res()
  {
    customerSeat.CustomerQueue.deleteQueue();
    customerSeat.GeneralQueue.deleteQueue();
    customerSeat.deleteSeat();
  }

  void RED(string name, int energy)
  {
    // cout << name << " " << energy << endl;
    customer *cus = new customer(name, energy, nullptr, nullptr);
    customerSeat.RED(cus);
  }
  void BLUE(int num)
  {
    // cout << "blue " << num << endl;
    customerSeat.BLUE(num);
  }
  void PURPLE()
  {
    // cout << "purple" << endl;
    customerSeat.PURPLE();
  }
  void REVERSAL()
  {
    // cout << "reversal" << endl;
    customerSeat.REVERSE();
  }
  void UNLIMITED_VOID()
  {
    // cout << "unlimited_void" << endl;
    customerSeat.UNLIMITED_VOID();
  }
  void DOMAIN_EXPANSION()
  {
    // cout << "domain_expansion" << endl;
    customerSeat.DOMAIN_EXPANSION();
  }
  void LIGHT(int num)
  {
    // cout << "light " << num << endl;
    customerSeat.LIGHT(num);
    // DEBUGGING
    // if (num == 1)
    // {
    //   cout << "DEBUGGING GENERAL QUEUE: \n";
    //   customer* temp = customerSeat.GeneralQueue.front;
    //   while (temp != nullptr)
    //   {
    //     temp->print();
    //     temp = temp->next;
    //   }
    //   cout << "DEBUGGING GENERAL QUEUE\n";
    // }
    // DEBUGGING
  }
};
