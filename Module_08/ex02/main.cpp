/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 00:00:00 by copilot           #+#    #+#             */
/*   Updated: 2026/05/15 13:13:16 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <list>
#include <stack>
#include <string>

#include "MutantStack.hpp"

/**
 * @brief Prints a visual separator for a test section.
 *
 * @param title Section title to display.
 */
static void print_section(const std::string &title)
{
	std::cout << "\n=== " << title << " ===" << std::endl;
}

/**
 * @brief Prints whether a check passed or failed.
 *
 * @param label Name of the check.
 * @param ok True when the check passed.
 */
static void print_check(const std::string &label, bool ok)
{
	std::cout << (ok ? "[OK] " : "[FAIL] ") << label << std::endl;
}

/**
 * @brief Compares two integer values and prints the result.
 *
 * @param label Name of the check.
 * @param actual Value obtained during the test.
 * @param expected Reference value.
 * @return True when both values are equal.
 */
static bool expect_equal(const std::string &label, int actual, int expected)
{
	const bool ok = (actual == expected);
	std::cout << label << ": " << actual << " (expected " << expected << ")" << std::endl;
	print_check(label, ok);
	return ok;
}

/**
 * @brief Checks the top element of a MutantStack against an expected value.
 *
 * @param label Name of the check.
 * @param stack Stack under test.
 * @param expected Expected top value.
 * @return True when the stack is not empty and the top value matches.
 */
static bool expect_top(const std::string &label, const MutantStack<int> &stack, int expected)
{
	const bool ok = (!stack.empty() && stack.top() == expected);
	std::cout << label << ": top=" << stack.top() << " (expected " << expected << ")" << std::endl;
	print_check(label, ok);
	return ok;
}

/**
 * @brief Verifies that the stack iterates in the expected order.
 *
 * @param label Name of the check.
 * @param stack Stack under test.
 * @param expected Array containing the expected values.
 * @param count Number of expected elements.
 * @return True when iteration matches the expected sequence.
 */
static bool expect_sequence(const std::string &label, const MutantStack<int> &stack, const int *expected, std::size_t count)
{
	std::size_t index = 0;
	MutantStack<int>::const_iterator it = stack.begin();
	MutantStack<int>::const_iterator ite = stack.end();
	bool ok = true;

	std::cout << label << ":" << std::endl;
	for (; it != ite; ++it, ++index)
	{
		std::cout << "  [" << index << "] " << *it << std::endl;
		if (index >= count || *it != expected[index])
			ok = false;
	}
	if (index != count)
		ok = false;
	print_check(label, ok);
	return ok;
}

/**
 * @brief Compares a MutantStack against a std::list reference container.
 *
 * @param label Name of the check.
 * @param stack Stack under test.
 * @param reference Reference list that mirrors the stack operations.
 * @return True when both containers contain the same values in the same order.
 */
static bool compare_stack_with_list(const std::string &label, const MutantStack<int> &stack, const std::list<int> &reference)
{
	MutantStack<int>::const_iterator stack_it = stack.begin();
	MutantStack<int>::const_iterator stack_end = stack.end();
	std::list<int>::const_iterator list_it = reference.begin();
	std::list<int>::const_iterator list_end = reference.end();
	std::size_t index = 0;
	bool ok = (stack.size() == reference.size());

	std::cout << label << ":" << std::endl;
	while (stack_it != stack_end && list_it != list_end)
	{
		std::cout << "  [" << index << "] stack=" << *stack_it << " | list=" << *list_it << std::endl;
		if (*stack_it != *list_it)
			ok = false;
		++stack_it;
		++list_it;
		++index;
	}
	if (stack_it != stack_end || list_it != list_end)
		ok = false;
	print_check(label, ok);
	return ok;
}

/**
 * @brief Validates the empty-state behavior of MutantStack.
 *
 * @return True when all empty-state checks pass.
 */
