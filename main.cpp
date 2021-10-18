#include <iostream>
#include "History.hpp"
#include "Transaction.hpp"


#ifndef MARMOSET_TESTING
unsigned int Transaction::assigned_trans_id = 0;
int main() {
  History trans_history{};
  trans_history.read_history();

  Transaction * Tr1 {new Transaction {"VGRO",13,01,2018,true,1150,10300.140}};
  Transaction * Tr2 {new Transaction {"VGRO",13,01,2018,true,9150,10300.140}};
  Transaction * Tr3 {new Transaction {"VGRO",13,01,2018,true,1650,10300.140}};

  History main_history{};
  main_history.insert(Tr1);
  main_history.insert(Tr2);
  main_history.insert(Tr3);
  main_history.print();

  main_history.sort_by_date();
  main_history.print();

  std::cout << "[Starting history]:" << std::endl;
  trans_history.print();
  trans_history.sort_by_date();

  std::cout << "[Sorted          ]:" << std::endl;
  trans_history.print();

  trans_history.update_acb_cgl();
  trans_history.print();

  std::cout << "[CGL for 2018    ]: " << trans_history.compute_cgl(2018) << std::endl;
  std::cout << "[CGL for 2019    ]: " << trans_history.compute_cgl(2019) << std::endl;

  return 0;
}
#endif
