#include <string>

#ifndef TTT_TABLE_H
#define TTT_TABLE_H

class TTTTable {
public:
	TTTTable() {}

	TTTTable(int id, int size, std::string table, std::string nextPlayer)
			: id{id}, size{size}, table{table}, nextPlayer{nextPlayer} {}

	TTTTable(int id, int size, std::string table, std::string nextPlayer, std::string state)
			: id{id}, size{size}, table{table}, nextPlayer{nextPlayer}, state{state} {}

	/*
	 * Get the id of the table.
	 *
	 * @return the id of the table.
	 */
	int getId() const {
		return id;
	}

	/*
	 * Get the size of the table.
	 *
	 * @return the size of the table.
	 */
	int getSize() const {
		return size;
	}

	/*
	 * Get the table of the table.
	 *
	 * @return the table of the table.
	 */
	const std::string& getTable() const {
		return table;
	}

	/*
	 * Get the next player of the table.
	 *
	 * @return the next player of the table.
	 */
	std::string getNextPlayer() const {
		return nextPlayer;
	}

	/*
	 * Get the state of the table.
	 *
	 * @return the state of the table.
	 */
	std::string getState() const {
		return state;
	}

	/*
	 * Set the size of the table.
	 *
	 * @param newSize the new size of the table.
	 */
	void setSize(int newSize) {
		size = newSize;
	}

	/*
	 * Set the table of the table.
	 *
	 * @param newTable the new table of the table.
	 */
	void setTable(std::string newTable) {
		table = newTable;
	}

	/*
	 * Set the next player of the table.
	 *
	 * @param newNextPlayer the new next player of the table.
	 */
	void setNextPlayer(std::string newNextPlayer) {
		nextPlayer = newNextPlayer;
	}

	/*
	 * Set the state of the table.
	 *
	 * @param newState the new state of the table.
	 */
	void setState(std::string newState) {
		state = newState;
	}

	/*
	 * Play this turn of the table by filling a cell.
	 *
	 * @param x the x value of the table cell.
	 * @param y the y value of the table cell.
	 */
	void playTable(int x, int y) {
		int i = x * size + y;
		char c = nextPlayer[0];
		table[i] = c;

		if (nextPlayer == "X") {
			nextPlayer = "0";
		} else if (nextPlayer == "0") {
			nextPlayer = "X";
		}
	}

private:
	int id = 0;
	int size = 3;

	std::string table = "---------";
	std::string nextPlayer = "X";
	std::string state = "Not started";
};

#endif //TTT_TABLE_H
