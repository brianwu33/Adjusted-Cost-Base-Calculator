#ifndef _HISTORY_TRANSACTION_CPP_
#define _HISTORY_TRANSACTION_CPP_

#include <cassert>
#include <iomanip>
#include <iostream>

#include "project4.hpp"
#include "History.hpp"
#include "Transaction.hpp"

////////////////////////////////////////////////////////////////////////////////
// Definitions for Transaction class
////////////////////////////////////////////////////////////////////////////////
//
//

// Constructor
// TASK 1
Transaction::Transaction( std::string ticker_symbol,  unsigned int day_date,
		unsigned int month_date,  unsigned year_date,
		bool buy_sell_trans,  unsigned int number_shares,
		double trans_amount){
	symbol = ticker_symbol;
	day = day_date;
	month = month_date;
	year = year_date;
	shares = number_shares;
	amount = trans_amount;
	if(buy_sell_trans){
		trans_type = "Buy";
	}else{
		trans_type = "Sell";
	}
	trans_id = assigned_trans_id;
	assigned_trans_id++;
	acb = 0.0;
	share_balance = 0;
	acb_per_share = 0.0;
	cgl = 0.0;
	p_next = nullptr;
}
//


// Destructor
// TASK 1
Transaction::~Transaction(){
}
//

// Overloaded < operator.
// TASK 2

bool Transaction::operator<( Transaction const &other ){
	//this : left
	//other : right

	if(this->year < other.get_year()){
		return true;
	}
	else if((this->year == other.get_year()) && (this->month < other.get_month())){
		return true;
	}
	else if((this->year == other.get_year())&&(this->month == other.get_month())&&(this->day < other.get_day())){
		return true;
	}
	return false;
}
//

// GIVEN
// Member functions to get values.
//
std::string Transaction::get_symbol() const {
	return symbol;
}
unsigned int Transaction::get_day() const {
	return day;
}
unsigned int Transaction::get_month() const {
	return month;
}
unsigned int Transaction::get_year() const {
	return year;
}
unsigned int Transaction::get_shares() const {
	return shares;
}
double Transaction::get_amount() const {
	return amount;
}
double Transaction::get_acb() const {
	return acb;
}
double Transaction::get_acb_per_share() const {
	return acb_per_share;
}
unsigned int Transaction::get_share_balance() const {
	return share_balance;
}
double Transaction::get_cgl() const {
	return cgl;
}
bool Transaction::get_trans_type() const {
	return (trans_type == "Buy") ? true: false ;
}
unsigned int Transaction::get_trans_id() const {
	return trans_id;
}
Transaction *Transaction::get_next() {
	return p_next;
}

// GIVEN
// Member functions to set values.
//
void Transaction::set_acb( double acb_value ) {
	acb = acb_value;
}
void Transaction::set_acb_per_share( double acb_share_value ) {
	acb_per_share = acb_share_value;
}
void Transaction::set_share_balance( unsigned int bal ) {
	share_balance = bal ;
}
void Transaction::set_cgl( double value ) {
	cgl = value;
}
void Transaction::set_next( Transaction *p_new_next ) {
	p_next = p_new_next;
}

// GIVEN
// Print the transaction.
//
void Transaction::print() {
	std::cout << std::fixed << std::setprecision(2);
	std::cout << std::setw(4) << get_trans_id() << " "
			<< std::setw(4) << get_symbol() << " "
			<< std::setw(4) << get_day() << " "
			<< std::setw(4) << get_month() << " "
			<< std::setw(4) << get_year() << " ";


	if ( get_trans_type() ) {
		std::cout << "  Buy  ";
	} else { std::cout << "  Sell "; }

	std::cout << std::setw(4) << get_shares() << " "
			<< std::setw(10) << get_amount() << " "
			<< std::setw(10) << get_acb() << " " << std::setw(4) << get_share_balance() << " "
			<< std::setw(10) << std::setprecision(3) << get_acb_per_share() << " "
			<< std::setw(10) << std::setprecision(3) << get_cgl()
			<< std::endl;
}


////////////////////////////////////////////////////////////////////////////////
// Definitions for the History class
////////////////////////////////////////////////////////////////////////////////
//
//


// Constructor
// TASK 3
History::History(){
	p_head = nullptr;
}
//


// Destructor
// TASK 3
History::~History(){
//	Transaction* p_temp1 = p_head;
//	Transaction* p_temp2 = p_head;
//	while(p_temp1 != nullptr){
//		p_temp1 = p_temp2->get_next();
//		delete p_temp2;
//		p_temp2 = nullptr;
//		p_temp2 = p_temp1;
//	}
	while(p_head != nullptr){
		Transaction *p_temp = p_head;
		p_head = p_head->get_next();
		delete p_temp;
		p_temp = nullptr;
	}
}
//


