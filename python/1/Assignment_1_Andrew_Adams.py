import random
import copy
import time
import Queue
from collections import deque


# A node for storing puzzle-state objects of the search
class Node(object):
    def __init__(self, puzzle_state):
        self.state = puzzle_state           # The puzzle state
        self.moves_performed = []           # A list of moves performed so far
        self.total_estimated_cost = 0       # Estimated cost from initial state to current state to goal state
        self.last_move_cell = [0,0]         # The last move performed to arrive at this state

    # Store list of total moves so far, as well as last move made
    def add_move(self, all_moves, new_move):
        for i in range(0,len(all_moves)):
            self.moves_performed.append(all_moves[i])
        self.last_move_cell = new_move

    # Store total estimated cost (cost to reach current state plus estimated cost to goal)
    def add_cost(self, estimated_cost_to_goal):
        self.total_estimated_cost = len(self.moves_performed) + estimated_cost_to_goal


# Create a list of lists to represent rows and columns of puzzle
# Populate initially with zeros
def create_puzzle(rows, columns):
    puzzle = [[0] * columns for i in range(rows)]
    return puzzle


# Perform one move
def perform_move(puzzle, row, col):
    puzzle_copy = copy.deepcopy(puzzle)
    # Toggle specified cell
    toggle(puzzle_copy, row, col)
    # Check if cell is on top edge; if not, toggle cell above it
    if row != 0:
        toggle(puzzle_copy, row - 1, col)
    # Check if cell is on bottom edge; if not, toggle cell below it
    if row != len(puzzle_copy) - 1:
        toggle(puzzle_copy, row + 1, col)
    # Check if cell is on left edge; if not, toggle cell to its left
    if col != 0:
        toggle(puzzle_copy, row, col - 1)
    # Check if cell is on right edge; if not, toggle cell to its right
    if col != len(puzzle_copy[row]) - 1:
        toggle(puzzle_copy, row, col + 1)
    return puzzle_copy


# Toggle; if cell is a 1, change to 0, and vice versa
def toggle(puzzle, row, col):
    cell = puzzle[row][col]
    if cell == 0:
        puzzle[row][col] = 1
    else:
        puzzle[row][col] = 0


# Given row and column, return next cell, wrapping around
# to next row if at last column of row
def next_cell(row, col):
    if col == puzzle_columns - 1:
        next_cell_coord = [row + 1, 0]
    else:
        next_cell_coord = [row, col + 1]
    return next_cell_coord


# Scramble puzzle by randomly toggling cells
def scramble(puzzle):
    for i in range(0, len(puzzle)):
        for j in range(0, len(puzzle[i])):
            do_toggle = random.randint(0,1)
            if do_toggle == 1:
                puzzle = perform_move(puzzle, i, j)
    return puzzle


# Helper function for printing puzzle
def print_puzzle(puzzle):
    for i in range(0, len(puzzle)):
        for j in range(0, len(puzzle[i])):
            print puzzle[i][j],
        print


# Returns true if puzzle state is clear of all 1's
def is_solved(puzzle):
    solved = True
    for i in range(0, len(puzzle)):
        for j in range(0, len(puzzle[i])):
            if puzzle[i][j] == 1:
                solved = False
    return solved


