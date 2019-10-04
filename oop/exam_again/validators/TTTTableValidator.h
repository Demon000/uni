#include <string>

#ifndef TTT_TABLE_VALIDATOR_H
#define TTT_TABLE_VALIDATOR_H

class InvalidTableSizeException : public std::exception {};
class InvalidNextPlayerException : public std::exception {};
class InvalidTableStateException : public std::exception {};
class InvalidTableException : public std::exception {};

class TTTTableValidator {
public:
	/*
	 * Validate the size of a table.
	 *
	 * @param size the size to be validated.
	 *
	 * @throw InvalidTableSizeException if the size is invalid.
	 */
	void validateSize(int size) const {
		if (size < 3 || size > 5) {
			throw InvalidTableSizeException();
		}
	}

	/*
	 * Validate the next player of a table.
	 *
	 * @param nextPlayer the next player to be validated.
	 *
	 * @throw InvalidNextPlayerException if the next player is invalid.
	 */
	void validateNextPlayer(std::string nextPlayer) const {
		if (nextPlayer != "X" && nextPlayer != "0") {
			throw InvalidNextPlayerException();
		}
	}

	/*
	 * Validate the state of a table.
	 *
	 * @param state the next state to be validated.
	 *
	 * @throw InvalidTableStateException if the state is invalid.
	 */
	void validateState(std::string state) const {
		if (state != "Not started"
				&& state != "In progress"
				&& state != "Finished") {
			throw InvalidTableStateException();
		}
	}

	/*
	 * Validate the coordinates of a cell of a table.
	 *
	 * @param size the size of the table.
	 * @param x the x value of the table cell to be validated.
	 * @param y the y value of the table cell to be validated.
	 *
	 * @throw InvalidTableException if coordinates of the cell is invalid.
	 */
	void validatePosition(int size, int x, int y) const {
		int i = x * size + y;
		if (i < 0 || i > size * size - 1) {
			throw InvalidTableException();
		}
	}

	/*
	 * Validate the the table of a table.
	 *
	 * @param size the size of the table.
	 * @param table the table to be validated.
	 *
	 * @throw InvalidTableException if table is invalid.
	 */
	void validateTable(int size, std::string table) const {
		if (table.size() != size * size) {
			throw InvalidTableException();
		}

		for (auto ci = table.begin(); ci < table.end(); ci++) {
			if (*ci != '-'
					&& *ci != 'X'
					&& *ci != '0') {
				throw InvalidTableException();
			}
		}
	}
};

#endif // TTT_TABLE_VALIDATOR_H