// read_transaction(...): Read the transaction history from file.
// TASK 4
void History::read_history(){
	ece150::open_file();
	while(ece150::next_trans_entry()){
		Transaction *p_newtran = new Transaction(ece150::get_trans_symbol(),
				ece150::get_trans_day(),
				ece150::get_trans_month(),
				ece150::get_trans_year(),
				ece150::get_trans_type(),
				ece150::get_trans_shares(),
				ece150::get_trans_amount());
		this->insert(p_newtran);
	}
	ece150::close_file();
}
//

// insert(...): Insert transaction into linked list.
// TASK 5
void History::insert(Transaction *p_new_trans){
	if(p_head == nullptr){
		p_head = p_new_trans;
	}
	else{
		Transaction *p_temp {p_head};

		while(p_temp->get_next() != nullptr){
			p_temp = p_temp->get_next();
		}
		p_temp->set_next(p_new_trans);
	}
}
//


// sort_by_date(): Sort the linked list by trade date.
// TASK 6
void History::sort_by_date(){
	//check if the list is empty or just one node
	Transaction *p_sorted = nullptr;
	if((p_head == nullptr )||(p_head->get_next() == nullptr)){
		return;
	}else{
		//step 2
		p_sorted = p_head;
		p_head = p_head->get_next();
		p_sorted->set_next(nullptr);
		//step 3
		while(p_head != nullptr){
			//step 3
			Transaction *p_temp = p_head;
			p_head = p_head->get_next();
			p_temp->set_next(nullptr);
			//step4
			if(*p_temp < *p_sorted){
				p_temp->set_next(p_sorted);
				p_sorted = p_temp;
			}
			else{
				Transaction *p_insert = p_sorted;
				while ((p_insert->get_next() != nullptr) && (*p_insert->get_next() < *p_temp)) {
					p_insert = p_insert->get_next();
				}
				p_temp->set_next(p_insert->get_next());
				p_insert->set_next(p_temp);
			}
		}
		p_head = p_sorted;
	}
}
//


// update_acb_cgl(): Updates the ACB and CGL values.
// TASK 7
void History::update_acb_cgl(){
	int total_share_balance = 0;
	double ACB_total = 0.0;
	double ACB_per_share = 0.0;
	Transaction *p_temp {p_head};
	while(p_temp != nullptr){
		//BUY
		if(p_temp->get_trans_type()){
			//set ACB
			ACB_total +=p_temp->get_amount();
			p_temp->set_acb(ACB_total);

			//set share balance
			total_share_balance += p_temp->get_shares();
			p_temp->set_share_balance(total_share_balance);

			//set ACB/shares
			ACB_per_share = ACB_total/total_share_balance;
			p_temp->set_acb_per_share(ACB_per_share);

			//set capital gain/loss
			p_temp->set_cgl(0);

		}else{
			//SELL
			//SET ACB
			ACB_total -= p_temp->get_shares() * ACB_per_share;
			p_temp->set_acb(ACB_total);

			//Set share Balance
			total_share_balance -= p_temp->get_shares();
			p_temp->set_share_balance(total_share_balance);

			//SET ACB/SHARE (does not change)
			p_temp->set_acb_per_share(ACB_per_share);

			//set cgl
			double cgl = p_temp->get_amount() - (p_temp->get_shares()*ACB_per_share);
			p_temp->set_cgl(cgl);
		}
		p_temp = p_temp->get_next();
	}

}
//



// compute_cgl(): )Compute the ACB, and CGL.
// TASK 8

double History::compute_cgl(unsigned int year){
	double total_cgl = 0;
	Transaction *p_temp = p_head;
	while(p_temp != nullptr){
		if(p_temp->get_year() == year){
			total_cgl += p_temp->get_cgl();
		}
		p_temp = p_temp->get_next();
	}
	return total_cgl;
}




// print() Print the transaction history.
//TASK 9
void History::print(){
	std::cout<<"========== BEGIN TRANSACTION HISTORY ============"<<std::endl;
	Transaction *p_temp {p_head};
	while(p_temp != nullptr){
		p_temp->print();
		p_temp = p_temp->get_next();
	}
	std::cout<<"========== END TRANSACTION HISTORY ============"<<std::endl;
}
//
void Linked_list::rotate(){
	Node *p_old_list_head{p_list_head};
	p_list_head = p_list_head->p_next_node_;

	Node *p_temp{p_list_head};
	while(p_temp->p_next_node_ != nullptr){
		p_temp = p_temp->p_next_node;
	}
	p_temp->p_next_node_ = p_old_list_node_;
	p_old_list_node_->p_next_node = nullptr;

}



// GIVEN
// get_p_head(): Full access to the linked list.
//
Transaction *History::get_p_head() { return p_head; }


#endif