static bool test_empty_state()
{
	bool ok = true;
	std::list<int> reference;
	MutantStack<int> stack;

	print_section("Empty stack");
	ok &= expect_equal("Initial size", static_cast<int>(stack.size()), 0);
	ok &= expect_equal("Initial list size", static_cast<int>(reference.size()), 0);
	print_check("Initial empty state", stack.empty());
	print_check("Initial list empty state", reference.empty());
	ok &= compare_stack_with_list("Empty comparison", stack, reference);
	return ok;
}

/**
 * @brief Exercises push, pop, top and size behavior.
 *
 * @param stack Stack reused across the rest of the tests.
 * @param reference List that mirrors the stack contents.
 * @return True when all push/pop checks pass.
 */
static bool test_push_pop_behavior(MutantStack<int> &stack, std::list<int> &reference)
{
	bool ok = true;

	print_section("Push, top and pop");
	stack.push(5);
	reference.push_back(5);
	stack.push(17);
	reference.push_back(17);
	ok &= expect_equal("Size after two pushes", static_cast<int>(stack.size()), 2);
	ok &= expect_equal("List size after two pushes", static_cast<int>(reference.size()), 2);
	ok &= expect_top("Top after pushes", stack, 17);
	std::cout << "List back after pushes: " << reference.back() << " (expected 17)" << std::endl;
	print_check("List back after pushes", reference.back() == 17);
	ok &= compare_stack_with_list("Comparison after two pushes", stack, reference);

	stack.pop();
	reference.pop_back();
	ok &= expect_equal("Size after pop", static_cast<int>(stack.size()), 1);
	ok &= expect_equal("List size after pop", static_cast<int>(reference.size()), 1);
	ok &= expect_top("Top after pop", stack, 5);
	std::cout << "List back after pop: " << reference.back() << " (expected 5)" << std::endl;
	print_check("List back after pop", reference.back() == 5);
	ok &= compare_stack_with_list("Comparison after pop", stack, reference);

	stack.push(3);
	reference.push_back(3);
	stack.push(5);
	reference.push_back(5);
	stack.push(737);
	reference.push_back(737);
	stack.push(0);
	reference.push_back(0);
	ok &= expect_equal("Size after full sequence", static_cast<int>(stack.size()), 5);
	ok &= expect_equal("List size after full sequence", static_cast<int>(reference.size()), 5);
	ok &= expect_top("Top after full sequence", stack, 0);
	std::cout << "List back after full sequence: " << reference.back() << " (expected 0)" << std::endl;
	print_check("List back after full sequence", reference.back() == 0);
	ok &= compare_stack_with_list("Comparison after full sequence", stack, reference);
	return ok;
}

/**
 * @brief Verifies iterator traversal and compares it with std::list.
 *
 * @param stack Stack under test.
 * @param reference Reference list with the same values.
 * @return True when iterator traversal matches the list order.
 */
static bool test_iterators(const MutantStack<int> &stack, const std::list<int> &reference)
{
	bool ok = true;

	print_section("Iterator traversal");
	{
		const int expected[] = {5, 3, 5, 737, 0};
		ok &= expect_sequence("Forward iteration", stack, expected, 5);
		ok &= compare_stack_with_list("Iterator comparison with list", stack, reference);
	}

	print_section("Const iterator traversal");
	{
		const MutantStack<int> &const_stack = stack;
		std::size_t index = 0;
		const int expected[] = {5, 3, 5, 737, 0};
		bool section_ok = true;

		for (MutantStack<int>::const_iterator it = const_stack.begin(); it != const_stack.end(); ++it, ++index)
		{
			std::cout << "  [" << index << "] " << *it << std::endl;
			if (index >= 5 || expected[index] != *it)
				section_ok = false;
		}
		if (index != 5)
			section_ok = false;
		print_check("Const iteration", section_ok);
		ok &= section_ok;
		ok &= compare_stack_with_list("Const iterator comparison with list", const_stack, reference);
	}
	return ok;
}

/**
 * @brief Validates the copy constructor and assignment operator.
 *
 * @param stack Source stack.
 * @param reference Reference list that mirrors the source stack.
 * @return True when copies behave independently and preserve the same values.
 */
