/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 20:00:46 by pablo             #+#    #+#             */
/*   Updated: 2025/12/10 22:35:29 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Account.hpp"
#include <ctime>
#include <iostream>

// Definiciones de variables estáticas
int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

////////////////////////////////// CONSTRUCTOR ////////////////////////////////

Account::Account(int initial_deposit)
{
	_accountIndex = _nbAccounts;
	_amount = initial_deposit;
	_nbDeposits = 0;
	_nbWithdrawals = 0;
	_totalAmount += initial_deposit;
	Account::_displayTimestamp();
	std::cout << " index:" << _accountIndex << ";amount:" << _amount
	          << ";created" << std::endl;
	_nbAccounts++;
}

////////////////////////////////// DESTRUCTOR ////////////////////////////////

Account::~Account()
{
	Account::_displayTimestamp();
	std::cout << " index:" << _accountIndex << ";amount:" << _amount
	          << ";closed" << std::endl;
	_nbAccounts--;
	_totalAmount -= _amount;
}

///////////////////////////////////// GETTERS /////////////////////////////////

int Account::getNbAccounts()
{
	return _nbAccounts;
}

int Account::getTotalAmount()
{
	return _totalAmount;
}

int Account::getNbDeposits()
{
	return _totalNbDeposits;
}

int Account::getNbWithdrawals()
{
	return _totalNbWithdrawals;
}
//////////////////////////////////// HELPERS ///////////////////////////////////
/**
 * @brief Displays the current timestamp to the standard output.
 *
 * This private member function retrieves the current time, formats it into a
 * string in the format "[YYYYMMDD_HHMMSS]", and outputs it to std::cout. The
 * timestamp represents the local time at the moment the function is called.
 *
 * @note This function uses C-style time functions and assumes the system's
 * local time zone.
 */
void Account::_displayTimestamp()
{
	time_t now = time(0);
	tm *local_time = localtime(&now);
	char buffer[20];
	strftime(buffer, 20, "[%Y%m%d_%H%M%S]", local_time);
	std::cout << buffer;
}

/////////////////////////////////// FUNCTIONS //////////////////////////////////

/**
 * @brief Displays summary information for all accounts.
 *
 * This static method outputs the total number of accounts, the total amount
 * across all accounts, the total number of deposits, and the total number of
 * withdrawals to the standard output stream.
 */
void Account::displayAccountsInfos()
{
	Account::_displayTimestamp();
	std::cout << " accounts:" << _nbAccounts << ";total:" << _totalAmount
	          << ";deposits:" << _totalNbDeposits
	          << ";withdrawals:" << _totalNbWithdrawals << std::endl;
}

/**
 * @brief Processes a deposit into the account.
 *
 * This method updates the account's balance and deposit counters, displays a
 * timestamp, and prints the transaction details to the standard output.
 *
 * @param deposit The amount to be deposited (must be positive).
 */
void Account::makeDeposit(int deposit)
{
	Account::_displayTimestamp();
	std::cout << " index:" << _accountIndex << ";p_amount:" << _amount
	          << ";deposit:" << deposit << ";amount:" << (_amount + deposit)
	          << ";nb_deposits:" << (_nbDeposits + 1) << std::endl;
	++_nbDeposits;
	++_totalNbDeposits;
	_amount += deposit;
	_totalAmount += deposit;
}

/**
 * @brief Attempts to withdraw a specified amount from the account.
 *
 * This method checks if the withdrawal amount is less than or equal to the
 * current account balance. If sufficient funds are available, it performs the
 * withdrawal by updating the account's amount, incrementing the number of
 * withdrawals for this account and the total number of withdrawals across all
 * accounts, and displays the transaction details. If insufficient funds, it
 * refuses the withdrawal and displays a refusal message.
 *
 * @param withdrawal The amount to withdraw from the account.
 * @return true if the withdrawal is successful, false if refused due to
 * insufficient funds.
 */
bool Account::makeWithdrawal(int withdrawal)
{
	Account::_displayTimestamp();
	if (withdrawal > this->_amount)
	{
		std::cout << " index:" << _accountIndex << ";p_amount:" << _amount
				  << ";withdrawal:refused" << std::endl;
		return false;
	}
	std::cout << " index:" << _accountIndex << ";p_amount:" << _amount
			  << ";withdrawal:" << withdrawal
			  << ";amount:" << (_amount - withdrawal)
			  << ";nb_withdrawals:" << (_nbWithdrawals + 1) << std::endl;
	++_nbWithdrawals;
	++_totalNbWithdrawals;
	_amount -= withdrawal;
	_totalAmount -= withdrawal;
	return true;
}

/**
 * @brief Retrieves the current amount in the account.
 *
 * This method returns the value of the private member _amount, representing
 * the current balance or amount associated with the account.
 *
 * @return The current amount as an integer value.
 */
int Account::checkAmount() const
{
	return _amount;
}

void Account::displayStatus() const
{
	Account::_displayTimestamp();
	std::cout << " index:" << _accountIndex << ";amount:" << _amount
	          << ";deposits:" << _nbDeposits
	          << ";withdrawals:" << _nbWithdrawals << std::endl;
}