# Breadth-first search algorithm
def breadth_first(puzzle):
    start_time = time.time()
    search_steps = 0
    frontier = deque()
    initial_puzzle = Node(puzzle)
    frontier.append(initial_puzzle)
    explored = []
    search_done = False
    current_cell = initial_puzzle.last_move_cell
    while not search_done:
        # Pop from left (FIFO) for current node to expand
        current_state = frontier.popleft()
        # Get cell where last move was performed for current puzzle state
        current_cell = current_state.last_move_cell
        # Unless performing first move, calculate next cell for next move
        if current_state != initial_puzzle:
            current_cell = next_cell(current_cell[0], current_cell[1])
        # Add current state to list of explored states
        explored.append(current_state.state)
        # Generate left and right "children" of current state
        # Left child is the state resulting from a move being performed at the next cell,
        # while right child is the result of not performing a move at the next cell
        left_child = Node(perform_move(current_state.state, current_cell[0], current_cell[1]))
        right_child = Node(current_state.state)
        # Update children states with list of moves performed and record of last move made
        right_child.add_move(current_state.moves_performed, current_cell)
        updated_move_list = current_state.moves_performed
        updated_move_list.append(current_cell)
        left_child.add_move(updated_move_list, current_cell)
        # Increment search steps
        search_steps += 1
        # Test is left child is solution; right child will not be solution because no move was performed.
        # Before testing, check if left child has been explored or is in frontier, both of which would
        # indicate it has already been tested
        if left_child.state not in explored and not any(x.state == left_child.state for x in frontier):
            if is_solved(left_child.state):
                search_done = True
                print "Search steps performed: ", search_steps
                # Add search steps to list of moves so it can be returned
                left_child.moves_performed.append(search_steps)
            # If left child is not solution, and if end of puzzle has not been reached,
            # then add left and right child to frontier
            elif current_cell != [puzzle_rows - 1, puzzle_columns - 1]:
                frontier.append(left_child)
                frontier.append(right_child)
    # Calculate total time spent and add it to move list so it can be returned
    end_time = time.time()
    total_time = end_time - start_time
    left_child.moves_performed.append(total_time)
    return left_child.moves_performed


# Depth-first search algorithm
# Note: Same as breadth-first, except that nodes are popped LIFO from the frontier;
# i.e., the last added, which will be the deepest, is expanded next
def depth_first(puzzle):
    start_time = time.time()
    search_steps = 0
    frontier = deque()
    initial_puzzle = Node(puzzle)
    frontier.append(initial_puzzle)
    explored = []
    search_done = False
    current_cell = initial_puzzle.last_move_cell
    while not search_done:
        # Pop from right (LIFO) for current node to expand
        current_state = frontier.pop()
        # Get cell where last move was performed for current puzzle state
        current_cell = current_state.last_move_cell
        # Unless performing first move, calculate next cell for next move
        if current_state != initial_puzzle:
            current_cell = next_cell(current_cell[0], current_cell[1])
        # Add current state to list of explored states
        explored.append(current_state.state)
        # Generate left and right "children" of current state
        # Left child is the state resulting from a move being performed at the next cell,
        # while right child is the result of not performing a move at the next cell
        left_child = Node(perform_move(current_state.state, current_cell[0], current_cell[1]))
        right_child = Node(current_state.state)
        # Update children states with list of moves performed and record of last move made
        right_child.add_move(current_state.moves_performed, current_cell)
        updated_move_list = current_state.moves_performed
        updated_move_list.append(current_cell)
        left_child.add_move(updated_move_list, current_cell)
        # Increment search steps
        search_steps += 1
        # Test is left child is solution; right child will not be solution because no move was performed.
        # Before testing, check if left child has been explored or is in frontier, both of which would
        # indicate it has already been tested
        if left_child.state not in explored and not any(x.state == left_child.state for x in frontier):
            if is_solved(left_child.state):
                search_done = True
                print "Search steps performed: ", search_steps
                # Add search steps to list of moves so it can be returned
                left_child.moves_performed.append(search_steps)
            # If left child is not solution, and if end of puzzle has not been reached,
            # then add left and right child to frontier
            elif current_cell != [puzzle_rows - 1, puzzle_columns - 1]:
                frontier.append(left_child)
                frontier.append(right_child)
    # Calculate total time spent and add it to move list so it can be returned
    end_time = time.time()
    total_time = end_time - start_time
    left_child.moves_performed.append(total_time)
    return left_child.moves_performed


