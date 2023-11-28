import random
import time
import copy

#####################################################
#####################################################
# Please enter the number of hours you spent on this
# assignment here
num_hours_i_spent_on_this_assignment = 10
#####################################################
#####################################################

#####################################################
#####################################################
# Give one short piece of feedback about the course so far. What
# have you found most interesting? Is there a topic that you had trouble
# understanding? Are there any changes that could improve the value of the
# course to you? (We will anonymize these before reading them.)
#
# FEEDBACK:
# The units on logic have been interesting, in particular looking at logical
# sentences from the viewpoint of satisfiability and the way that logical
# clauses can be resolved to test for this.
#
# Probability has been a bit challenging, particularly probability distributions
# and Bayesian networks.
#
# As always, I seem to have trouble understanding algorithms when they are given
# in class. Maybe that's just me though. I usually need to step through an algorithm
# extremely slowly for the first time when trying to understand it.
#####################################################
#####################################################


# A clause consists of a set of symbols, each of which is negated
# or not. A clause where
# clause.symbols = {"a": 1, "b": -1, "c": 1}
# corresponds to the statement: a OR (NOT b) OR c .
class Clause:
    def __init__(self):
        pass

    def from_str(self, s):
        s = s.split()
        self.symbols = {}
        for token in s:
            if token[0] == "-":
                sign = -1
                symbol = token[1:]
            else:
                sign = 1
                symbol = token
            self.symbols[symbol] = sign

    def __str__(self):
        tokens = []
        for symbol,sign in self.symbols.items():
            token = ""
            if sign == -1:
                token += "-"
            token += symbol
            tokens.append(token)
        return " ".join(tokens)

# A SAT instance consists of a set of CNF clauses. All clauses
# must be satisfied in order for the SAT instance to be satisfied.
class SatInstance:
    def __init__(self):
        pass

    def from_str(self, s):
        self.symbols = set()
        self.clauses = []
        for line in s.splitlines():
            clause = Clause()
            clause.from_str(line)
            self.clauses.append(clause)
            for symbol in clause.symbols:
                self.symbols.add(symbol)
        self.symbols = sorted(self.symbols)

    def __str__(self):
        s = ""
        for clause in self.clauses:
            s += str(clause)
            s += "\n"
        return s

    # Takes as input an assignment to symbols and returns True or
    # False depending on whether the instance is satisfied.
    # Input:
    # - assignment: Dictionary of the format {symbol: sign}, where sign
    #       is either 1 or -1.
    # Output: True or False
    def is_satisfied(self, assignment):
        true_clauses = 0
        # For every clause in assignment, test if clause
        # is true. If number of true clauses = number of
        # clauses in instance, then instance is satisfied
        for clause in self.clauses:
            if true_clause(clause, assignment):
                true_clauses += 1
        if true_clauses == len(self.clauses):
            satisfied = True
        else:
            satisfied = False
        return satisfied


# Finds a satisfying assignment to a SAT instance,
# using the DPLL algorithm.
# Input: SAT instance
# Output: Dictionary of the format {symbol: sign}, where sign
#         is either 1 or -1.
def solve_dpll(instance):
    # Create empty assignment model and call helper DPLL method
    assignment = {}
    dpll(instance.clauses, instance.symbols, assignment)
    return assignment


# Recursive helper method for solve_dpll
def dpll(clauses, symbols, model):
    # Check if instance is satisfied under current model;
    # if satisfied, return True
    instance = SatInstance()
    instance.clauses = clauses
    instance.symbols = symbols
    if instance.is_satisfied(model):
        return True
    # Check if current model leads to any clause in the instance
    # being false; if so, model is false, so return False
    elif model_false(clauses, model):
        return False
    # Search for a pure symbol under current conditions
    p = find_pure_symbol(symbols, clauses, model)
    # If pure symbol exists, remove it from list of symbols,
    # and update model with that symbol and its truth value
    if p:
        symbols.remove(p[0])
        model.update({p[0]: p[1]})
        # Call dpll with the new model and symbol list;
        # if dpll returns true, then assignment is correct,
        # so return True; else undo the assignment and restore
        # that symbol to list of symbols, and return False
        if dpll(clauses, symbols, model):
            return True
        else:
            del model[p[0]]             # Remove assignment from model
            symbols.append(p[0])        # Restore symbol to list of symbols
            return False
    # Search for unit clause under current conditions
    p = find_unit_clause(clauses, model)
    # If unit clause exists, remove that symbol from list of
    # symbols and update model with that symbol and its truth value
    if p:
        symbols.remove(p[0])
        model.update({p[0]: p[1]})
        # Call dpll with the new model and symbol list;
        # if dpll returns true, then assignment is correct,
        # so return True; else undo the assignment and restore
        # that symbol to list of symbols, and return False
        if dpll(clauses, symbols, model):
            return True
        else:
            del model[p[0]]             # Remove assignment from model
            symbols.append(p[0])        # Restore symbol to list of symbols
            return False
    # If unassigned symbols remain, remove first symbol from list
    # and test both possible assignments for it
    if symbols:
        p = symbols.pop(0);
        # Assign symbol as "true" and call dpll with this assignment;
        # if dpll returns true, then model is correct, so return
        # True; else test assignment of "false"
        model.update({p: 1})
        if dpll(clauses, symbols, model):
            return True
        else:
            model[p] = -1
            # If assignment returns true, model is correct, so return True;
            # else undo the assignment and restore that symbols to list of
            # symbols, and return False
            if dpll(clauses, symbols, model):
                return True
            else:
                del model[p]            # Remove assignment from model
                symbols.append(p)       # Restore symbol to list of symbols
                return False