static bool test_copy_and_assignment(const MutantStack<int> &stack, const std::list<int> &reference)
{
	bool ok = true;

	print_section("Copy constructor and assignment");
	MutantStack<int> copy(stack);
	std::list<int> reference_copy(reference);
	ok &= expect_equal("Copy size", static_cast<int>(copy.size()), 5);
	ok &= expect_equal("Copy list size", static_cast<int>(reference_copy.size()), 5);
	ok &= expect_top("Copy top", copy, 0);
	std::cout << "Copy list back: " << reference_copy.back() << " (expected 0)" << std::endl;
	print_check("Copy list back", reference_copy.back() == 0);
	ok &= compare_stack_with_list("Copy comparison with list", copy, reference_copy);

	copy.pop();
	reference_copy.pop_back();
	copy.push(42);
	reference_copy.push_back(42);
	ok &= expect_top("Copy modified top", copy, 42);
	std::cout << "Copy list modified back: " << reference_copy.back() << " (expected 42)" << std::endl;
	print_check("Copy list modified back", reference_copy.back() == 42);
	ok &= expect_top("Original top unchanged", stack, 0);
	ok &= compare_stack_with_list("Copy comparison after modifications", copy, reference_copy);

	MutantStack<int> assigned;
	std::list<int> reference_assigned;
	assigned = stack;
	reference_assigned = reference;
	ok &= expect_equal("Assigned size", static_cast<int>(assigned.size()), 5);
	ok &= expect_equal("Assigned list size", static_cast<int>(reference_assigned.size()), 5);
	ok &= expect_top("Assigned top", assigned, 0);
	std::cout << "Assigned list back: " << reference_assigned.back() << " (expected 0)" << std::endl;
	print_check("Assigned list back", reference_assigned.back() == 0);
	ok &= compare_stack_with_list("Assigned comparison with list", assigned, reference_assigned);

	assigned.pop();
	reference_assigned.pop_back();
	assigned.push(99);
	reference_assigned.push_back(99);
	ok &= expect_top("Assigned modified top", assigned, 99);
	std::cout << "Assigned list modified back: " << reference_assigned.back() << " (expected 99)" << std::endl;
	print_check("Assigned list modified back", reference_assigned.back() == 99);
	ok &= expect_top("Original top still unchanged", stack, 0);
	ok &= compare_stack_with_list("Assigned comparison after modifications", assigned, reference_assigned);
	return ok;
}

/**
 * @brief Confirms that MutantStack remains compatible with std::stack.
 *
 * @param stack Stack under test.
 * @param reference Reference list used for comparison.
 * @return True when the std::stack construction and reference output are correct.
 */
static bool test_std_stack_compatibility(const MutantStack<int> &stack, const std::list<int> &reference)
{
	bool ok = true;
	std::stack<int> standard_stack(stack);

	print_section("std::stack compatibility");
	ok &= expect_equal("std::stack size", static_cast<int>(standard_stack.size()), 5);
	std::cout << "std::stack top: " << standard_stack.top() << " (expected 0)" << std::endl;
	print_check("std::stack top", standard_stack.top() == 0);
	std::cout << "std::list back: " << reference.back() << " (expected 0)" << std::endl;
	print_check("std::list back", reference.back() == 0);
	return ok;
}

/**
 * @brief Runs the full MutantStack test suite.
 *
 * @return 0 when all checks pass, 1 otherwise.
 */
int main()
{
	bool all_ok = true;
	std::list<int> reference;

	// Run each test section in order so the output stays readable.
	MutantStack<int> stack;
	all_ok &= test_empty_state();
	all_ok &= test_push_pop_behavior(stack, reference);
	all_ok &= test_iterators(stack, reference);
	all_ok &= test_copy_and_assignment(stack, reference);
	all_ok &= test_std_stack_compatibility(stack, reference);

	print_section("Final result");
	print_check("Overall status", all_ok);
	return all_ok ? 0 : 1;
}