# A* search algorithm;
# h(n) = number of lights remaining divided by 5
def a_star(puzzle):
    start_time = time.time()
    search_steps = 0
    frontier = []
    initial_puzzle = Node(puzzle)
    frontier.append(initial_puzzle)
    explored = []
    search_done = False
    current_cell = initial_puzzle.last_move_cell
    while not search_done:
        # Pop from front of list, which is sorted by lowest estimated cost first
        current_state = frontier.pop(0)
        # Get cell where last move was performed for current puzzle state
        current_cell = current_state.last_move_cell
        # Unless performing first move, calculate next cell for next move
        if current_state != initial_puzzle:
            current_cell = next_cell(current_cell[0], current_cell[1])
        # Add current state to list of explored states
        explored.append(current_state.state)
        # Generate left and right "children" of current state
        # Left child is the state resulting from a move being performed at the next cell,
        # while right child is the result of not performing a move at the next cell
        left_child = Node(perform_move(current_state.state, current_cell[0], current_cell[1]))
        right_child = Node(current_state.state)
        # Update children states with list of moves performed and record of last move made
        right_child.add_move(current_state.moves_performed, current_cell)
        updated_move_list = current_state.moves_performed
        updated_move_list.append(current_cell)
        left_child.add_move(updated_move_list, current_cell)
        # Estimate remaining path cost from children states to goal states,
        # and store this value in child nodes
        remaining_cost = estimate_cost_to_goal(left_child.state)
        left_child.add_cost(remaining_cost)
        remaining_cost = estimate_cost_to_goal(right_child.state)
        right_child.add_cost(remaining_cost)
        # Increment search steps
        search_steps += 1
        # Test is left child is solution; right child will not be solution because no move was performed.
        # Before testing, check if left child has been explored or is in frontier, both of which would
        # indicate it has already been tested
        if left_child.state not in explored and not any(x.state == left_child.state for x in frontier):
            if is_solved(left_child.state):
                search_done = True
                print "Search steps performed: ", search_steps
                # Add search steps to list of moves so it can be returned
                left_child.moves_performed.append(search_steps)
            # If left child is not solution, and if end of puzzle has not been reached,
            # then add left and right child to frontier
            elif current_cell != [puzzle_rows - 1, puzzle_columns - 1]:
                frontier.append(left_child)
                frontier.append(right_child)
                frontier.sort(key=lambda node: node.total_estimated_cost)
    # Calculate total time spent and add it to move list so it can be returned
    end_time = time.time()
    total_time = end_time - start_time
    left_child.moves_performed.append(total_time)
    return left_child.moves_performed


# Estimates remaining cost to goal state from a given state;
# estimated cost is number of lights remaining on in the puzzle
# (the number of 1's) divided by the maximum number of lights
# that can be turned off with a single move, which is 4
def estimate_cost_to_goal(puzzle_state):
    cost = 0
    for i in range(len(puzzle_state)):
        for j in range(len(puzzle_state[i])):
            if puzzle_state[i][j] == 1:
                cost += 1
    cost = cost / 5
    return cost


def main():
    # Define global variables for number of rows and columns,
    # for use in next_cell method (so that method can know the puzzle's size)
    global puzzle_rows
    global puzzle_columns
    hundred_puzzles = []
    total_moves = 0
    total_steps = 0
    total_time = 0
    # Create and scramble 100 puzzles and add to list of 100 puzzles
    for i in range(0,100):
        puzzle = scramble(create_puzzle(4,4))
        hundred_puzzles.append(puzzle)
    # Perform depth-first search and report statistics;
    # returned list will contain solution moves, plus
    # two additional values on end (total steps and total time)
    print "Performing depth-first search on 100 puzzles"
    for i in range(0,100):
        solved = depth_first(hundred_puzzles[i])
        total_moves += len(solved) - 2
        total_steps += solved[len(solved) - 2]
        total_time += solved[len(solved) - 1]
    print "Total moves: ", total_moves
    print "Total search steps: ", total_steps
    print "Total time: ", total_time
    # Perform breadth-first search and report statistics;
    # returned list will contain solution moves, plus
    # two additional values on end (total steps and total time)
    total_moves = 0
    total_steps = 0
    total_time = 0
    print "Performing breadth-first search on 100 puzzles"
    for i in range(0, 100):
        solved = breadth_first(hundred_puzzles[i])
        total_moves += len(solved) - 2
        total_steps += solved[len(solved) - 2]
        total_time += solved[len(solved) - 1]
    print "Total moves: ", total_moves
    print "Total search steps: ", total_steps
    print "Total time: ", total_time
    # Perform A* search and report statistics;
    # returned list will contain solution moves, plus
    # two additional values on end (total steps and total time)
    total_moves = 0
    total_steps = 0
    total_time = 0
    print "Performing A* search on 100 puzzles"
    for i in range(0, 100):
        solved = a_star(hundred_puzzles[i])
        total_moves += len(solved) - 2
        total_steps += solved[len(solved) - 2]
        total_time += solved[len(solved) - 1]
    print "Total moves: ", total_moves
    print "Total search steps: ", total_steps
    print "Total time: ", total_time


puzzle_rows = 4
puzzle_columns = 4
main()