# Finds a unit clause under current assignment model
# Input:
#   - clauses: List of Clause objects
#   - model: Dictionary consisting of current assignments
# Output: Unit clause, if found, as List of format [symbol, value];
# if no unit clause found, outputs None
def find_unit_clause(clauses, model):
    # For all clauses, test if clause is unit clause
    for clause in clauses:
        a_true_literal = False
        false_literals = 0
        # If clause consists of only one symbol, it is a unit clause, so return it
        if len(clause.symbols) == 1:
            for key, value in clause.symbols.items():
                unit_clause = [key, value]
            return unit_clause
        # For all symbols in the clause, check if symbol has assignment in model,
        # and if that assignment makes it true in the clause, or false
        for symbol in clause.symbols:
            if symbol in model:
                if clause.symbols[symbol] == model[symbol]:
                    a_true_literal = True
                else:
                    false_literals += 1
            # If symbol not in assignment, it may be unit clause if all other
            # literals are false under the assignment
            else:
                possible_unit_clause = [symbol, clause.symbols[symbol]]
        # If no true literal found under the assignment, and all symbols in
        # clause assigned false except one, then return that symbol as unit clause
        if not a_true_literal and false_literals == (len(clause.symbols) - 1):
            return possible_unit_clause


# Finds pure symbol under current assignment model
# Inputs:
#   - symbols: list of unassigned symbols
#   - clauses: list of Clause objects
#   - model: current assignment model
# Output: Pure symbol, if found, as List of format [symbol, sign];
# returns None if no pure symbol found
def find_pure_symbol(symbols, clauses, model):
    # For every unassigned symbol, test if symbol is pure
    for symbol in symbols:
        pure = True
        first_instance = True
        symbol_found = False
        # For every clause in the instance, if clause is not already true,
        # check if clause contains the symbol
        for clause in clauses:
            clause_true = true_clause(clause, model)
            if not clause_true and symbol in clause.symbols:
                symbol_found = True
                # Get sign of symbol
                sign = clause.symbols[symbol]
                # If this is first time symbol is encountered in a clause,
                # create a check-value from its sign to check against all
                # future occurrences of the symbol
                if first_instance:
                    sign_check = sign
                first_instance = False
                # If an occurrence of the symbol is found that does not match
                # the sign of an earlier occurrence, then the symbol is not a
                # pure symbol; set pure = False, and break inner for-loop to
                # test purity of next symbol in list
                if sign != sign_check:
                    pure = False
                    break
        # If pure symbol found, return pure symbol
        if symbol_found and pure:
            return [symbol, sign]


# Tests is a clause is true; that is, if at least one literal is true
# under the current assignment model.
# Inputs:
#   - clause: Clause object to test
#   - model: current assignment model
# Outputs:
#   - True if at least one literal in clause is true under model
#   - False if no literal is true under current model or if truth
#   of clause cannot be determined from current model due to incomplete
#   assignment (symbols in clause that are not yet assigned)
def true_clause(clause, model):
    clause_truth = False
    # For all symbols in clause, if symbol has an assignment that
    # makes it true in clause, then clause is true; break loop and return True
    for symbol in clause.symbols:
        if symbol in model:
            if clause.symbols[symbol] == model[symbol]:
                clause_truth = True
                break
    return clause_truth


# Tests if current assignment model is false; if any clause of instance is false
# under the assignment model, then the model cannot satisfy the instance
# Inputs:
#   - clauses: List of Clause objects in instance
#   - model: Dictionary of format {symbol: sign} consisting of current assignments
# Outputs:
#   - True if a false clause found
#   - False if no false clause found; an undetermined clause is not considered false
def model_false(clauses, model):
    false_model = False
    # For all clauses, search for some symbol in clause that has an assignment that
    # makes the clause true; if no such symbol found and all symbols in clause have
    # assignment, then clause is false
    for clause in clauses:
        false_clause = True
        # Tally how many symbols in clause have an assignment
        symbols_in_model = 0
        for symbol in clause.symbols:
            if symbol in model:
                symbols_in_model += 1
                # If true literal found under assignment, clause not false
                if clause.symbols[symbol] == model[symbol]:
                    false_clause = False
                    break
        # If not all symbols in clause have an assignment, clause not false
        if symbols_in_model != len(clause.symbols):
            false_clause = False
        # If a false clause was found, then model is false
        if false_clause:
            false_model = True
            break
    return false_model


with open("big_instances.txt", "r") as input_file:
    instance_strs = input_file.read()

instance_strs = instance_strs.split("\n\n")

with open("big_assignments.txt", "w") as output_file:
    for instance_str in instance_strs:
        if instance_str.strip() == "":
            continue
        instance = SatInstance()
        instance.from_str(instance_str)
        assignment = solve_dpll(instance)
        for symbol_index, (symbol,sign) in enumerate(assignment.items()):
            if symbol_index != 0:
                output_file.write(" ")
            token = ""
            if sign == -1:
                token += "-"
            token += symbol
            output_file.write(token)
        output_file.write("\n")
















