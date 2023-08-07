#include <bits/stdc++.h>

using namespace std;

class Items {
  private: string name;
  float price;
  public: Items(string nam, float p) {
    name = nam;
    price = p;
  }
  string getName() {
    return name;
  }
  void updatePrice(float p) {
    price = p;
  }
  float getPrice() {
    return price;
  }
  friend class Waiter;
};

class Menu {
  private: vector < Items > menuList;
  public: void addItem(const Items & item) {
    menuList.push_back(item);
  }
  void displayMenu() {
    cout << "\nMenu:\n";
    for (int i = 0; i < menuList.size(); i++) {
      cout << i + 1 << ". " << menuList[i].getName() << " - " << menuList[i].getPrice() << " TK\n";
    }
  }
  void changeItemPrice(const string & itemName) {
    int chk = 0;
    for (int i = 0; i < menuList.size(); i++) {
      if (menuList[i].getName() == itemName) {
        float newPrice;
        cout << "The updated price: ";
        cin >> newPrice;
        menuList[i].updatePrice(newPrice);
        chk = 1;
        cout << "Price Updated Successfully for " << itemName << "!" << endl;
        break;
      }
    }
    if (chk == 0) {
      cout << "No items with name " << itemName << endl;
    }
  }
  void addNewItem(const Items & newItem) {
    menuList.push_back(newItem);
  }
  friend class Waiter;
  friend class Manager;
};

class Manager {
  private: Menu & menu;
  protected: float totalSales = 0;
  float waiterSalary = 0;
  public: Manager(Menu & menu): menu(menu) {}
  void changeItemPrice(string & itemName) {
    menu.changeItemPrice(itemName);
  }
  void addNewItem(const Items & newItem) {
    menu.addNewItem(newItem);
  }
  void displaytotalSales() {
    cout << "\nTotal sales is " << totalSales << " TK" << endl;
  }
  void showwaiterSalary() {
    cout << "\nWaiter's today's salary is " << waiterSalary << " TK" << endl;
  }
  friend class Waiter;
};

class Waiter {
  private: vector < Items > orders;
  const Menu & menu;
  public: Waiter(const Menu & m): menu(m) {}
  void placeOrder(Manager & manager) {
    int itemNo;
    while (true) {
      cout << "Enter item number to add to order (0 to finish): ";
      cin >> itemNo;
      if (itemNo > 0 && itemNo <= menu.menuList.size()) {
        orders.push_back(menu.menuList[itemNo - 1]);
        manager.totalSales += menu.menuList[itemNo - 1].price;
        manager.waiterSalary += (menu.menuList[itemNo - 1].price * 0.05);
      }else if(itemNo==0){
        break;
      } else {
        cout << "Invalid item number. Try again.\n";
      }

    }
  }
  friend void payReceipt(Waiter& waitertemp);
};

void payReceipt(Waiter& waitertemp) {
  if (waitertemp.orders.size() == 0) {
    cout << "No Orders given yet!!" << endl;
  } else {
    float total = 0.0;
    cout << "\nOrder:\n";
    for(int i=0;i<waitertemp.orders.size();i++){
      cout << waitertemp.orders[i].getName() << " - TK " << waitertemp.orders[i].getPrice() << "\n";
      total += waitertemp.orders[i].getPrice();
    }
    cout << "Total: TK " << total << "\n";
  }
}

int main() {
  Menu menu1;
  Waiter waiter(menu1);
  Manager manager(menu1);
  menu1.addItem(Items("Vaat-Dim", 40));
  menu1.addItem(Items("Vaat-Murgi", 50));
  cout << "\n\t\t#### SIUUU HOTEL ####" << endl << endl;
  int mainNum;
  welcomeTasks:
    cout << "\nWelcome to Siuuu Hotel..." << endl;
  do {
    cout << "1. Check the menu." << endl;
    cout << "2. Place an order." << endl;
    cout << "3. Get the receipt." << endl;
    cout << "4. I am the manager." << endl;
    cout << "5. Exit " << endl;
    cout << "\nEnter response: ";
    cin >> mainNum;
    if (mainNum == 1) {
      menu1.displayMenu();
    } else if (mainNum == 2) {
      menu1.displayMenu();
      waiter.placeOrder(manager);
    } else if (mainNum == 3) {
      payReceipt(waiter);
    } else if (mainNum == 4) {
      int managerNum;
      do {
        invalidManager: string userName,
        pass;
        cout << "\nEnter the username: ";
        cin >> userName;
        cout << "Enter the password: ";
        cin >> pass;
        if (pass == "77777" && userName == "Ronaldo") {
          managerTasks: cout << "\n\n\tWelcome Boss ^_^\n" << endl;
          cout << "1. Change the price of an existing item." << endl;
          cout << "2. Add a new item to the menu." << endl;
          cout << "3. Total Sales." << endl;
          cout << "4. Waiter's salary today." << endl;
          cout << "5. Back to main menu." << endl;
          cout << "\nEnter response: ";
          cin >> managerNum;

          if (managerNum == 1) {
            menu1.displayMenu();
            cout << "\nEnter the item's name: ";
            string findName;
            cin >> findName;
            manager.changeItemPrice(findName);
          } else if (managerNum == 2) {
            menu1.displayMenu();
            string newName;
            float newPrice;
            cout << "\nEnter new item's name: ";
            cin >> newName;
            cout << "Enter new item's price: ";
            cin >> newPrice;
            manager.addNewItem(Items(newName, newPrice));
            cout << "Successfully added " << newName << " to the menu!" << endl;
          } else if (managerNum == 3) {
            manager.displaytotalSales();
          } else if (managerNum == 4) {
            manager.showwaiterSalary();
          } else if (managerNum == 5) {
            goto welcomeTasks;
          } else {
            cout << "Invalid Option!!!" << endl;
          }
          cout << "Do you want to continue?(Y/N): ";
          char res;
          cin >> res;
          if (res == 'n' || res == 'N') {
            goto endTask;
          } else {
            goto managerTasks;
          }
        }
        else {
          cout << "\nAccess denied!" << endl;
          cout << "\nDo you want to try again?(Y/N): ";
          char again;
          cin >> again;
          if (again == 'y' || again == 'Y') {
            goto invalidManager;
          } else {
            mainNum = 5;
            goto endTask;
          }
        }
      }
      while (managerNum != 3);
    } else if (mainNum == 5) {
      goto endTask;
    }
    cout << "Do you want to continue?(Y/N): ";
    char take;
    cin >> take;
    if (take == 'n' || take == 'N') {
      mainNum = 5;
    } else {
      goto welcomeTasks;
    }
    endTask:
      cout << "Come Again <3" << endl;
  }
  while (mainNum != 5);
  return 0;
}
